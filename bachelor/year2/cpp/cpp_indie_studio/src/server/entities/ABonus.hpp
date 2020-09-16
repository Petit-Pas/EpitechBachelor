/*
** EPITECH PROJECT, 2021
** cpp_indie_studio
** File description:
** internal functions
*/

#ifndef CPP_INDIE_STUDIO_ABONUS_HPP
# define CPP_INDIE_STUDIO_ABONUS_HPP

#include "AEntity.hpp"
#include "Player.hpp"

class ABonus : public AEntity {
public:
	ABonus(const std::pair<float, float> &pos, int id, Element::Type kind);
	virtual void apply(Player *player);
private:
};

#endif //CPP_INDIE_STUDIO_ABONUS_HPP
