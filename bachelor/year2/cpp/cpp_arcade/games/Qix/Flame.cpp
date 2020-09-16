/*
** EPITECH PROJECT, 2021
** cpp_arcade
** File description:
** internal functions
*/

#include <stdio.h>
#include <cstdlib>
#include "Flame.hpp"
#include "TextureQix.hpp"

ar::Flame::Flame(ar::Map &map, int y, int x) : _map(map), _x(x), _y(y), _prevX(-1), _prevY(-1), _texture(FLAME1)
{
	goBack();
}

ar::Flame::~Flame()
{
	_map[_y][_x] = TRAIL;
}

void ar::Flame::goBack()
{
	static int pos[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
	int prevX = -1;
	int prevY = -1;

	while (_map[_y][_x] != BORDER && _map[_y][_x] != SPARK1 && _map[_y][_x] != SPARK2) {
		for (int i = 0; i != 4; i += 1) {
			if (checkIfCellIsInside(_x + pos[i][0], _y + pos[i][1])
				&& !(_x + pos[i][0] == prevX && _y + pos[i][1] == prevY)
				&& _map[_y + pos[i][1]][_x + pos[i][0]] == TRAIL) {
				prevX = _x;
				prevY = _y;
				_y += pos[i][1];
				_x += pos[i][0];
				break;
			} else if (checkIfCellIsInside(_x + pos[i][0], _y + pos[i][1])
				&& (_map[_y + pos[i][1]][_x + pos[i][0]] == BORDER
				|| _map[_y + pos[i][1]][_x + pos[i][0]] == SPARK1
				|| _map[_y + pos[i][1]][_x + pos[i][0]] == SPARK2)) {
				_y += pos[i][1];
				_x += pos[i][0];
				break;
			}
		}
	}
}

bool ar::Flame::checkIfCellIsInside(int x, int y)
{
	return (x >= 0 && x <= _map.getWidth() && y >= 0 && y <= _map.getHeight());
}

bool ar::Flame::live()
{
	static int pos[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

	_texture = (_texture == FLAME1 ? FLAME2 : FLAME1);
	if (_prevX != -1)
		_map[_y][_x] = TRAIL;
	for (int i = 0; i != 4; i += 1) {
		if (checkIfCellIsInside(_x + pos[i][0], _y + pos[i][1])
			&& !(_x + pos[i][0] == _prevX && _y + pos[i][1] == _prevY)
			&& _map[_y + pos[i][1]][_x + pos[i][0]] == TRAIL) {
			_prevX = _x;
			_prevY = _y;
			_y += pos[i][1];
			_x += pos[i][0];
			_map[_y][_x] = _texture;
			return false;
		} else if (checkIfCellIsInside(_x + pos[i][0], _y + pos[i][1])
			&& !(_x + pos[i][0] == _x && _y + pos[i][1] == _y)
			&& _map[_y + pos[i][1]][_x + pos[i][0]] == PLAYER) {
			_prevX = _x;
			_prevY = _y;
			_y += pos[i][1];
			_x += pos[i][0];
			_map[_y][_x] = _texture;
			return true;
		}
	}
	return false;
}
