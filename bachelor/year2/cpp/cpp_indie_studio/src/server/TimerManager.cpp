/*
** EPITECH PROJECT, 2021
** cpp_inidie_studio
** File description:
** internal functions
*/

#include <iostream>
#include <utility>
#include <thread>
#include <cstring>
#include "RandomBonusGenerator.hpp"
#include "Bomb.hpp"
#include "Player.hpp"
#include "TimerManager.hpp"
#include "Direction.hpp"
#include "MyGlobal.hpp"
#include "AI.hpp"

TimerManager::TimerManager(std::shared_ptr<LockedItem<std::vector<std::unique_ptr<Player>>>> players,
	std::shared_ptr<LockedItem<std::vector<std::unique_ptr<AEntity>>>> blocking,
	std::shared_ptr<LockedItem<std::vector<std::unique_ptr<Fire>>>> fires,
	std::shared_ptr<LockedItem<std::vector<std::unique_ptr<Bomb>>>> bombs,
	std::shared_ptr<LockedItem<std::vector<std::unique_ptr<ABonus>>>> bonuses,
	std::shared_ptr<LockedItem<std::vector<PlayerCommunication>>> playerCom
) : _players(players), _blocking(blocking), _fires(fires), _bombs(bombs), _bonuses(bonuses), _playerCom(playerCom),
	_uniqueID(1000000), _startAI(false)
{
}

TimerManager::~TimerManager()
{
}

void TimerManager::run()
{
	while (!endG) {
		if (_startAI)
			updateAIs();
		explodeBombs();
		dispawnFires();
		movePlayers();
		checkDeconnection();
		std::this_thread::sleep_for(std::chrono::milliseconds(25));
	}
}

void TimerManager::dispawnFires()
{
	_fires.get()->lockItem();
	auto fire = _fires.get()->getItem().begin();
	while (fire != _fires.get()->getItem().end()) {
		fire->get()->update();
		if (fire->get()->isOver()) {
			if (fire->get()->canSpawnBonus() && rand() % 3 == 0)
				addBonus(fire->get()->getPos());
			sendDeleteObject(fire->get());
			_fires.get()->getItem().erase(fire);
		} else
			fire++;
	}
	_fires.get()->unlockItem();
}

void TimerManager::explodeBombs()
{
	_bombs.get()->lockItem();
	if (!_bombs.get()->getItem().empty()) {
		auto bomb = _bombs.get()->getItem().begin();
		while (bomb != _bombs.get()->getItem().end()) {
			bomb->get()->update();
			if (bomb->get()->isOver()) {
				explodeBomb(bomb->get());
				sendDeleteObject(bomb->get());
				removeBombFromPlayer(bomb->get());
				_bombs.get()->getItem().erase(bomb);
			} else
				bomb++;
		}
	}
	_bombs.get()->unlockItem();
}

void TimerManager::explodeBomb(Bomb *bomb)
{
	_blocking.get()->lockItem();
	auto explosion = bomb->getFire(_blocking.get()->getItem(), _uniqueID);
	_blocking.get()->unlockItem();
	for (auto &item : explosion) {
		_fires.get()->lockItem();
		sendCreateObject(&item);
		spawnExplosion(item);
		_fires.get()->unlockItem();
	}
}

void TimerManager::checkDeconnection()
{
	_players->lockItem();
	for (size_t i = 0; i < _playerCom->getItem().size(); i++) {
		if (!_playerCom->getItem()[i].isOpen() &&
		    _players->getItem()[i]->getState() != Element::State::DEAD) {
			_players->getItem()[i]->setState(Element::State::DEAD);
			sendDeleteObject(_players->getItem()[i].get());
		}
	}
	_players->unlockItem();
}

