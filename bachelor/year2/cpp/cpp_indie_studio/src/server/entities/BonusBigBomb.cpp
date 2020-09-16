/*
** EPITECH PROJECT, 2021
** cpp_indie_studio
** File description:
** internal functions
*/

#include "BonusBigBomb.hpp"
#include "Element.hpp"

BonusBigBomb::BonusBigBomb(const std::pair<float, float> &pos, int id) : ABonus(pos, id, Element::Type::PIERCE_BOMB)
{
}

void BonusBigBomb::apply(Player *player)
{
	player->addBigBomb();
}
