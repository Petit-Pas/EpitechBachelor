/*
** EPITECH PROJECT, 2021
** cpp_indie_studio
** File description:
** internal functions
*/

#include "SpeedUp.hpp"

SpeedUp::SpeedUp(const std::pair<float, float> &pos, int id) : ABonus(pos, id, Element::Type::SPEED_UP)
{
}

void SpeedUp::apply(Player *player)
{
	player->incrementSpeed();
}
