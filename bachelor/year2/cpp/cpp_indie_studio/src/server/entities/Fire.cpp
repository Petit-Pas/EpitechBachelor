/*
** EPITECH PROJECT, 2021
** cpp_inidie_studio
** File description:
** internal functions
*/

#include <iostream>
#include "Fire.hpp"

Fire::Fire(const std::pair<float, float> &pos, int id) : AEntity(pos, Element::Type::FIRE, id),
	_tikTak(std::chrono::steady_clock::now()), _over(false), _canSpawnBonus(false)
{
}

bool Fire::isOver()
{
	return _over;
}

void Fire::update()
{
	const long diff = std::chrono::duration_cast<std::chrono::milliseconds>(
		std::chrono::steady_clock::now() - _tikTak).count();

	if (diff >= 2000) {
		_over = true;
	}
}

bool Fire::canSpawnBonus()
{
	return _canSpawnBonus;
}

void Fire::canNowSpawnBonus()
{
	_canSpawnBonus = true;
}
