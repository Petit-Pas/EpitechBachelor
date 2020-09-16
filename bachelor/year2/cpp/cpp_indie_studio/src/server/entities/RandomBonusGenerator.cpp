/*
** EPITECH PROJECT, 2021
** cpp_indie_studio
** File description:
** internal functions
*/

#include <cstdlib>
#include <iostream>
#include "RandomBonusGenerator.hpp"
#include "SpeedUp.hpp"
#include "PassThrough.hpp"
#include "BonusBigBomb.hpp"
#include "FireUp.hpp"
#include "BombUp.hpp"

ABonus *RandomBonusGenerator::getRandomBonus(const std::pair<float, float> &pos, int id)
{
	switch (rand() % 5) {
	case 0:
		return new FireUp(pos, id);
	case 1:
		return new BombUp(pos, id);
	case 2:
		return new SpeedUp(pos, id);
	case 3:
		return new PassThrough(pos, id);
	default:
		return new BonusBigBomb(pos, id);
	}
}
