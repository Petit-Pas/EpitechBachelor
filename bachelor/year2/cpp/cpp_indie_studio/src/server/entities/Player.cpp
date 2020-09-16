/*
** EPITECH PROJECT, 2018
** refactured_entities
** File description:
** Created by vincent,
*/
#include "Player.hpp"

Player::Player(const std::pair<float, float> &pos, int id) : AMovable(pos, Element::Type::PLAYER, id), _nbLives(1),
	_nbBombMax(1), _nbBombDrop(0), _firePower(1), _bombTimer(2000), _speed(0.1), _ghostWall(0), _isInAWall(false),
	_bigBomb(0), _idle(true), _idleSend(false)
{
	_state = Element::State::ALIVE;
}

void Player::bombAvailable()
{
	_nbBombDrop--;
}

bool Player::isBombAvailable() const
{
	return (_nbBombDrop < _nbBombMax);
}

bool Player::isBlocked(const std::pair<float, float> &pos, const std::vector<AEntity> &blocking,
	const std::vector<AEntity> &explosions
) const
{
	for (const auto &item : blocking) {
		if (item.isHitBigHitBox(pos)) {
			return true;
		}
	}
	for (const auto &item : explosions) {
		if (item.getType() == Element::Type::BOMB && item.isHitBigHitBox(pos)) {
			return true;
		}
	}
	return false;
}

void Player::checkDeath(const std::vector<std::unique_ptr<Fire>> &explosions)
{
	for (const auto &item : explosions) {
		if (item->getType() == Element::Type::FIRE && item->isHitBigHitBox(_pos)) {
			_nbLives--;
			if (_nbLives <= 0)
				_state = Element::State::DEAD;
			return;
		}
	}
}

void Player::checkBonus(std::vector<AEntity> &bonus)
{
	size_t i = 0;

	for (const auto &item : bonus) {
		if (item.isHitBigHitBox(_pos)) {
			// item->applyBonus(*this)
			bonus.erase(bonus.begin() + i);
		}
		i++;
	}
}

void Player::addBomb()
{
	_nbBombMax++;
}

void Player::addFirePower()
{
	_firePower++;
}

int Player::getFirePower() const
{
	return _firePower;
}

int Player::getAmountBombs()
{
	return _nbBombDrop;
}

int Player::getAmountBombsMax()
{
	return _nbBombMax;
}

int Player::getBombTimer()
{
	return _bombTimer;
}

float Player::getSpeed()
{
	return _speed;
}

void Player::incrementSpeed()
{
	_speed += 0.02;
}

void Player::removeBomb()
{
	_nbBombDrop += 1;
}

bool Player::canWalkThrough()
{
	if (_ghostWall != 0) {
		_ghostWall -= 1;
		return true;
	}
	return false;
}

void Player::addWalkThrough()
{
	_ghostWall += 1;
}

void Player::setInAWall(bool value)
{
	_isInAWall = value;
}

bool Player::isInAWall()
{
	return _isInAWall;
}

void Player::addBigBomb()
{
	_bigBomb += 1;
}

bool Player::hasBigBomb()
{
	if (_bigBomb != 0) {
		_bigBomb -= 1;
		return true;
	}
	return false;
}

void Player::setIdle()
{
	_idle = true;
}

void Player::unsetIdle()
{
	_idle = false;
	_idleSend = false;
}

void Player::setIdleSend()
{
	_idleSend = true;
}

bool Player::isIdle() const
{
	return _idle;
}

bool Player::isIdleSend() const
{
	return _idleSend;
}
