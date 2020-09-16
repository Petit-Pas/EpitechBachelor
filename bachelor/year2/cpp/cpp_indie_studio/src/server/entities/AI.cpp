/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Created by vincent,
*/

#include <thread>
#include <cmath>
#include <algorithm>
#include "AI.hpp"

AI::AI(const std::pair<float, float> &pos, int id,
	std::shared_ptr<LockedItem<std::vector<std::unique_ptr<Player>>>> players,
	std::shared_ptr<LockedItem<std::vector<std::unique_ptr<AEntity>>>> blocking,
	std::shared_ptr<LockedItem<std::vector<std::unique_ptr<Fire>>>> fire,
	std::shared_ptr<LockedItem<std::vector<std::unique_ptr<Bomb>>>> bomb,
	std::shared_ptr<LockedItem<std::vector<std::unique_ptr<ABonus>>>> bonuses,
	std::shared_ptr<LockedItem<std::vector<PlayerCommunication>>> communication)
: Player(pos, id), _players(players), _blocking(blocking), _fires(fire),
_bombs(bomb), _bonuses(bonuses), _communication(communication), _uniqueID(20000 + ((getId() - 10) * 10)), _goalAchieve(false), _limitCalcul(0), _goalType(Element::Type::EMPTY), _lapsT(0), _limitCalc(0), _firstUpdate(true), _blocked(0)
{
	_dir = 0;
	_nextDir = dir::directions::NONE;
	_type = Element::Type::AI;

	_bombTimer = 3000;
	unsigned short nodeId = 0;
	twoFloat pos2f = {0.5f, 0.5f};
	for (int i = 0; i < 13; ++i) {
		pos2f.x = 0.5f;
		std::vector<node> tmp;
		for (int j = 0; j < 15; ++j) {
			tmp.push_back({false, false, {nullptr, nullptr, nullptr,
				nullptr}, nullptr, {pos2f.y, pos2f.x},
				Element::Type::EMPTY, 0, 0, nodeId, 0});
			pos2f.x += 1.f;
			nodeId++;
		}
		_nodeMap.push_back(tmp);
		pos2f.y += 1.f;
	}
}

void AI::configureMap()
{
	_blocking->lockItem();
	for (const auto &block : _blocking->getItem()) {
		if (block->getType() == Element::Type::HARDWALL) {
			const auto pos = block->getPos();
			_nodeMap[pos.first][pos.second].type = block->getType();
			_nodeMap[pos.first][pos.second].danger = 0;
			_nodeMap[pos.first][pos.second].goal = 0;
		}
	}
	_blocking->unlockItem();

	for (auto &cells : _nodeMap) {
		for (auto &cell : cells) {
			if (!cell.type) {
				unsigned char path = 1;
				for (auto &neighbour : cell.near) {
					if (!_nodeMap[cell.pos.y + dir::directionPos[path].first][cell.pos.x + dir::directionPos[path].second].type)
						neighbour = &_nodeMap[cell.pos.y + dir::directionPos[path].first][cell.pos.x + dir::directionPos[path].second];
					path++;
				}
			}
		}
	}
}

void AI::update()
{
	if (_firstUpdate) {
		_lastPos.y = _pos.first;
		_lastPos.x = _pos.second;
		configureMap();
		_firstUpdate = false;
	}
	reset();
	updatePlayersOnMap();
	updateBlocksOnMap();
	updateFireOnMap();
	updateBonusesOnMap();
	updateBombsOnMap();
	revalueMap();
	elaborateStrategy();
}

