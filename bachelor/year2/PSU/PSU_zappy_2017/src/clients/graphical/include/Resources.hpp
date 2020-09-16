/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** Internal functions
*/

#ifndef ZAPPY_RESOURCE_HPP
# define ZAPPY_RESOURCE_HPP

#include <SFML/Graphics.hpp>

enum Resources {
	FOOD = 0,
	LINEMATE,
	DERAUMERE,
	SIBUR,
	MENDIANE,
	PHIRAS,
	THYSTAME
};

struct Resource {
	int quantity;
	sf::RectangleShape shape;
	sf::Texture *texture;
	sf::IntRect single;
	sf::IntRect multiple;
};

#endif //ZAPPY_RESOURCE_HPP
