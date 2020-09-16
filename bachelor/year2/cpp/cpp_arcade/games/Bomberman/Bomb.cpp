/*
** EPITECH PROJECT, 2021
** cpp_arcade
** File description:
** internal functions
*/

#include <iostream>
#include "Bomb.hpp"
#include "textureBomberman.hpp"

ar::Bomb::Bomb(int posX, int posY, int power, int span) : _posX(posX),
	_posY(posY), _power(power), _span(span), _start(time(nullptr))
{
}

ar::Bomb::~Bomb()
{
}

bool ar::Bomb::live(Map &map)
{
	if (time(nullptr) - _start >= _span || map[_posY][_posX] == EXPLOSION) {
		explode(map);
		map[_posY][_posX] = EMPTY;
		return false;
	}
	map[_posY][_posX] = BOMB;
	return true;
}

int ar::Bomb::getPosX() const
{
	return _posX;
}

int ar::Bomb::getPosY() const
{
	return _posY;
}

int ar::Bomb::getPower() const
{
	return _power;
}

int ar::Bomb::getSpan() const
{
	return _span;
}

time_t ar::Bomb::getStart() const
{
	return _start;
}

void ar::Bomb::explodeOneDirection(int modifY, int modifX, Map &map, int now)
{
	int amount = 0;
	int toAddY = modifY;
	int toAddX = modifX;

	while (amount != _power) {
		if (map[_posY + modifY][_posX + modifX] == EMPTY ||
			map[_posY + modifY][_posX + modifX] == PLAYER_UP ||
			map[_posY + modifY][_posX + modifX] == PLAYER_DOWN ||
			map[_posY + modifY][_posX + modifX] == PLAYER_LEFT ||
			map[_posY + modifY][_posX + modifX] == PLAYER_RIGHT ||
			map[_posY + modifY][_posX + modifX] == BOMB ||
			map[_posY + modifY][_posX + modifX] == BONUS_BOMB ||
			map[_posY + modifY][_posX + modifX] == BONUS_EXPLOSION ||
			map[_posY + modifY][_posX + modifX] == EXPLOSION ||
			map[_posY + modifY][_posX + modifX] == MOB) {
			explosionT newOne = {_posX + modifX, _posY + modifY,
				now, EMPTY};
			_explosion.push_back(newOne);
		} else if (map[_posY + modifY][_posX + modifX] == BREAKABLE) {
			map[_posY + modifY][_posX + modifX] = EMPTY;
			explosionT newOne = {_posX + modifX, _posY + modifY,
				now, EXPLOSED_WALL};
			_explosion.push_back(newOne);
			_brokenWalls += 1;
			return;
		} else if (map[_posY + modifY][_posX + modifX] == WALL)
			return;
		amount += 1;
		modifY += toAddY;
		modifX += toAddX;
	}
}

void ar::Bomb::explode(Map &map)
{
	int pos[][2] = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};
	int now = static_cast<int>(time(nullptr));

	_brokenWalls = 0;
	for (int i = 0; i != 4; i++) {
		explodeOneDirection(pos[i][1], pos[i][0], map, now);
	}
	explosionT newOne = {_posX, _posY, now, EMPTY};
	_explosion.push_back(newOne);
}

std::vector<explosionT> ar::Bomb::getExplosion()
{
	return _explosion;
}

int ar::Bomb::getBrokenWalls()
{
	return _brokenWalls;
}

ar::Bomb ar::Bomb::operator=(const ar::Bomb &old)
{
	_posX = old.getPosX();
	_posY = old.getPosY();
	_power = old.getPower();
	_span = old.getSpan();
	_start = old.getStart();
	return *this;
}
