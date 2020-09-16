/*
** EPITECH PROJECT, 2021
** cpp_indie_studio
** File description:
** internal functions
*/

#ifndef CPP_INDIE_STUDIO_SPEEDUP_HPP
# define CPP_INDIE_STUDIO_SPEEDUP_HPP

#include <utility>
#include "ABonus.hpp"

class SpeedUp : public ABonus {
public:
	SpeedUp(const std::pair<float, float> &, int id);

	void apply(Player *) override;
};

#endif //CPP_INDIE_STUDIO_SPEEDUP_HPP
