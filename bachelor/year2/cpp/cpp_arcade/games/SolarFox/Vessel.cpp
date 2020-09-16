//
// EPITECH PROJECT, 2018
// Arcade
// File description:
// SolarFox Vessel
//

#include "Vessel.hpp"

ar::Vessel::Vessel(ar::Vessel::pos_t pos, int width, int height, Map *map)
	: _posX(pos.posX), _maxX(width), _posY(pos.posY), _maxY(height), _dir(pos.dir),
	  _shoot(false), _missil({0, 0, ar::Event::AR_UNKNOWN, EMPTY}), _old(EMPTY), _gameOver(false),
	  _map(map)
{
	(*_map)[_posY][_posX] = VESSEL_B;
}

ar::Vessel::pos_t ar::Vessel::getPos()
{
	pos_t pos = {_posX, _posY, _dir, (*_map)[_posY][_posX]};
	return pos;
}

void ar::Vessel::shoot(Event dir)
{
	if (!_shoot) {
		_shoot = true;
		_missilLife = 2;
		_missil = (pos_t){_posX, _posY, dir, (*_map)[_posY][_posX]};
		if (dir == AR_DOWN || dir == AR_UP)
			_missil.posY += (dir == AR_UP) ? -1 : 1;
		if (dir == AR_RIGHT || dir == AR_LEFT)
			_missil.posX += (dir == AR_LEFT) ? -1 : 1;
	}
}

void ar::Vessel::moveMissil()
{
	if (_shoot) {
		_missilLife -= 1;
		(*_map)[_missil.posY][_missil.posX] = _missil.old;
		Event dir = _missil.dir;
		if (dir == AR_DOWN || dir == AR_UP)
			_missil.posY += (dir == AR_UP) ? -1 : 1;
		if (dir == AR_RIGHT || dir == AR_LEFT)
			_missil.posX += (dir == AR_LEFT) ? -1 : 1;
		_missil.old = (*_map)[_missil.posY][_missil.posX];
		if (_missil.old == COIN)
			_score += 10;
		if (_missil.old == EMPTY || _missil.old == COIN)
			_missil.old = (_missil.old == COIN) ? EMPTY : _missil.old;
		if (_missil.posX < 1 || _missil.posX >= _maxX ||
			_missil.posY < 1 || _missil.posY >= _maxY - 1)
			_missilLife = -1;
		if (_missil.old >= VESSEL_B && _missil.old <= VESSEL_L)
			_missil.old = EMPTY;
		if (_missilLife <= 0) {
			_shoot = false;
			if (_missil.old == EMPTY || _missil.old == COIN)
				(*_map)[_missil.posY][_missil.posX] = _missil.old;
		} else
			(*_map)[_missil.posY][_missil.posX] = SHOOT_V + (dir == AR_LEFT || dir == AR_RIGHT);
	}
}

bool ar::Vessel::isGameOver()
{
	return _gameOver;
}

void ar::Vessel::move(Event dir)
{
	int vessel = _old;

	if (_old >= VESSEL_B && _old <= VESSEL_L)
		_old = EMPTY;
	(*_map)[_posY][_posX] = _old;
	_dir = dir;
	switch (dir) {
	case ar::AR_DOWN:
		_posY += 1;
		vessel = VESSEL_B;
		break;
	case ar::AR_UP:
		_posY -= 1;
		vessel = VESSEL_T;
		break;
	case ar::AR_LEFT:
		_posX -= 1;
		vessel = VESSEL_L;
		break;
	case ar::AR_RIGHT:
		_posX += 1;
		vessel = VESSEL_R;
		break;
	default:
		return;
	}
	_old = (*_map)[_posY][_posX];
	if (_old >= ENEMY_SHOOT_V && _old <= SHOOT_H)
		_gameOver = true;
	else
		(*_map)[_posY][_posX] = vessel;
	if (_posX < 1 || _posX >= _maxX || _posY < 1 || _posY >= _maxY - 1)
		_gameOver = true;
}

int ar::Vessel::getScore()
{
	return _score;
}