void AI::elaborateStrategy()
{
	const auto acceptableDanger = static_cast<unsigned char>(50 + _speed * 10);
	if (_nodeMap[_pos.first][_pos.second].danger > acceptableDanger || _nodeMap[_pos.first + 0.255f][_pos.second].danger > acceptableDanger || _nodeMap[_pos.first - 0.275f][_pos.second].danger > acceptableDanger || _nodeMap[_pos.first][_pos.second + 0.275f].danger > acceptableDanger || _nodeMap[_pos.first][_pos.second - 0.275f].danger > acceptableDanger)
		actDefensively();
	else
		actOffensively();
	const auto futurePos = _pos + _dirVector;
	if (isBodyBlocking(_nodeMap[futurePos.first][futurePos.second].type) || _nodeMap[futurePos.first][futurePos.second].type == Element::FIRE)
		recenterMyPosition();
	const auto yPrecision = _pos.first - floorf(_pos.first);
	const auto xPrecision = _pos.second - floorf(_pos.second);
	if (((_dir == dir::UP && _nextDir == dir::LEFT) || (_dir == dir::DOWN && _nextDir == dir::RIGHT)
		|| (_dir == dir::DOWN && _nextDir == dir::LEFT) || (_dir == dir::UP && _nextDir == dir::RIGHT))
		&& yPrecision < 0.6f && yPrecision > 0.4f) {
		recenterMyYPosition();
		_dir = _nextDir;
	}
	else if (((_dir == dir::RIGHT && _nextDir == dir::UP) || (_nextDir == dir::DOWN && _dir == dir::LEFT)
		|| (_nextDir == dir::DOWN && _dir == dir::RIGHT) || (_nextDir == dir::UP && _dir == dir::LEFT))
		&& xPrecision < 0.6f && xPrecision > 0.4f) {
		recenterMyXPosition();
		_dir = _nextDir;
	}
	else if (((_dir == dir::RIGHT && _nextDir == dir::LEFT) || (_dir == dir::LEFT && _nextDir == dir::RIGHT))
		&& (yPrecision < 0.6f && yPrecision > 0.4f)) {
		recenterMyYPosition();
		_dir = _nextDir;
	}
	else if (((_dir == dir::UP && _nextDir == dir::DOWN) || (_dir == dir::DOWN && _nextDir == dir::UP))
		&& (xPrecision < 0.6f && xPrecision > 0.4f)) {
		recenterMyXPosition();
		_dir = _nextDir;
	}
	else if (_dir == dir::NONE && _dir != _nextDir) {
		recenterMyPosition();
		_dir = _nextDir;
	}
	_dirVector.first = dir::directionPos[_dir].first;
	_dirVector.second = dir::directionPos[_dir].second;
}

void AI::evaluateGoal(node &node)
{
	for (const auto *neighbour : node.near) {
		if (neighbour && neighbour->type == Element::Type::SOFTWALL)
			node.goal += 15 + (rand() % 15);
	}
}

void AI::evaluateCellEscapes(node *node)
{
	for (const auto *neighbour : node->near) {
		if (neighbour && !isBodyBlocking(neighbour->type))
			node->danger -= 4;
		else
			node->danger++;
	}
}

void AI::evaluateDanger(node &node, const Bomb &bomb)
{
	const auto firePower = bomb.getRadius();
	auto percentage = bomb.getPercentageBeforeExplosion();
	if (percentage < node.danger - 200)
		percentage = static_cast<unsigned short>(node.danger - 200);
	unsigned char dir = paths::UP;

	for (auto *neighbour : node.near) {
		if (neighbour)
			spreadFireInLine(firePower, percentage, neighbour, dir);
		dir++;
	}
}

void AI::compareGoalCells(node *node)
{
	unsigned short goal = 0;
	if (node->goal > goal) {
		interestingGoal(node);
		return;
	}
	for (auto *neighbour : node->near) {
		if (neighbour && neighbour->goal > 0){
			interestingGoal(neighbour);
			return;
		}
	}
	_findPath.setGoal({0.5f, 0.5f});
	_findPath.setStart(_pos);
	_findPath.findPath(_nodeMap);
	_goalPos = _findPath.interestingGoalCell(_goalType);
}

void AI::setPath()
{
	_findPath.setGoal(_goalPos);
	_findPath.setStart(_pos);
	_findPath.setAcceptableDanger(static_cast<unsigned char>(50 +_speed * 10));
	unsigned char direction = _findPath.findPath(_nodeMap);
	_nextDir = static_cast<dir::directions>(direction);

	if (_nextDir == dir::directions::NONE) {
		recenterMyPosition();
		_dir = _nextDir;
		_blocked++;
		if (_blocked > 60 && isBombAvailable() && isGoodTimeToDropBomb()) {
			removeBomb();
			auto newOne = std::make_unique<Bomb>(
				std::pair<float, float>(_pos.first, _pos.second),
				getFirePower(), getBombTimer(),
				getId(), _uniqueID++, false);
			packageServerClient package(newOne->entityToPackage(PackageType::CREATE));

			_communication.get()->lockItem();
			auto vec = _communication.get()->getItem();
			for (auto &player : vec) {
				player.sendData(package);
			}
			_communication.get()->unlockItem();
			_bombs->lockItem();
			_bombs->getItem().emplace_back(std::move(newOne));
			_bombs->unlockItem();
			_blocked = 0;
			_lapsT++;
		}
	} else
		_blocked = 0;
}

