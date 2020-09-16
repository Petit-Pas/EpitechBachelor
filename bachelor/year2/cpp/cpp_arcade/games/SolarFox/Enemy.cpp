/*
** EPITECH PROJECT, 2018
** Arcade
** File description:
** SolarFox Vessel
*/

#include "Enemy.hpp"

ar::Enemy::Enemy(pos_t pos, int max, Map *map, int text)
	: _posX(pos.posX), _posY(pos.posY), _max(max - 2), _dir(pos.dir),
	  _map(map), _texture(text), _shoot(false), _missil({0, 0, AR_UNKNOWN, EMPTY})
{
	int next[2] = {_dir == AR_RIGHT || _dir == AR_LEFT,
		_dir == AR_UP || _dir == AR_DOWN};

	_old= (*map)[_posY][_posX];
	(*map)[_posY][_posX] = _texture;
	(*map)[_posY + next[1]][_posX + next[0]] = _texture + 1;
}

ar::Enemy::pos_t ar::Enemy::getPos()
{
	pos_t pos = {_posX, _posY, _dir, EMPTY};
	return pos;
}

void ar::Enemy::shoot()
{
	if (!_shoot) {
		Event dir = AR_UNKNOWN;
		_shoot = true;
		if (_missil.dir == AR_UNKNOWN) {
			dir = AR_DOWN;
			if (_dir == AR_RIGHT || _dir == AR_LEFT)
				dir = (_dir == AR_RIGHT) ? AR_DOWN : AR_UP;
			else if (_dir == AR_UP || _dir == AR_DOWN)
				dir = (_dir == AR_UP) ? AR_LEFT : AR_RIGHT;
		} else
			dir = _missil.dir;
		_missil = (pos_t){_posX, _posY, dir, 0};
		if (_missil.dir == AR_DOWN || _missil.dir == AR_UP)
			_missil.posY += (_missil.dir == AR_UP) ? -1 : 1;
		else if (_missil.dir == AR_RIGHT || _missil.dir == AR_LEFT)
			_missil.posX += (_missil.dir == AR_LEFT) ? -1 : 1;
		_missil.old = (*_map)[_missil.posY][_missil.posX];
	}
}

void ar::Enemy::moveShoot()
{
	if (!_shoot && rand() % 10 <= 2)
		shoot();
	if (_shoot) {
		if (_missil.old == EMPTY || _missil.old == COIN)
			(*_map)[_missil.posY][_missil.posX] = _missil.old;
		if (_missil.dir == AR_DOWN || _missil.dir == AR_UP)
			_missil.posY += (_missil.dir == AR_UP) ? -1 : 1;
		if (_missil.dir == AR_RIGHT || _missil.dir == AR_LEFT)
			_missil.posX += (_missil.dir == AR_LEFT) ? -1 : 1;
		_missil.old = (*_map)[_missil.posY][_missil.posX];
		int missil = (_missil.dir == AR_DOWN || _missil.dir == AR_UP) ? ENEMY_SHOOT_V : ENEMY_SHOOT_H;
		if (_missil.old != WALL_H && _missil.old != WALL_V)
			(*_map)[_missil.posY][_missil.posX] = missil;
		if (_missil.dir == AR_UP || _missil.dir == AR_DOWN)
			if (_missil.posY < 1 || !(*_map)[_missil.posY + 1]) {
				_shoot = false;
				if (_missil.old == EMPTY || _missil.old == COIN)
					(*_map)[_missil.posY][_missil.posX] = _missil.old;
			}
		if (_missil.dir == AR_LEFT || _missil.dir == AR_RIGHT)
			if (_missil.posX <= 1 ||
				!(*_map)[_missil.posY][_missil.posX + 1]) {
				_shoot = false;
				if (_missil.old == EMPTY || _missil.old == COIN)
					(*_map)[_missil.posY][_missil.posX] = _missil.old;
			}
	}
}

void ar::Enemy::move()
{
	int pos[2] = {_dir == AR_RIGHT || _dir == AR_LEFT,
		_dir == AR_UP || _dir == AR_DOWN};

	(*_map)[_posY][_posX] = _old;
	(*_map)[_posY + pos[1]][_posX + pos[0]] = _old;
	_posX += pos[0] * ((_dir == AR_LEFT) ? -1 : 1);
	_posY += pos[1] * ((_dir == AR_UP) ? -1 : 1);
	if (_dir == AR_RIGHT || _dir == AR_LEFT) {
		if (_posX >= _max || _posX <= 1)
			_dir = (_dir == AR_RIGHT) ? AR_LEFT : AR_RIGHT;
	} else if (_dir == AR_DOWN || _dir == AR_UP) {
		if (_posY >= _max || _posY <= 1)
			_dir = (_dir == AR_DOWN) ? AR_UP : AR_DOWN;
	}
	(*_map)[_posY][_posX] = _texture;
	(*_map)[_posY + pos[1]][_posX + pos[0]] = _texture + 1;
}
