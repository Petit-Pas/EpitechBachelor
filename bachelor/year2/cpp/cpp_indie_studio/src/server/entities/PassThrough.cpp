/*
** EPITECH PROJECT, 2021
** cpp_indie_studio
** File description:
** internal functions
*/

#include "PassThrough.hpp"

PassThrough::PassThrough(const std::pair<float, float> &pos, int id) : ABonus(pos, id, Element::Type::WALK_THROUGH)
{
}

void PassThrough::apply(Player *player)
{
	player->addWalkThrough();
}