void AI::setSafePosition()
{
	auto &node = _nodeMap[_pos.first][_pos.second];
	evaluateCellEscapes(&node);
	short danger = node.danger;
	unsigned short interest = node.goal;
	int targetPath = 1;
	_nextDir = dir::NONE;

	for (auto *neighbour : node.near) {
		if (neighbour)
			evaluateCellEscapes(neighbour);
	}

	for (auto *neighbour : node.near) {
		if (neighbour && isSaferCell(neighbour, danger, interest)) {
			_safePos.y = neighbour->pos.y;
			_safePos.x = neighbour->pos.x;
			_nextDir = static_cast<dir::directions>(targetPath);
			danger = neighbour->danger;
			interest = neighbour->goal;
		}
		targetPath++;
	}
	if (_nextDir == dir::NONE) {
		_dir = _nextDir;
		recenterMyPosition();
	}
}

void AI::actDefensively()
{
	setSafePosition();
}

void AI::actOffensively()
{
	_lapsT = 0;
	if (_limitCalcul <= 0) {
		compareGoalCells(&_nodeMap[_pos.first][_pos.second]);
		setPath();
		_limitCalcul = 4;
	} else
		_limitCalcul--;

	bool goalAchieve = false;
	if ((fabsf(_goalPos.y - _pos.first) <= 0.1f &&
		fabsf(_goalPos.x - _pos.second) <= 0.1f)) {
		goalAchieve = true;
	}

	if (!_lapsT && goalAchieve && isBombAvailable() && isGoodTimeToDropBomb()) {
		removeBomb();
		auto newOne = std::make_unique<Bomb>(
			std::pair<float, float>(_goalPos.y,_goalPos.x),
			getFirePower(), getBombTimer(),
			getId(), _uniqueID++, false);
		packageServerClient package(newOne->entityToPackage(PackageType::CREATE));

		_communication.get()->lockItem();
		auto vec = _communication.get()->getItem();
		for (auto &player : vec) {
			player.sendData(package);
		}
		_communication.get()->unlockItem();
		_bombs->lockItem();
		_bombs->getItem().emplace_back(std::move(newOne));
		_bombs->unlockItem();
	}
}

short AI::isSaferCell(node *cell, const short minDanger, const unsigned short interest)
{
	if (!isBodyBlocking(cell->type) && cell->type != Element::Type::FIRE
		&& cell->danger <= minDanger) {
		if (cell->danger < minDanger)
			return true;
		return (interest < cell->goal);
	}
	return (false);

}

unsigned short AI::interestingGoal(const node *nodeInformation)
{
	_goalPos.y = nodeInformation->pos.y;
	_goalPos.x = nodeInformation->pos.x;
	return  nodeInformation->goal;
}

bool AI::isTransitoryEntity(const Element::Type &type) const
{
	return (type != Element::Type::HARDWALL);
}

void AI::reset()
{
	for (auto &nodes : _nodeMap) {
		for (auto &node : nodes) {
			if (isTransitoryEntity(node.type)) {
				node.visited = false;
				node.deadEnd = false;
				node.parent = nullptr;
				node.type = Element::EMPTY;
				node.goal = 0;
				node.danger = 0;
				node.uniqueID = 0;
			}
		}
	}
}

