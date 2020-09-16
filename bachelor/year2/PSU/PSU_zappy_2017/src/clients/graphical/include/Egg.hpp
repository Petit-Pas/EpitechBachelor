/*
** EPITECH PROJECT, 2018
** Zappy
** File description:
** Created by martin.van-elslande@epitech.eu,
*/

#ifndef ZAPPY_EGG_HPP
#define ZAPPY_EGG_HPP

#include <string>
#include <SFML/Graphics.hpp>

struct Egg {
	int id;
	bool hatching;
	sf::Vector2i pos;
	std::string teamName;
	sf::RectangleShape shape;
	sf::Texture &texture;
};

#endif //ZAPPY_EGG_HPP
