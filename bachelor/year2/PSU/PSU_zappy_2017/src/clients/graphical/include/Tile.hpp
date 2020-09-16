/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** Internal functions
*/

#ifndef ZAPPY_TILE_HPP
# define ZAPPY_TILE_HPP

#include <SFML/Graphics.hpp>

struct Tile {
	sf::Vector2i pos;
	std::map<int, Resource> resources;
	sf::RectangleShape shape;
	sf::FloatRect hitbox;
	sf::Texture &texture;
	sf::Texture &textureIncantation;
};

#endif //ZAPPY_TILE_HPP
