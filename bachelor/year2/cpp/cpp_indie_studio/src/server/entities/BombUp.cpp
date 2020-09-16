/*
** EPITECH PROJECT, 2018
** refactured_entities
** File description:
** Created by vincent,
*/

#include "BombUp.hpp"

BombUp::BombUp(const std::pair<float, float> &pos, int id) : ABonus(pos, id, Element::Type::BOMB_UP)
{
}

void BombUp::apply(Player *player)
{
	player->addBomb();
}
