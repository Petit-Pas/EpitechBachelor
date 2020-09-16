/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Created by vincent,
*/

#include "AIFactory.hpp"

AI *AIFactory::getAI(ind::ia::Types type, const std::pair<float, float> &pos, int id, std::shared_ptr<LockedItem<std::vector<std::unique_ptr<Player>>>> players,
	std::shared_ptr<LockedItem<std::vector<std::unique_ptr<AEntity>>>> blocking,
	std::shared_ptr<LockedItem<std::vector<std::unique_ptr<Fire>>>> fire,
	std::shared_ptr<LockedItem<std::vector<std::unique_ptr<Bomb>>>> bomb,
	std::shared_ptr<LockedItem<std::vector<std::unique_ptr<ABonus>>>> bonuses,
	std::shared_ptr<LockedItem<std::vector<PlayerCommunication>>> communication)
{
	switch (static_cast<int>(type)) {
	case 1:
		return new Coward(pos, id, players, blocking, fire, bomb, bonuses, communication);
	case 2:
		return new EasyHunter(pos, id, players, blocking, fire, bomb, bonuses, communication);
	case 3:
		return new Hunter(pos, id, players, blocking, fire, bomb, bonuses, communication);
	case 4:
		return new EasyAI(pos, id, players, blocking, fire, bomb, bonuses, communication);
	case 5:
		return new AI(pos, id, players, blocking, fire, bomb, bonuses, communication);
	default:
		return nullptr;
	}
}