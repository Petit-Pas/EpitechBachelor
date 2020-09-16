/*
** EPITECH PROJECT, 2021
** cpp_arcade
** File description:
** internal functions
*/

#ifndef CPP_ARCADE_TEXTUREBOMBERMAN_HPP
# define CPP_ARCADE_TEXTUREBOMBERMAN_HPP

/*! This enum references all the possible texture*/
enum textureBomberman {
	EMPTY = 2, /*!< The texture representing a empty area */
	WALL = 3, /*!< The texture representing a wall area */
	PLAYER_UP = 4,
	PLAYER_DOWN = 5,
	PLAYER_LEFT = 6,
	PLAYER_RIGHT = 7,
	BREAKABLE = 8,
	BOMB = 9,
	EXPLOSION = 10,
	EXPLOSED_WALL = 11,
	BONUS_BOMB = 12,
	BONUS_EXPLOSION = 13,
	MOB = 14
};

typedef struct posS {
	int x;
	int y;
	int start;
	textureBomberman hidden;
} explosionT;

#endif //CPP_ARCADE_TEXTUREBOMBERMAN_HPP
