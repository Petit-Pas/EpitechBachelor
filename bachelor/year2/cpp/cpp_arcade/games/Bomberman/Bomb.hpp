/*
** EPITECH PROJECT, 2021
** cpp_arcade
** File description:
** internal functions
*/

#ifndef CPP_ARCADE_BOMB_HPP
# define CPP_ARCADE_BOMB_HPP

#include "Map.hpp"
#include "textureBomberman.hpp"
#include <vector>
#include <ctime>

namespace ar {
	class Bomb {
	public:
		Bomb(int posX, int posY, int power, int span);
		Bomb operator=(const Bomb &old);

		Bomb();

		~Bomb();

		void explode(Map &map);
		void explodeOneDirection(int modifY, int modifX, Map &map, int now);
		bool live(Map &map);
		std::vector<explosionT> getExplosion();
		int getBrokenWalls();

	private:
		int _posX;
	public:
		int getPosX() const;

		int getPosY() const;

		int getPower() const;

		int getSpan() const;

		time_t getStart() const;

	private:
		int _posY;
		int _power;
		int _span;
		time_t _start;
		std::vector<explosionT> _explosion;
		int _brokenWalls;
	};
};

#endif //CPP_ARCADE_BOMB_HPP
