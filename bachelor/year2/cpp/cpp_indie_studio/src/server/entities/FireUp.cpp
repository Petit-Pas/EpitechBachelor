/*
** EPITECH PROJECT, 2018
** refactured_entities
** File description:
** Created by vincent,
*/
#include "FireUp.hpp"

FireUp::FireUp(const std::pair<float, float> &pos, int id) : ABonus(pos, id, Element::Type::FIRE_UP)
{
}

void FireUp::apply(Player *player)
{
	player->addFirePower();
}