void TimerManager::spawnExplosion(Fire &fire)
{
	_fires.get()->getItem().emplace_back(std::make_unique<Fire>(fire));
	_players.get()->lockItem();
	for (auto &player : _players.get()->getItem()) {
		if (fire.isHitBigHitBox(player->getPos())) {
			player->setState(Element::State::DEAD);
			sendDeleteObject(player.get());
		}
	}
/*	_playerCom->lockItem();
	for (size_t i = 0; i < _players->getItem().size(); i++) {
		if (_players->getItem()[i]->getState() == Element::State::DEAD) {
			_players->getItem().erase(_players->getItem().begin() + i);
			_playerCom->getItem().erase(_playerCom->getItem().begin() + i);
			i--;
		}
	}
	_playerCom->unlockItem();*/
	_players.get()->unlockItem();

	_blocking.get()->lockItem();
	auto blocking = _blocking.get()->getItem().begin();
	while (blocking != _blocking.get()->getItem().end()) {
		if (fire.isHitBigHitBox((*blocking)->getPos())) {
			sendDeleteObject(blocking->get());
			_blocking.get()->getItem().erase(blocking);
			_blocking.get()->unlockItem();
			fire.canNowSpawnBonus();
			return;
		}
		blocking++;
	}
	_blocking.get()->unlockItem();

	for (auto &bomb : _bombs.get()->getItem()) {
		if (bomb->isHitBigHitBox(fire.getPos())) {
			bomb->forceExplosion();
			return;
		}
	}

	_bonuses.get()->lockItem();
	auto bonus = _bonuses.get()->getItem().begin();
	while (bonus != _bonuses.get()->getItem().end()) {
		if (bonus->get()->isHitBigHitBox(fire.getPos())) {
			sendDeleteObject(bonus->get());
			_bonuses.get()->getItem().erase(bonus);
			_bonuses.get()->unlockItem();
			return;
		}
		bonus++;
	}
	_bonuses.get()->unlockItem();
}

void TimerManager::movePlayers()
{
	_players.get()->lockItem();
	for (auto &player : _players.get()->getItem()) {
		if (player->getDirVector() != dir::directionPos.at(dir::NONE)) {
			if (playerCanMove(player.get())) {
				std::pair<float, float> tmp(
					player->getPos().first + player->getDirVector().first * player->getSpeed(),
					player->getPos().second + player->getDirVector().second * player->getSpeed());
				player->setPos(tmp);
				player->unsetIdle();
				if (!_startAI)
					_startAI = true;
			}
		} else {
			if (!player->isIdleSend()) {
				sendIdleObject(player.get());
				player->setIdleSend();
			}
		}
	}
	_players.get()->unlockItem();
}

void TimerManager::removeBombFromPlayer(Bomb *bomb)
{
	_players.get()->lockItem();
	for (auto &player : _players.get()->getItem()) {
		if (player->getId() == bomb->getPlayerId()) {
			player->bombAvailable();
			break;
		}
	}
	_players.get()->unlockItem();
}

void TimerManager::addBonus(const std::pair<float, float> &pos)
{
	_bonuses.get()->lockItem();
	auto *newOne = RandomBonusGenerator::getRandomBonus(pos, getNewUniqueID());
	sendCreateObject(newOne);
	_bonuses.get()->getItem().emplace_back(std::unique_ptr<ABonus>(newOne));
	_bonuses.get()->unlockItem();
}

int TimerManager::getNewUniqueID()
{
	_uniqueID += 1;
	return _uniqueID;
}

TimerManager::TimerManager(TimerManager &toCopy) : _players(toCopy._players), _blocking(toCopy._blocking),
	_fires(toCopy._fires), _bombs(toCopy._bombs), _bonuses(toCopy._bonuses)
{
}

void TimerManager::sendIdleObject(AEntity *object)
{
	packageServerClient package(object->entityToPackage(PackageType::IDLE));

	_playerCom.get()->lockItem();
	auto vec = _playerCom.get()->getItem();
	for (auto &player : vec) {
		player.sendData(package);
	}
	_playerCom.get()->unlockItem();
}

void TimerManager::sendDeleteObject(AEntity *object)
{
	packageServerClient package(object->entityToPackage(PackageType::DEL));

	_playerCom.get()->lockItem();
	auto vec = _playerCom.get()->getItem();
	for (auto &player : vec) {
		player.sendData(package);
	}
	_playerCom.get()->unlockItem();
}

