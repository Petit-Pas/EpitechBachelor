/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Created by vincent,
*/

#ifndef CPP_INDIE_STUDIO_AIFACTORY_HPP
#define CPP_INDIE_STUDIO_AIFACTORY_HPP

#include "AI.hpp"
#include "Hunter.hpp"
#include "EasyHunter.hpp"
#include "EasyAI.hpp"
#include "Coward.hpp"

class AIFactory {
public:
	static AI *getAI(ind::ia::Types type, const std::pair<float, float> &pos, int id, std::shared_ptr<LockedItem<std::vector<std::unique_ptr<Player>>>> players,
	std::shared_ptr<LockedItem<std::vector<std::unique_ptr<AEntity>>>> blocking,
	std::shared_ptr<LockedItem<std::vector<std::unique_ptr<Fire>>>> fire,
	std::shared_ptr<LockedItem<std::vector<std::unique_ptr<Bomb>>>> bomb,
	std::shared_ptr<LockedItem<std::vector<std::unique_ptr<ABonus>>>> bonuses,
	std::shared_ptr<LockedItem<std::vector<PlayerCommunication>>> communication);
};

#endif //CPP_INDIE_STUDIO_AIFACTORY_HPP
