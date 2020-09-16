/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Created by vincent,
*/

#ifndef CPP_INDIE_STUDIO_COWARD_HPP
#define CPP_INDIE_STUDIO_COWARD_HPP

#include "AI.hpp"

class Coward : public AI {
public:
	Coward(const std::pair<float, float> &pos, int id, std::shared_ptr<LockedItem<std::vector<std::unique_ptr<Player>>>> players,
	std::shared_ptr<LockedItem<std::vector<std::unique_ptr<AEntity>>>> blocking,
	std::shared_ptr<LockedItem<std::vector<std::unique_ptr<Fire>>>> fire,
	std::shared_ptr<LockedItem<std::vector<std::unique_ptr<Bomb>>>> bomb,
	std::shared_ptr<LockedItem<std::vector<std::unique_ptr<ABonus>>>> bonuses,
	std::shared_ptr<LockedItem<std::vector<PlayerCommunication>>> communication);
	virtual ~Coward() = default;

	void updatePlayersOnMap() override;
	void addBomb() override;
	bool isGoodTimeToDropBomb() override;
	void compareGoalCells(node *node) override;
	void evaluateCellEscapes(node *node) override;

	private:
	unsigned char _lapsBetween2Drop;
};

#endif //CPP_INDIE_STUDIO_COWARD_HPP