void TimerManager::sendCreateObject(AEntity *object)
{
	packageServerClient package(object->entityToPackage(PackageType::CREATE));

	_playerCom.get()->lockItem();
	auto vec = _playerCom.get()->getItem();
	for (auto &player : vec) {
		player.sendData(package);
	}
	_playerCom.get()->unlockItem();
}

bool TimerManager::playerCanMove(Player *player)
{
	std::pair<float, float> plannedPos = {
		player->getPos().first + (player->getSpeed()) * player->getDirVector().first,
		player->getPos().second + (player->getSpeed()) * player->getDirVector().second};

	if (checkHitboxBlocking(plannedPos, player))
		return false;
	if (checkHitboxBombs(plannedPos, player))
		return false;
	if (checkHitboxFires(plannedPos, player))
		return true;
	if (checkHitboxBonuses(plannedPos, player))
		return true;
	return true;
}

bool TimerManager::checkWalkThrough(Player *player)
{
	if (player->isInAWall())
		return true;
	if (!player->canWalkThrough())
		return false;
	player->setInAWall(true);
	return true;
}

bool TimerManager::checkHitboxBlocking(const std::pair<float, float> &plannedPos, Player *player
)
{
	_blocking.get()->lockItem();
	for (auto &blocking : _blocking.get()->getItem()) {
		if (blocking->isHitBigHitBox(plannedPos) && blocking->getType() == Element::Type::HARDWALL) {
			_blocking.get()->unlockItem();
			return true;
		}
	}
	for (auto &blocking : _blocking.get()->getItem()) {
		if (blocking->isHitBigHitBox(plannedPos) && blocking->getType() == Element::Type::SOFTWALL) {
			bool retVal = checkWalkThrough(player);
			_blocking.get()->unlockItem();
			return !retVal;
		}
	}
	_blocking.get()->unlockItem();
	player->setInAWall(false);
	return false;
}

bool TimerManager::checkHitboxBombs(const std::pair<float, float> &plannedPos, Player *player
)
{
	_bombs.get()->lockItem();
	for (auto &bomb : _bombs.get()->getItem()) {
		if (bomb->isHitBigHitBox(plannedPos)) {
			_bombs.get()->unlockItem();
			if (!bomb->isHitBigHitBox(player->getPos()))
				return true;
			std::pair<int, int> fullCoord(static_cast<const int>(player->getPos().first),
				static_cast<const int>(player->getPos().second));
			std::pair<int, int> fullPlannedCoord(static_cast<const int>(plannedPos.first),
				static_cast<const int>(plannedPos.second));
			if (fullPlannedCoord == fullCoord)
				return false;
			if (!bomb->isHitNormalHitBox(plannedPos))
				return false;
			return true;
		}
	}
	_bombs.get()->unlockItem();
	return false;
}

bool TimerManager::checkHitboxFires(const std::pair<float, float> &plannedPos, Player *player
)
{
	_fires.get()->lockItem();
	for (auto &fire : _fires.get()->getItem()) {
		if (fire->isHitNormalHitBox(plannedPos)) {
			_fires.get()->unlockItem();
			player->setState(Element::State::DEAD);
			sendDeleteObject(player);
			return true;
		}
	}
	_fires.get()->unlockItem();
	return false;
}

bool TimerManager::checkHitboxBonuses(const std::pair<float, float> &plannedPos, Player *player
)
{
	_bonuses.get()->lockItem();
	auto bonus = _bonuses.get()->getItem().begin();
	while (bonus != _bonuses.get()->getItem().end()) {
		if ((*bonus)->isHitNormalHitBox(plannedPos)) {
			bonus->get()->apply(player);
			sendDeleteObject(bonus->get());
			_bonuses.get()->getItem().erase(bonus);
			_bonuses.get()->unlockItem();
			return true;
		}
		bonus++;
	}
	_bonuses.get()->unlockItem();
	return false;
}

void TimerManager::updateAIs()
{
	_players->lockItem();
	for (auto &ai : _players->getItem()) {
		if (ai->getType() == Element::Type::AI && ai->getState() != Element::State::DEAD) {
			dynamic_cast<AI *>(ai.get())->update();
		}
	}
	_players->unlockItem();
}