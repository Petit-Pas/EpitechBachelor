/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Created by vincent,
*/

#include "Coward.hpp"

Coward::Coward(const std::pair<float, float> &pos, int id,
	std::shared_ptr<LockedItem<std::vector<std::unique_ptr<Player>>>> players,
	std::shared_ptr<LockedItem<std::vector<std::unique_ptr<AEntity>>>> blocking,
	std::shared_ptr<LockedItem<std::vector<std::unique_ptr<Fire>>>> fire,
	std::shared_ptr<LockedItem<std::vector<std::unique_ptr<Bomb>>>> bomb,
	std::shared_ptr<LockedItem<std::vector<std::unique_ptr<ABonus>>>> bonuses,
	std::shared_ptr<LockedItem<std::vector<PlayerCommunication>>> communication)
	: AI(pos, id, players, blocking, fire, bomb, bonuses, communication), _lapsBetween2Drop(250)
{}

void Coward::updatePlayersOnMap()
{
	for (const auto &player : _players->getItem()) {
		if (player->getState() == Element::State::DEAD)
			continue;
		const auto pos = player->getPos();
		node *cell = &_nodeMap[pos.first][pos.second];
		cell->type = player->getType();
		cell->uniqueID = player->getId();
		if (cell->type == Element::Type::PLAYER) {
			cell->danger += 215;
			unsigned char dir = paths::UP;
			for (auto *neighbour : cell->near) {
				for (int i = 0; neighbour && i < 8 && !isBodyBlocking(neighbour->type); ++i) {
					neighbour->danger += 215 - (i * 15);
					neighbour = neighbour->near[dir];
				}
				dir++;
			}
		}
		else if (cell->type == Element::Type::AI && cell->uniqueID != _id) {
			cell->danger += 175;
			unsigned char dir = paths::UP;
			for (auto *neighbour : cell->near) {
				for (int i = 0; neighbour && i < 8 && !isBodyBlocking(neighbour->type); ++i) {
					neighbour->danger += 175 - (i * 15);
					neighbour = neighbour->near[dir];
				}
				dir++;
			}
		}
	}
}

void Coward::addBomb()
{
}


bool Coward::isGoodTimeToDropBomb()
{
	if (_lapsBetween2Drop) {
		_lapsBetween2Drop--;
		return false;
	}

	auto &node = _nodeMap[_pos.first][_pos.second];
	unsigned char dir = paths::UP;
	const auto firePower = getFirePower();

	for (auto *neighbour : node.near) {
		if (neighbour && !isBodyBlocking(neighbour->type) && neighbour->danger < 1) {
			char breakSoftCapability = 1;
			for (unsigned char fireAdvance = 0; canSpreadFire(fireAdvance, firePower, neighbour, breakSoftCapability); ++fireAdvance) {
				for (auto *nextNeighbour : neighbour->near) {
					if (nextNeighbour && !isBodyBlocking(nextNeighbour->type) && hasWayOut(nextNeighbour->pos, node.pos, dir) && nextNeighbour->danger < 1) {
						_lapsBetween2Drop = 150;
						return true;
					}
				}
				neighbour = neighbour->near[dir];
			}
			if (neighbour && !isBodyBlocking(neighbour->type) && neighbour->danger < 1) {
				_lapsBetween2Drop = 150;
				return true;
			}
		}
		dir++;
	}
	return false;
}

void Coward::compareGoalCells(node *node)
{
	_findPath.setGoal({0.5f, 0.5f});
	_findPath.setStart(_pos);
	_findPath.findPath(_nodeMap);
	_goalPos = _findPath.interestingSafeCell(node->type);
}

void Coward::evaluateCellEscapes(node *node)
{
	for (const auto *neighbour : node->near) {
		if (neighbour && !isBodyBlocking(neighbour->type))
			node->danger -= 8 + (rand() % 10);
		else
			node->danger++;
	}
}