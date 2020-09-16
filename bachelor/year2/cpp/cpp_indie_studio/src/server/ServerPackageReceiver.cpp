/*
** EPITECH PROJECT, 2021
** cpp_indie_studio
** File description:
** internal functions
*/

#include <iostream>
#include <utility>
#include <thread>
#include "ABonus.hpp"
#include "Player.hpp"
#include "Bomb.hpp"
#include "ServerPackageReceiver.hpp"
#include "Direction.hpp"
#include "MyGlobal.hpp"

ServerPackageReceiver::ServerPackageReceiver(std::shared_ptr<LockedItem<std::vector<std::unique_ptr<Player>>>> players,
	std::shared_ptr<LockedItem<std::vector<std::unique_ptr<AEntity>>>> blocking,
	std::shared_ptr<LockedItem<std::vector<std::unique_ptr<Fire>>>> fire,
	std::shared_ptr<LockedItem<std::vector<std::unique_ptr<Bomb>>>> bomb,
	std::shared_ptr<LockedItem<std::vector<std::unique_ptr<ABonus>>>> bonuses,
	std::shared_ptr<LockedItem<std::vector<PlayerCommunication>>> playerCom
) : _players(players), _blocking(blocking), _fires(fire), _bombs(bomb), _bonuses(bonuses), _uniqueIDAvailable(1000),
	_playerCom(playerCom)
{
}

void ServerPackageReceiver::run()
{
	while (!endG) {
		packageClientServer input = getPackage();
		switch (input.magicNumber) {
		case SPAWNBOMB:
			spawnBomb(input);
			break;
		case MOVE:
			movePlayer(input);
			break;
		default:
			std::this_thread::sleep_for(std::chrono::milliseconds(40));
			break;
		}
	}
}

packageClientServer ServerPackageReceiver::getPackage()
{
	packageClientServer input = {NONE, 0, 0};

	_playerCom.get()->lockItem();
	auto vec = _playerCom.get()->getItem();
	for (auto &player : vec) {
		if (player.recvData<>(input)) {
			_playerCom.get()->unlockItem();
			return (input);
		}
	}
	_playerCom.get()->unlockItem();
	return input;
}

void ServerPackageReceiver::spawnBomb(packageClientServer &input)
{
	Player *stockPlayer = nullptr;

	_players->lockItem();
	for (auto &player : _players->getItem()) {
		if (input.playerID == player->getId()) {
			if (!player->isBombAvailable()) {
				_players->unlockItem();
				return;
			}
			stockPlayer = player.get();
		}
	}
	if (!stockPlayer || stockPlayer->isInAWall()) {
		_players->unlockItem();
		return;
	}

	_bombs->lockItem();
	for (auto &bomb : _bombs->getItem()) {
		std::pair<int, int> bombPos(bomb->getPos().first, bomb->getPos().second);
		std::pair<int, int> playerPos(stockPlayer->getPos().first, stockPlayer->getPos().second);
		if (bombPos == playerPos) {
			_bombs->unlockItem();
			_players->unlockItem();
			return;
		}
	}

	stockPlayer->removeBomb();
	auto newOne = std::make_unique<Bomb>(
		std::pair<float, float>(static_cast<int>(stockPlayer->getPos().first) + 0.5f,
			static_cast<int>(stockPlayer->getPos().second) + 0.5f), stockPlayer->getFirePower(),
		stockPlayer->getBombTimer(), stockPlayer->getId(), getNewUniqueID(), stockPlayer->hasBigBomb());

	packageServerClient package(newOne->entityToPackage(PackageType::CREATE));

	_playerCom.get()->lockItem();
	auto vec = _playerCom.get()->getItem();
	for (auto &player : vec) {
		player.sendData(package);
	}
	_playerCom.get()->unlockItem();

	_bombs->getItem().emplace_back(std::move(newOne));

	_players->unlockItem();
	_bombs->unlockItem();
}

void ServerPackageReceiver::movePlayer(packageClientServer &input)
{
	_players.get()->lockItem();
	for (auto &player : _players.get()->getItem()) {
		if (player->getId() == input.playerID) {
			player->setDirVector(dir::directionPos[input.action]);
			player->setDir(input.action);
			break;
		}
	}
	_players.get()->unlockItem();
}

int ServerPackageReceiver::getNewUniqueID()
{
	_uniqueIDAvailable += 1;
	return _uniqueIDAvailable;
}

ServerPackageReceiver::~ServerPackageReceiver()
{
}
