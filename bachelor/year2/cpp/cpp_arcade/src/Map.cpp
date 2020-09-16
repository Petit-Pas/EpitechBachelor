/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Internal functions
*/
#include "Map.hpp"

ar::Map::~Map()
{
	for (int i = 0; i < _height; ++i) {
		delete[] _map[i];
	}
	delete[] _map;
}

ar::Map::Map(int _width, int _height) : _height(_height), _width(_width),
	_playerPosX(0), _playerPosY(0)
{
	_map = new int *[_height + 1];
	for (int i = 0; i < _height; ++i) {
		_map[i] = new int[_width + 1];
		for (int j = 0; j < _width; ++j) {
			_map[i][j] = 0;
		}
		_map[i][_width] = 0;
	}
	_map[_height] = nullptr;
}

int ar::Map::getHeight() const
{
	return _height;
}

int ar::Map::getWidth() const
{
	return _width;
}

int *&ar::Map::operator[](int x)
{
	return _map[x];
}

int ar::Map::getPlayerX() const
{
	return _playerPosX;
}

int ar::Map::getPlayerY() const
{
	return _playerPosY;
}

void ar::Map::setPlayerY(int y)
{
	_playerPosY = y;
}

void ar::Map::setPlayerX(int x)
{
	_playerPosX = x;
}