void AI::updatePlayersOnMap()
{
	for (const auto &player : _players->getItem()) {
		if (player->getState() == Element::State::DEAD)
			continue;
		const auto pos = player->getPos();
		node *cell = &_nodeMap[pos.first][pos.second];
		cell->uniqueID = player->getId();
		cell->type = player->getType();
		if (cell->type == Element::Type::PLAYER) {
			cell->goal += 45;
			unsigned char dir = paths::UP;
			for (auto *neighbour : cell->near) {
				for (int i = 0; neighbour && i < (getFirePower() / 2 + 1) && !isBodyBlocking(neighbour->type); ++i) {
					neighbour->goal += 45 - i;
					neighbour = neighbour->near[dir];
				}
				dir++;
			}
		}
		else if (cell->type == Element::Type::AI && cell->uniqueID != _id) {
			cell->goal += 45;
			unsigned char dir = paths::UP;
			for (auto *neighbour : cell->near) {
				for (int i = 0; neighbour && i < (getFirePower() / 2 + 1) && !isBodyBlocking(neighbour->type); ++i) {
					neighbour->goal += 45 - i;
					neighbour = neighbour->near[dir];
				}
				dir++;
			}
		}
	}
}

void AI::updateBlocksOnMap()
{
	_blocking->lockItem();
	for (const auto &block : _blocking->getItem()) {
		const auto pos = block->getPos();
		_nodeMap[pos.first][pos.second].type = block->getType();
		_nodeMap[pos.first][pos.second].danger = 0;
		_nodeMap[pos.first][pos.second].goal = 0;
	}
	_blocking->unlockItem();
}

void AI::updateFireOnMap()
{
	_fires->lockItem();
	for (const auto &fire : _fires->getItem()) {
		const auto pos = fire->getPos();
		_nodeMap[pos.first][pos.second].type = fire->getType();
		_nodeMap[pos.first][pos.second].danger = 200;
		_nodeMap[pos.first][pos.second].goal = 0;
	}
	_fires->unlockItem();
}

void AI::updateBombsOnMap()
{
	_bombs->lockItem();
	for (const auto &bomb : _bombs->getItem()) {
		const auto pos = bomb->getPos();
		_nodeMap[pos.first][pos.second].type = bomb->getType();
		if (_nodeMap[pos.first][pos.second].danger > 15 &&  _nodeMap[pos.first][pos.second].danger < 110)
			_nodeMap[pos.first][pos.second].danger = static_cast<unsigned short>(200 + _nodeMap[pos.first][pos.second].danger);
		else
			_nodeMap[pos.first][pos.second].danger = static_cast<unsigned short>(200 + bomb->getPercentageBeforeExplosion());
		_nodeMap[pos.first][pos.second].goal = 0;
		evaluateDanger(_nodeMap[pos.first][pos.second], *bomb);
	}
	_bombs->unlockItem();
}

void AI::updateBonusesOnMap()
{
	_bonuses->lockItem();
	for (const auto &bonus : _bonuses->getItem()) {
		const auto pos = bonus->getPos();
		_nodeMap[pos.first][pos.second].type = bonus->getType();
		_nodeMap[pos.first][pos.second].danger = 0;
		_nodeMap[pos.first][pos.second].goal = 250;
	}
	_bonuses->unlockItem();
}

void AI::revalueMap()
{
	for (auto &nodes : _nodeMap) {
		for (auto &node : nodes) {
			if (!isBodyBlocking(node.type)) {
				evaluateGoal(node);
				evaluateCellEscapes(&node);
			}
		}
	}
}

float AI::calculateDistanceBetween2f(const twoFloat &nb1, const twoFloat &nb2) const
{
	const float distanceX = powf(nb1.x - nb2.x, 2.f);
	const float distanceY = powf(nb1.y - nb2.y, 2.f);

	return sqrtf(distanceX - distanceY);
}

bool AI::compareDistance(const std::pair<float, twoFloat> &elmnt1, const std::pair<float, twoFloat> &elmnt2)
{
	return (elmnt1.first < elmnt2.first);
}

bool AI::canSpreadFire(const unsigned char fireAdvance, const int firePower, const node *neighbour, char &breakSoftCapability)
{
	if (fireAdvance < firePower && neighbour && neighbour->type != Element::Type::HARDWALL && breakSoftCapability) {
		if (neighbour->type == Element::Type::SOFTWALL)
			breakSoftCapability--;
		return true;
	}
	return false;
}

