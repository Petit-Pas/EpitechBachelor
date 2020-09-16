/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Created by vincent.larcher@epitech.eu,
*/

#include <cmath>
#include <iostream>
#include "AEntity.hpp"

AEntity::AEntity(const std::pair<float, float> &pos, const Element::Type type, const int id) : _id(id), _type(type),
	_state(Element::State::NONE), _pos(pos),
	_hitboxY(std::pair<float, float>(floorf(_pos.first), roundf(_pos.first))),
	_hitboxX(std::pair<float, float>(floorf(_pos.second), roundf(_pos.second)))
{
}

const std::pair<float, float> &AEntity::getPos() const
{
	return _pos;
}

Element::Type AEntity::getType() const
{
	return _type;
}

Element::State AEntity::getState() const
{
	return _state;
}

void AEntity::setState(const Element::State &state)
{

	_state = state;
}

int AEntity::getId() const
{
	return _id;
}

bool AEntity::isHitBigHitBox(std::pair<float, float> pos) const
{
	return (pos.first > _hitboxY.first - 0.25f && pos.first < _hitboxY.second + 0.25f &&
		pos.second > _hitboxX.first - 0.25f && pos.second < _hitboxX.second + 0.25f);
}

bool AEntity::isHitNormalHitBox(std::pair<float, float> pos) const
{
	return (pos.first > _hitboxY.first && pos.first < _hitboxY.second && pos.second > _hitboxX.first &&
		pos.second < _hitboxX.second);
}

packageServerClient AEntity::entityToPackage(const PackageType &type)
{
	return {type, 0, _id, _pos.first, _pos.second, 0, static_cast<int>(_type), static_cast<int>(_state)};
}

