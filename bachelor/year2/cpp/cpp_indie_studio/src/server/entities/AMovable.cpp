/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Created by vincent.larcher@epitech.eu,
*/

#include <iostream>
#include <cmath>
#include <Direction.hpp>
#include "AMovable.hpp"

AMovable::AMovable(const std::pair<float, float> &pos, Element::Type type, int id) : AEntity(pos, type, id),
	_dirVector(0, 0), _dir(dir::DOWN)
{
	setPos(pos);
}

const std::pair<float, float> &AMovable::getDirVector() const
{
	return _dirVector;
}

void AMovable::setDirVector(float y, float x)
{
	_dirVector.first = y;
	_dirVector.second = x;
}

void AMovable::setDirVector(const std::pair<float, float> &dir)
{
	_dirVector.first = dir.first;
	_dirVector.second = dir.second;
}

void AMovable::setPos(const std::pair<float, float> &pos)
{
	_pos.first = pos.first;
	_pos.second = pos.second;
	_hitboxY.first = floorf(_pos.first) + 0.1f;
	_hitboxY.second = roundf(_pos.first) - 0.1f;
	_hitboxX.first = floorf(_pos.second) + 0.1f;
	_hitboxX.second = roundf(_pos.second) - 0.1f;
}

void AMovable::setDir(int dir)
{
	_dir = dir;
}

int AMovable::getDir()
{
	return _dir;
}

packageServerClient AMovable::entityToPackage(const PackageType &type)
{
	return {type, 0, _id, _pos.first, _pos.second, _dir, static_cast<int>(_type), static_cast<int>(_state)};
}
