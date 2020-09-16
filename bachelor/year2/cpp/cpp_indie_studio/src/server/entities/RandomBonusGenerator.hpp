/*
** EPITECH PROJECT, 2021
** cpp_indie_studio
** File description:
** internal functions
*/

#ifndef CPP_INDIE_STUDIO_RANDOMBONUSGENERATOR_HPP
# define CPP_INDIE_STUDIO_RANDOMBONUSGENERATOR_HPP

#include "ABonus.hpp"

class RandomBonusGenerator {
public:
	static ABonus *getRandomBonus(const std::pair<float, float> &pos, int id);
};

#endif //CPP_INDIE_STUDIO_RANDOMBONUSGENERATOR_HPP
