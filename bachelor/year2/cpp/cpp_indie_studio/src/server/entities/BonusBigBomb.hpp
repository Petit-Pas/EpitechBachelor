/*
** EPITECH PROJECT, 2021
** cpp_indie_studio
** File description:
** internal functions
*/

#ifndef CPP_INDIE_STUDIO_BONUSBIGBOMB_HPP
# define CPP_INDIE_STUDIO_BONUSBIGBOMB_HPP

#include "ABonus.hpp"

class BonusBigBomb : public ABonus {
public:
	BonusBigBomb(const std::pair<float, float> &pos, int id);
	void apply(Player *player) override;
};

#endif //CPP_INDIE_STUDIO_BONUSBIGBOMB_HPP
