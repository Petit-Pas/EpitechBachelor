/*
** EPITECH PROJECT, 2021
** cpp_arcade
** File description:
** internal functions
*/

#include <cstdlib>
#include <iostream>
#include "textureBomberman.hpp"
#include "Mob.hpp"

ar::Mob::Mob(int posX, int posY) : _posX(posX), _posY(posY)
{
}

void ar::Mob::findPossibleWays(int *possibleWays, Map &map)
{
	int pos[][2] = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};

	for (int i = 0; i != 4; i++) {
		if (map[_posY + pos[i][1]][_posX + pos[i][0]] == EMPTY ||
			map[_posY + pos[i][1]][_posX + pos[i][0]] == PLAYER_UP ||
			map[_posY + pos[i][1]][_posX + pos[i][0]] == PLAYER_DOWN ||
			map[_posY + pos[i][1]][_posX + pos[i][0]] == PLAYER_LEFT ||
			map[_posY + pos[i][1]][_posX + pos[i][0]] == PLAYER_RIGHT ||
			map[_posY + pos[i][1]][_posX + pos[i][0]] == BONUS_EXPLOSION ||
			map[_posY + pos[i][1]][_posX + pos[i][0]] == BONUS_BOMB) {
			if (_posY + pos[i][1] == _oldY &&
				_posX + pos[i][0] == _oldX)
				possibleWays[i] = 1;
			else
				possibleWays[i] = 2;
		} else
			possibleWays[i] = 0;
	}
}

bool ar::Mob::live(Map &map)
{
	int possibleWays[4] = {0, 0, 0, 0};

	if (map[_posY][_posX] == EXPLOSION)
		return false;
	map[_posY][_posX] = EMPTY;
	findPossibleWays(possibleWays, map);
	_oldY = _posY;
	_oldX = _posX;
	if (amountOfHighPriority(possibleWays) >= 1)
		chooseHighPriority(possibleWays);
	else if (isLowPriority(possibleWays))
		goLowerPriority(possibleWays);
	map[_posY][_posX] = MOB;
	return true;
}

int ar::Mob::amountOfHighPriority(int *possibleWays)
{
	int res = 0;
	for (int i = 0; i != 4; i++) {
		if (possibleWays[i] == 2)
			res += 1;
	}
	return res;
}

void ar::Mob::chooseHighPriority(int *possibleWays)
{
	static int pos[][2] = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};
	int st = rand() % 4;
	int i = st + 1;

	if (i == 4)
		i = 0;
	while (st != i) {
		if (possibleWays[i] == 2) {
			_posX += pos[i][0];
			_posY += pos[i][1];
			return;
		}
		i += 1;
		if (i == 4)
			i = 0;
	}
}

bool ar::Mob::isLowPriority(int *possibleWays)
{
	for (int i = 0; i != 4; i++) {
		if (possibleWays[i] == 1)
			return true;
	}
	return false;
}

void ar::Mob::goLowerPriority(int *possibleWays)
{
	static int pos[][2] = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};

	for (int i = 0; i != 4; i++) {
		if (possibleWays[i] == 1) {
			_posX += pos[i][0];
			_posY += pos[i][1];
			return;
		}
	}
}
