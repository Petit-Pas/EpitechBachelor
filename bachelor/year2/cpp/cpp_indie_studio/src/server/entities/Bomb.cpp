/*
** EPITECH PROJECT, 2021
** cpp_inidie_studio
** File description:
** internal functions
*/

#include <chrono>
#include <cmath>
#include <iostream>
#include "Bomb.hpp"
#include "Breakable.hpp"

Bomb::Bomb(std::pair<float, float> pos, int radius, int explosionTimer, int idPlayer, int id, bool isBig) : AEntity(pos,
	Element::Type::BOMB, id), _radius(radius), _time(explosionTimer), _idPlayer(idPlayer), _isExploded(false),
	_tikTak(std::chrono::steady_clock::now()), _isBig(isBig)
{
}

void Bomb::update()
{
	const long diff = std::chrono::duration_cast<std::chrono::milliseconds>(
		std::chrono::steady_clock::now() - _tikTak).count();

	if (diff >= _time) {
		_isExploded = true;
	}
}

bool Bomb::isOver()
{
	return _isExploded;
}

void Bomb::forceExplosion()
{
	_isExploded = true;
}

std::vector<Fire> Bomb::getFire(const std::vector<std::unique_ptr<AEntity>> &blocking, int &id)
{
	std::vector<Fire> result;
	Fire newOne(std::pair<float, float>(_pos.first, _pos.second), id + 1);
	id += 1;

	result.push_back(newOne);
	getFire(blocking, 1, 0, result, id);
	getFire(blocking, -1, 0, result, id);
	getFire(blocking, 0, 1, result, id);
	getFire(blocking, 0, -1, result, id);
	id += 1;
	return result;
}

std::vector<Fire> Bomb::getFire(const std::vector<std::unique_ptr<AEntity>> &blocking, const int xModifier,
	const int yModifier, std::vector<Fire> &toFill, int &id
)
{
	float newX = _pos.second + xModifier;
	float newY = _pos.first + yModifier;
	int amount = 0;
	int found = 0;

	while (amount != _radius) {
		found = 0;
		for (auto &item : blocking) {
			if (item->isHitBigHitBox(std::pair<float, float>(newY, newX))) {
				if (item->getType() == Element::Type::SOFTWALL) {
					found = 1;
					Fire newFire(std::pair<float, float>(newY, newX), id + 1);
					id += 1;
					newFire.canNowSpawnBonus();
					toFill.push_back(newFire);
					if (_isBig)
						break;
				}
				return toFill;
			}
		}
		if (found != 1) {
			Fire newFire(std::pair<float, float>(newY, newX), id + 1);
			id += 1;
			toFill.push_back(newFire);
		}
		newX += xModifier;
		newY += yModifier;
		amount += 1;
	}
	return toFill;
}

int Bomb::getPlayerId()
{
	return _idPlayer;
}

bool Bomb::isBig()
{
	return _isBig;
}

int Bomb::getRadius() const
{
	return _radius;
}

unsigned short Bomb::getPercentageBeforeExplosion() const
{
	return static_cast<uint8_t>(
		(std::chrono::duration_cast<std::chrono::milliseconds>(
			std::chrono::steady_clock::now() - _tikTak).count()) /
			(_time / 100));
}