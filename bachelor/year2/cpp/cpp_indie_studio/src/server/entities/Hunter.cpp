/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Created by vincent,
*/

#include "Hunter.hpp"

Hunter::Hunter(const std::pair<float, float> &pos, int id,
	std::shared_ptr<LockedItem<std::vector<std::unique_ptr<Player>>>> players,
	std::shared_ptr<LockedItem<std::vector<std::unique_ptr<AEntity>>>> blocking,
	std::shared_ptr<LockedItem<std::vector<std::unique_ptr<Fire>>>> fire,
	std::shared_ptr<LockedItem<std::vector<std::unique_ptr<Bomb>>>> bomb,
	std::shared_ptr<LockedItem<std::vector<std::unique_ptr<ABonus>>>> bonuses,
	std::shared_ptr<LockedItem<std::vector<PlayerCommunication>>> communication)
	: AI(pos, id, players, blocking, fire, bomb, bonuses, communication)
{}

void Hunter::updatePlayersOnMap()
{
	for (const auto &player : _players->getItem()) {
		if (player->getState() == Element::State::DEAD)
			continue;
		const auto pos = player->getPos();
		node *cell = &_nodeMap[pos.first][pos.second];
		cell->type = player->getType();
		cell->uniqueID = player->getId();
		if (cell->type == Element::Type::PLAYER) {
			cell->goal += 255;
			unsigned char dir = paths::UP;
			for (auto *neighbour : cell->near) {
				//TODO j'ai changé la range de HAINE
				for (int i = 0; neighbour && i < getFirePower() + 1 && !isBodyBlocking(neighbour->type); ++i) {
					neighbour->goal += 255 - (i * 5);
					neighbour = neighbour->near[dir];
				}
				dir++;
			}
		}
		else if (cell->type == Element::Type::AI && cell->uniqueID != _id) {
			cell->goal += 115;
			unsigned char dir = paths::UP;
			for (auto *neighbour : cell->near) {
				for (int i = 0; neighbour && i < getFirePower() + 1 && !isBodyBlocking(neighbour->type); ++i) {
					neighbour->goal += 115 - (i * 5);
					neighbour = neighbour->near[dir];
				}
				dir++;
			}
		}
	}
}

void Hunter::evaluateGoal(node &node)
{
	for (const auto *neighbour : node.near) {
		if (neighbour && neighbour->type == Element::Type::SOFTWALL)
			node.goal += (rand() % 10);
	}
}

void Hunter::updateBonusesOnMap()
{
	_bonuses->lockItem();
	for (const auto &bonus : _bonuses->getItem()) {
		const auto pos = bonus->getPos();
		_nodeMap[pos.first][pos.second].type = bonus->getType();
		_nodeMap[pos.first][pos.second].danger = 0;
		_nodeMap[pos.first][pos.second].goal = 50;
	}
	_bonuses->unlockItem();
}
