//
// EPITECH PROJECT, 2018
// zappy
// File description:
// methods of movement
//

#include <cstdlib>
#include "Movement.hpp"

Orientation::Orientation(Direction i) : _i(static_cast<int>(i) % 4), DIRECTIONS({{0, -1}, {-1, 0}, {0, 1}, {1, 0}})
{
	if (_i < 0)
		_i = 0;
}

Orientation::Orientation(int orient) : DIRECTIONS({{0, -1}, {-1, 0}, {0, 1}, {1, 0}})
{
	_i = 6 - (orient + 1) / 2;
	if (_i < 0)
		_i = 0;
	if (_i > 3)
		_i = _i % 4;
}

Orientation &Orientation::operator+=(int nb)
{
	_i += nb;
	if (_i < 0)
		_i += 4 * (-1 * _i / 4 + 1);
	if (static_cast<size_t>(_i) >= 4)
		_i = _i % 4;
	return (*this);
}

Orientation &Orientation::operator++(int)
{
	_i += 1;
	if (static_cast<size_t>(_i) >= 4)
		_i = _i % 4;
	return (*this);
}

Orientation &Orientation::operator--(int)
{
	_i -= 1;
	if (_i < 0)
		_i += 4;
	return (*this);
}

bool Orientation::operator==(const Orientation &sec) const
{
	return (_i == sec.getIndex());
}

Orientation &Orientation::operator=(const Orientation &sec)
{
	_i = sec.getIndex();
	return (*this);
}

std::size_t Orientation::getNbMovements(const Position &pos, const Position &target, const ElementMap &map) const
{
	auto dir = getDir();
	auto newTarget = target;

	if (newTarget.x < 0)
		newTarget.x += map.getSize().width;
	if (newTarget.y < 0)
		newTarget.y += map.getSize().height;
	if (dir.x != 0) {
		if ((newTarget.x - pos.x) * dir.x >= 0)
			return ((newTarget.x - pos.x) / dir.x);
		else if (newTarget.x - pos.x < 0 && dir.x > 0) {
			return (newTarget.x + static_cast<int>(map.getSize().width - pos.x) / dir.x);
		} else {
			return ((newTarget.x - (pos.x + static_cast<int>(map.getSize().width))) / dir.x);
		}
	}
	if ((newTarget.y - pos.y) * dir.y >= 0) {
		return ((newTarget.y - pos.y) / dir.y);
	} else if (newTarget.y - pos.y < 0 && dir.y > 0) {
		return (newTarget.y + static_cast<int>(map.getSize().height - pos.y) / dir.y);
	} else {
		return ((newTarget.y - (pos.y + static_cast<int>(map.getSize().height))) / dir.y);
	}
}

const Position &Orientation::getDir() const
{
	return (DIRECTIONS[_i]);
}

int Orientation::getIndex() const
{
	return (_i);
}

Position &Position::operator=(const Orientation &orientation)
{
	x = orientation.getDir().x;
	y = orientation.getDir().y;
	return (*this);
}

Position &Position::operator()(const Orientation &orientation)
{
	x = orientation.getDir().x;
	y = orientation.getDir().y;
	return (*this);
}

Position &Position::operator+=(const Orientation &orientation)
{
	const auto &dir = orientation.getDir();
	x += dir.x;
	y += dir.y;
	return (*this);
}

Position Position::operator+(const Orientation &orientation) const
{
	Position newPos = {y, x};
	const auto &dir = orientation.getDir();

	newPos.x += dir.x;
	newPos.y += dir.y;
	return (newPos);
}

Position &Position::operator+=(const Position &dir)
{
	x += dir.x;
	y += dir.y;
	return (*this);
}

Position Position::operator+(const Position &dir) const
{
	Position newPos = {y, x};

	newPos.x += dir.x;
	newPos.y += dir.y;
	return (newPos);
}

Position Position::operator*(const int i) const
{
	/**
	 * y and x are not set
	 */
	Position newPos = {y * i, x * i};

	return (newPos);
}

bool Position::operator!=(const Position &pos) const
{
	return (!(pos == *this));
}

bool Position::operator==(const Position &pos) const
{
	return (pos.x == x && pos.y == y);
}

void Position::scaleToMap(const ElementMap &map)
{
	if (y < 0)
		y += map.getSize().height;
	if (x < 0)
		x += map.getSize().width;
	if (static_cast<size_t>(x) >= map.getSize().width)
		x = x % map.getSize().width;
	if (static_cast<size_t>(y) >= map.getSize().height)
		y = y % map.getSize().height;
}

std::ostream &operator<<(std::ostream &os, const Position &pos)
{
	os << "y:" << pos.y << ", x:" << pos.x;
	return (os);
}

std::ostream &operator<<(std::ostream &os, const Orientation &ori)
{
	os << ori.getDir();
	return (os);
}
