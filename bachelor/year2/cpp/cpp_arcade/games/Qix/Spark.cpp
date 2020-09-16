/*
** EPITECH PROJECT, 2021
** cpp_arcade
** File description:
** internal functions
*/

#include <unistd.h>
#include <iostream>
#include "Spark.hpp"

ar::Spark::~Spark()
{
	_map[_y][_x] = BORDER;
}

ar::Spark::Spark(Map &map, int posX, int posY, int oldX, int oldY) : _x(posX), _y(posY), _prevY(oldY), _prevX(oldX),
	_map(map)
{
}

void ar::Spark::getSurroundingContent(ar::TextureQix *around)
{
	static int pos[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

	for (int i = 0; i != 4; i += 1)
		if (_y + pos[i][1] >= 0 && _y + pos[i][1] < _map.getHeight() && _x + pos[i][0] >= 0 &&
			_x + pos[i][0] <= _map.getWidth() && !(_y + pos[i][1] == _prevY && _x + pos[i][0] == _prevX))
			if ((_map[_y + pos[i][1]][_x + pos[i][0]] == ar::TextureQix::BORDER ||
				_map[_y + pos[i][1]][_x + pos[i][0]] == ar::TextureQix::PLAYER ||
				_map[_y + pos[i][1]][_x + pos[i][0]] == ar::TextureQix::SPARK1 ||
				_map[_y + pos[i][1]][_x + pos[i][0]] == ar::TextureQix::SPARK2 ||
				_map[_y + pos[i][1]][_x + pos[i][0]] == ar::TextureQix::WALL))
				around[i] = static_cast<ar::TextureQix>
				(_map[_y + pos[i][1]][_x + pos[i][0]]);
}

void ar::Spark::validateNewPos(int addonX, int addonY)
{
	TextureQix toPut = SPARK1;
	if (_map[_y][_x] == SPARK1)
		toPut = SPARK2;
	_map[_y][_x] = ar::TextureQix::WALL;
	_map[_y + addonY][_x + addonX] = toPut;
	_prevY = _y;
	_prevX = _x;
	_y += addonY;
	_x += addonX;
}

bool ar::Spark::checkHighPriorityMove(ar::TextureQix *around)
{
	static int pos[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

	for (int i = 0; i != 4; i += 1) {
		if (around[i] != 0 && around[i] != ar::TextureQix::WALL) {
			validateNewPos(pos[i][0], pos[i][1]);
			return true;
		}
	}
	return false;
}

int ar::Spark::countPossibleWays(ar::TextureQix *around)
{
	int count = 0;

	for (int i = 0; i != 4; i += 1) {
		if (around[i] == ar::TextureQix::WALL)
			count += 1;
	}
	return count;
}

void ar::Spark::validateFirstWay(ar::TextureQix *around)
{
	static int pos[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

	for (int i = 0; i != 4; i += 1) {
		if (around[i] != 0) {
			validateNewPos(pos[i][0], pos[i][1]);
			return;
		}
	}
}

void ar::Spark::pushCell(int x, int y, int depth, std::vector<ar::Spark::coordSpark> &toFill
)
{
	coordSpark toAdd{x, y};

	_map[y][x] = depth;
	toFill.push_back(toAdd);
}

ar::Spark::coordSpark ar::Spark::findClosestBorder(std::vector<ar::Spark::coordSpark> &oldSet)
{
	static int pos[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
	std::vector<coordSpark> newSet;
	int depth = -3;

	while (1) {
		newSet = {};
		for (auto &it : oldSet) {
			for (int i = 0; i != 4; i += 1) {
				if (checkIfCellIsInside(it.x + pos[i][0], it.y + pos[i][1]) == true &&
					_map[it.y + pos[i][1]][it.x + pos[i][0]] == ar::TextureQix::WALL) {
					pushCell(it.x + pos[i][0], it.y + pos[i][1], depth, newSet);
				} else if (checkIfCellIsInside(it.x + pos[i][0], it.y + pos[i][1]) == true &&
					_map[it.y + pos[i][1]][it.x + pos[i][0]] == ar::TextureQix::BORDER) {
					_map[it.y + pos[i][1]][it.x + pos[i][0]] = depth;
					return {it.x + pos[i][0], it.y + pos[i][1]};
				}
			}
		}
		depth -= 1;
		oldSet = newSet;
	}
}

void ar::Spark::pathfindToBorder(ar::TextureQix *around)
{
	std::vector<coordSpark> starts;
	static int pos[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

	_map[_y][_x] = -1;
	for (int i = 0; i != 4; i += 1) {
		if (around[i] == ar::TextureQix::WALL || around[i] == ar::TextureQix::SPARK1 ||
			around[i] == ar::TextureQix::SPARK2) {
			coordSpark coord;
			coord.x = _x + pos[i][0];
			coord.y = _y + pos[i][1];
			_map[coord.y][coord.x] = -2;
			starts.push_back(coord);
		}
	}
	coordSpark closest = findClosestBorder(starts);
	goBack(closest);
	erasePathfind();
}

void ar::Spark::doLowPriorityMove(ar::TextureQix *around)
{
	int count = countPossibleWays(around);

	if (count == 1)
		validateFirstWay(around);
	else
		pathfindToBorder(around);
}

void ar::Spark::live()
{
	ar::TextureQix around[4] = {};

	getSurroundingContent(around);
	if (!checkHighPriorityMove(around))
		doLowPriorityMove(around);
}

bool ar::Spark::checkIfCellIsInside(int x, int y)
{
	return (x >= 0 && x <= _map.getWidth() && y >= 0 && y < _map.getHeight());
}

void ar::Spark::erasePathfind()
{
	int y = 0;
	int x = 0;

	while (y != _map.getHeight()) {
		x = 0;
		while (x != _map.getWidth() + 1) {
			if (_map[y][x] < 0)
				_map[y][x] = ar::TextureQix::WALL;
			x += 1;
		}
		y += 1;
	}
}

void ar::Spark::dump()
{
	int y = 0;
	int x = 0;

	while (y != _map.getHeight()) {
		x = 0;
		while (x != _map.getWidth() + 1) {
			dprintf(2, "[%3i]", (int)_map[y][x]);
			x += 1;
		}
		y += 1;
		dprintf(2, "\n");
	}
}

void ar::Spark::goBack(ar::Spark::coordSpark closest)
{
	int y = closest.y;
	int x = closest.x;
	static int pos[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

	while (_map[y][x] != -2) {
		for (int i = 0; i != 4; i += 1) {
			if (checkIfCellIsInside(x + pos[i][0], y + pos[i][1]) &&
				_map[y + pos[i][1]][x + pos[i][0]] == _map[y][x] + 1) {
				y += pos[i][1];
				x += pos[i][0];
				break;
			}
		}
	}
	TextureQix toPut = SPARK1;
	if (_map[_prevY][_prevX] == SPARK1)
		toPut = SPARK2;
	_prevY = _y;
	_prevX = _x;
	_x = x;
	_y = y;
	_map[y][x] = toPut;
}
