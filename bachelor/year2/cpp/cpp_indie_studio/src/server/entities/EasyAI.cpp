/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Created by vincent,
*/

#include "EasyAI.hpp"

EasyAI::EasyAI(const std::pair<float, float> &pos, int id,
	std::shared_ptr<LockedItem<std::vector<std::unique_ptr<Player>>>> players,
	std::shared_ptr<LockedItem<std::vector<std::unique_ptr<AEntity>>>> blocking,
	std::shared_ptr<LockedItem<std::vector<std::unique_ptr<Fire>>>> fire,
	std::shared_ptr<LockedItem<std::vector<std::unique_ptr<Bomb>>>> bomb,
	std::shared_ptr<LockedItem<std::vector<std::unique_ptr<ABonus>>>> bonuses,
	std::shared_ptr<LockedItem<std::vector<PlayerCommunication>>> communication)
	: AI(pos, id, players, blocking, fire, bomb, bonuses, communication)
{}

void EasyAI::addBomb()
{
}