void AI::spreadFireInLine(const int firePower, const int percentage, node *neighbour,
	unsigned char dir)
{
	node *head = neighbour;
	char breakSoftCapability = 1;
	for (unsigned char fireAdvance = 0; canSpreadFire(fireAdvance, firePower, neighbour, breakSoftCapability); ++fireAdvance) {
		if (neighbour->danger < percentage + ((firePower - fireAdvance) * 2))
			neighbour->danger += percentage + ((firePower - fireAdvance) * 2);
		neighbour = neighbour->near[dir];
	}
	breakSoftCapability = 1;
	neighbour = head;
	for (unsigned char fireAdvance = 0; canSpreadFire(fireAdvance, firePower, neighbour, breakSoftCapability); ++fireAdvance) {
		for (auto *wayOut : neighbour->near) {
			if (wayOut && !isBodyBlocking(wayOut->type) && wayOut->danger < 1)
				return;
		}
		neighbour = neighbour->near[dir];
	}
	breakSoftCapability = 1;
	neighbour = head;
	for (unsigned char fireAdvance = 0; canSpreadFire(fireAdvance, firePower, neighbour, breakSoftCapability); ++fireAdvance) {
		neighbour->danger += 20;
		neighbour = neighbour->near[dir];
	}
}

bool AI::isBodyBlocking(const Element::Type &type)
{
	return (type == Element::Type::SOFTWALL ||
		type == Element::Type::HARDWALL ||
		type == Element::Type::BOMB);
}

bool AI::isGoodTimeToDropBomb()
{
	auto &node = _nodeMap[_pos.first][_pos.second];
	unsigned char dir = paths::UP;
	const auto firePower = getFirePower();

	for (auto *neighbour : node.near) {
		if (neighbour && !isBodyBlocking(neighbour->type) && neighbour->danger < 1) {
			char breakSoftCapability = 1;
			for (unsigned char fireAdvance = 0; canSpreadFire(fireAdvance, firePower, neighbour, breakSoftCapability); ++fireAdvance) {
				for (auto *nextNeighbour : neighbour->near) {
					if (nextNeighbour && !isBodyBlocking(nextNeighbour->type) && hasWayOut(nextNeighbour->pos, node.pos, dir) && nextNeighbour->danger < 1)
						return true;
				}
				neighbour = neighbour->near[dir];
			}
			if (neighbour && !isBodyBlocking(neighbour->type) && neighbour->danger < 1)
				return true;
		}
		dir++;
	}
	return false;
}

bool AI::hasWayOut(twoFloat wayOutPos, twoFloat bombPos, unsigned char direction)
{
	if (direction == paths::UP || direction == paths::DOWN)
		return (wayOutPos.x != bombPos.x);
	else
		return (wayOutPos.y != bombPos.y);
}

void AI::recenterMyPosition()
{
	auto fixPos = getPos();
	fixPos.first = floorf(_pos.first) + 0.5f;
	fixPos.second = floorf(_pos.second) + 0.5f;
	const auto diffX = fixPos.second - _pos.second;
	const auto diffY = fixPos.first - _pos.first;
	if (fabsf(diffX) >= 0.25f)
		_pos.second += (diffX > 0) ? (0.25f) : (-0.25f);
	else if (fabsf(diffX) < 0.25f && fabsf(diffX) >= 0.01f)
		_pos.second = floorf(_pos.second) + 0.5f;
	if (fabsf(diffY) >= 0.25f)
		_pos.first += (diffY > 0) ? (0.25f) : (-0.25f);
	else if (fabsf(diffY) < 0.25f && fabsf(diffY) >= 0.01f)
		_pos.first = floorf(_pos.first) + 0.5f;
}

void AI::recenterMyXPosition()
{
	_pos.second = floorf(_pos.second) + 0.5f;
}

void AI::recenterMyYPosition()
{
	_pos.first = floorf(_pos.first) + 0.5f;
}

unsigned short AI::deadEnd(const node *node)
{
	unsigned char deadEnd = 0;

	for (auto *neighbour : node->near) {
		if (neighbour && (isBodyBlocking(neighbour->type) || neighbour->danger > 0))
			deadEnd++;
	}
	return static_cast<unsigned short>(deadEnd * 2);
}

void AI::incrementSpeed()
{
	_speed += 0.01;
}