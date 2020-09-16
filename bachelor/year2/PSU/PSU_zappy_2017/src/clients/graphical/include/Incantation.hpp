/*
** EPITECH PROJECT, 2018
** Graphical
** File description:
** Created by martin.van-elslande@epitech.eu,
*/

#ifndef GRAPHICAL_INCANTATION_HPP
#define GRAPHICAL_INCANTATION_HPP

#include <SFML/Graphics.hpp>

enum IncantState {
	ON_HOLD,
	SUCCESS,
	FAILURE
};

struct Incantation {
	sf::Vector2i pos;
	int level;
	int incantator;
	std::vector<int> players;
	IncantState state;
};

#endif //GRAPHICAL_INCANTATION_HPP
