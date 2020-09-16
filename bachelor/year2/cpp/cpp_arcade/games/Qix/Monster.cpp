/*
** EPITECH PROJECT, 2021
** cpp_arcade
** File description:
** internal functions
*/

#include <stdlib.h>
#include <iostream>
#include "Monster.hpp"
#include "TextureQix.hpp"
ar::Monster::Monster(ar::Map &map) : _map(map)
{
	_body.push_back({21, 18, QIXHEAD});

	_body.push_back({20, 19, QIXBODY1});
	_body.push_back({21, 19, QIXBODY2});
	_body.push_back({22, 19, QIXBODY3});

	_body.push_back({19, 20, QIXARMLEFT});
	_body.push_back({20, 20, QIXBODY4});
	_body.push_back({21, 20, QIXBODY5});
	_body.push_back({22, 20, QIXBODY6});
	_body.push_back({23, 20, QIXARMRIGHT});

	_body.push_back({20, 21, QIXBODY7});
	_body.push_back({21, 21, QIXBODY8});
	_body.push_back({22, 21, QIXBODY9});

	_body.push_back({20, 22, QIXLEGLEFT});
	_body.push_back({22, 22, QIXLEGRIGHT});
}

bool ar::Monster::checkIfCellIsInside(int x, int y)
{
	return (x >= 0 && y >= 0 && y < _map.getHeight() && x < _map.getWidth());
}

bool ar::Monster::live()
{
	static int pos[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
	int i = rand() % 4;

	if (hitsPlayer(pos[i][0], pos[i][1]))
		return false;
	if (checkMove(pos[i][0], pos[i][1]))
		validateMove(pos[i][0], pos[i][1]);
	if (rand() % 2 == 0) {
		if (hitsPlayer(pos[i][0], pos[i][1]))
			return false;
		if (checkMove(pos[i][0], pos[i][1]))
			validateMove(pos[i][0], pos[i][1]);
	}
	return true;
}

void ar::Monster::putMonster()
{
	for (auto &it : _body) {
		_map[it.y][it.x] = it.texture;
	}
}

void ar::Monster::validateMove(int x, int y)
{
	for (auto it : _body) {
		_map[it.y][it.x] = ar::TextureQix::EMPTY;
	}
	for (auto &it : _body) {
		it.y += y;
		it.x += x;
		_map[it.y][it.x] = it.texture;
	}
}

bool ar::Monster::hitsPlayer(int x, int y)
{
	for (auto it : _body) {
		if (checkIfCellIsInside(it.x + x, it.y + y) && (_map[it.y + y][it.x + x] == ar::TextureQix::PLAYER
			|| _map[it.y + y][it.x + x] == ar::TextureQix::TRAIL || _map[it.y + y][it.x + x] == ar::TextureQix::FLAME1
			|| _map[it.y + y][it.x + x] == ar::TextureQix::FLAME2)) {
            if (_map[it.y + y][it.x + x] == ar::TextureQix::PLAYER && checkPlayerOnBorder(it.y + y, it.x + x))
                return false;
            return true;
        }
	}
	return false;
}

bool ar::Monster::checkMove(int x, int y)
{
	for (auto it : _body) {
		if (checkIfCellIsInside(it.x + x, it.y + y) &&
			(_map[it.y + y][it.x + x] == ar::TextureQix::BORDER
				|| _map[it.y + y][it.x + x] == ar::TextureQix::SPARK1
				|| _map[it.y + y][it.x + x] == ar::TextureQix::SPARK2
			 || _map[it.y + y][it.x + x] == ar::TextureQix::PLAYER)) {
			return false;
		}
	}
	return true;
}

bool ar::Monster::checkPlayerOnBorder(int y, int x) {
	static int pos[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
	int amount = 0;

	for (int i = 0; i != 4; i += 1)
		if (checkIfCellIsInside(x + pos[i][0], y + pos[i][1]) && _map[y + pos[i][1]][x + pos[i][0]])
			amount += 1;
	if (amount == 2)
		return true;
	return false;
}
