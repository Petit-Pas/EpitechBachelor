/*
** EPITECH PROJECT, 2018
** refactured_entities
** File description:
** Created by vincent,
*/
#ifndef REFACTURED_ENTITIES_FIREUP_HPP
#define REFACTURED_ENTITIES_FIREUP_HPP

#include "Player.hpp"
#include "ABonus.hpp"

class FireUp : public ABonus {
public:
	FireUp(const std::pair<float, float> &, int id);

	void apply(Player *) override;
};

#endif //REFACTURED_ENTITIES_FIREUP_HPP
