/*
** EPITECH PROJECT, 2021
** cpp_arcade
** File description:
** Created by angevil,
*/

#include <iostream>
#include <memory>
#include <algorithm>
#include "Bomberman.hpp"
#include "textureBomberman.hpp"

ar::Bomberman::Bomberman() : _score(0), _direction(ar::AR_UNKNOWN),
	_map(41, 41), _gameOver(false), _start(time(nullptr)), _paused(true),
	_powerBombs(1), _spanBombs(3), _amountBombs(1)
{
	_player = PLAYER_UP;
	initMap();
	_map[1][2] = EMPTY;
	_map[2][1] = EMPTY;
	_step = clock();
	_pause = time(nullptr);
	_posX = 1;
	_posY = 1;
	initColorsVector();
	initSpriteVector();
	initBomberman();
	initMobs();
	_map.setPlayerX(_posX);
	_map.setPlayerY(_posY);
}

void ar::Bomberman::initMap()
{
	for (int i = 0; i < _map.getHeight(); ++i) {
		_map[i][0] = WALL;
		for (int j = 1; j < _map.getWidth(); ++j) {
			if (i != 0 && i != _map.getHeight() - 1) {
				if (j % 2 == 0 && i % 2 == 0)
					_map[i][j] = WALL;
				else
					_map[i][j] = BREAKABLE;
			} else
				_map[i][j] = WALL;
		}
		_map[i][_map.getWidth() - 1] = WALL;
		_map[i][_map.getWidth()] = '\0';
	}
	_map[_map.getHeight()] = nullptr;
}

void ar::Bomberman::initBomberman()
{
	_map[_posY][_posX] = _player;
}

void ar::Bomberman::initColorsVector()
{
	_mapColors.insert(std::pair<unsigned char, colorVector>(WALL,
		(colorVector){255, 255, 255}));
	_mapColors.insert(std::pair<unsigned char, colorVector>(EMPTY,
		(colorVector){0, 0, 0}));
	_mapColors.insert(std::pair<unsigned char, colorVector>(PLAYER_UP,
		(colorVector){255, 255, 0}));
	_mapColors.insert(std::pair<unsigned char, colorVector>(PLAYER_DOWN,
		(colorVector){255, 255, 0}));
	_mapColors.insert(std::pair<unsigned char, colorVector>(PLAYER_LEFT,
		(colorVector){255, 255, 0}));
	_mapColors.insert(std::pair<unsigned char, colorVector>(PLAYER_RIGHT,
		(colorVector){255, 255, 0}));
	_mapColors.insert(std::pair<unsigned char, colorVector>(BREAKABLE,
		(colorVector){255, 0, 0}));
	_mapColors.insert(std::pair<unsigned char, colorVector>(BOMB,
		(colorVector){255, 0, 255}));
	_mapColors.insert(std::pair<unsigned char, colorVector>(EXPLOSION,
		(colorVector){0, 255, 0}));
	_mapColors.insert(std::pair<unsigned char, colorVector>(BONUS_EXPLOSION,
		(colorVector){0, 255, 0}));
	_mapColors.insert(std::pair<unsigned char, colorVector>(BONUS_BOMB,
		(colorVector){0, 255, 0}));
	_mapColors.insert(std::pair<unsigned char, colorVector>(MOB,
		(colorVector){0, 255, 255}));
}

void ar::Bomberman::initSpriteVector()
{
	_mapSprites.insert(std::pair<unsigned char, spriteCoords>(EMPTY,
		(spriteCoords){64, 128, 64, 64}));
	_mapSprites.insert(std::pair<unsigned char, spriteCoords>(WALL,
		(spriteCoords){128, 64, 64, 64}));
	_mapSprites.insert(std::pair<unsigned char, spriteCoords>(PLAYER_UP,
		(spriteCoords){128, 0, 64, 64}));
	_mapSprites.insert(std::pair<unsigned char, spriteCoords>(PLAYER_DOWN,
		(spriteCoords){0, 0, 64, 64}));
	_mapSprites.insert(std::pair<unsigned char, spriteCoords>(PLAYER_LEFT,
		(spriteCoords){64, 0, 64, 64}));
	_mapSprites.insert(std::pair<unsigned char, spriteCoords>(PLAYER_RIGHT,
		(spriteCoords){192, 0, 64, 64}));
	_mapSprites.insert(std::pair<unsigned char, spriteCoords>(BREAKABLE,
		(spriteCoords){64, 64, 64, 64}));
	_mapSprites.insert(std::pair<unsigned char, spriteCoords>(BOMB,
		(spriteCoords){256, 0, 64, 64}));
	_mapSprites.insert(std::pair<unsigned char, spriteCoords>(EXPLOSION,
		(spriteCoords){192, 64, 64, 64}));
	_mapSprites.insert(
		std::pair<unsigned char, spriteCoords>(BONUS_EXPLOSION,
			(spriteCoords){0, 128, 64, 64}));
	_mapSprites.insert(std::pair<unsigned char, spriteCoords>(BONUS_BOMB,
		(spriteCoords){256, 64, 64, 64}));
	_mapSprites.insert(std::pair<unsigned char, spriteCoords>(MOB,
		(spriteCoords){0, 64, 64, 64}));
}

ar::Bomberman::~Bomberman()
{
	_mapSprites.clear();
	_mapColors.clear();
}

const std::string ar::Bomberman::getGameName() const
{
	return "Bomberman";
}

const std::map<unsigned char, ar::spriteCoords> &ar::Bomberman::getSprites() const
{
	return _mapSprites;
}

const std::map<unsigned char, ar::colorVector> &ar::Bomberman::getColors() const
{
	return _mapColors;
}

void ar::Bomberman::handlePause()
{
	if (_paused) {
		_start += (time(nullptr) - _pause);
		_pause = 0;
		_paused = false;
	} else {
		_step = clock();
		_pause = time(nullptr);
		_paused = true;
	}
}

void ar::Bomberman::manageKey(const ar::Event &key)
{
	if (key == ar::AR_ACTION && !_paused)
		spawnBomb();
	if (key == ar::AR_PAUSE)
		handlePause();
	if (_paused)
		return;
	if (key == ar::AR_UP || key == ar::AR_DOWN || key == ar::AR_LEFT ||
		key == ar::AR_RIGHT)
		_direction = key;
}

int ar::Bomberman::refreshScore()
{
	return _score;
}

bool ar::Bomberman::isGameOver()
{
	return _gameOver;
}

void ar::Bomberman::loop()
{
	clock_t temp = clock();

	if (temp - _step > 100000 && !_gameOver && !_paused) {
		_step = temp;
		if (!_paused) {
			checkDeath();
			moveBomberman();
			refreshBombs();
			refreshBomberman();
			refreshExplosions();
			refreshMobs();
			checkDeath();
			checkWin();
		}
	}
}

void ar::Bomberman::refreshBomberman()
{
	_map[_posY][_posX] = _player;
}

void ar::Bomberman::moveBomberman()
{
	int stX = _posX;
	int stY = _posY;

	_map[_posY][_posX] = EMPTY;
	switch (_direction) {
	case ar::AR_DOWN:
		_posY += 1;
		break;
	case ar::AR_UP:
		_posY -= 1;
		break;
	case ar::AR_LEFT:
		_posX -= 1;
		break;
	case ar::AR_RIGHT:
		_posX += 1;
		break;
	default:
		break;
	}
	if (_map[_posY][_posX] != EMPTY && _map[_posY][_posX] != EXPLOSION &&
		_map[_posY][_posX] != BONUS_BOMB &&
		_map[_posY][_posX] != BONUS_EXPLOSION) {
		_posY = stY;
		_posX = stX;
	} else {
		if (_map[_posY][_posX] == BONUS_BOMB)
			_amountBombs += 1;
		if (_map[_posY][_posX] == BONUS_EXPLOSION)
			_powerBombs += 1;
		updateDirection();
	}
	_direction = AR_UNKNOWN;
}

int ar::Bomberman::refreshTimer()
{
	if (!_gameOver) {
		if (_paused)
			return static_cast<int>(
				_pause - _start);
		return static_cast<int>(time(nullptr) - _start);
	}
	return static_cast<int>(_end - _start);
}

void ar::Bomberman::setPause()
{
	if (!_paused)
		manageKey(ar::AR_PAUSE);
}

const std::string ar::Bomberman::getSpritesPath() const
{
	return "./resources/bomberman-texture.png";
}

ar::Map &ar::Bomberman::getMap()
{
	return _map;
}

void ar::Bomberman::spawnBomb()
{
	if (static_cast<int>(_bombs.size()) < _amountBombs) {
		Bomb newBomb(_posX, _posY, _powerBombs, _spanBombs);
		_bombs.push_back(newBomb);
	}
}

void ar::Bomberman::refreshBombs()
{
	auto it = _bombs.begin();

	while (it != _bombs.end()) {
		if ((*it).live(_map) == false) {
			_score += (*it).getBrokenWalls();
			addExplosion((*it).getExplosion());
			_bombs.erase(it);
		} else {
			it++;
		}
	}
}

void ar::Bomberman::addExplosion(std::vector<explosionT> explosion)
{
	for (auto &it : explosion)
		_explosedAreas.push_back(it);
}

void ar::Bomberman::refreshExplosions()
{
	int now = static_cast<int>(time(nullptr));
	auto it = _explosedAreas.begin();
	while (it != _explosedAreas.end()) {
		if (now - (*it).start >= 1) {
			if ((*it).hidden == EXPLOSED_WALL)
				spawnBonus((*it).x, (*it).y);
			_explosedAreas.erase(it);
		} else {
			it++;
		}
	}
	removeExplosions();
	for (auto &it : _explosedAreas) {
		_map[it.y][it.x] = EXPLOSION;
	}
}

void ar::Bomberman::removeExplosions()
{
	int y = 0;

	while (y != _map.getHeight()) {
		int x = 0;
		while (x != _map.getWidth()) {
			if (_map[y][x] == EXPLOSION)
				_map[y][x] = EMPTY;
			x += 1;
		}
		y += 1;
	}
}

void ar::Bomberman::checkDeath()
{
	if (_map[_posY][_posX] == EXPLOSION || _map[_posY][_posX] == MOB) {
		_gameOver = true;
		_end = time(nullptr);
	}
}

void ar::Bomberman::spawnBonus(int x, int y)
{
	int ratio = rand() % 100;

	if (ratio > 94)
		_map[y][x] = BONUS_EXPLOSION;
	else if (ratio > 85)
		_map[y][x] = BONUS_BOMB;
}

void ar::Bomberman::initMobs()
{
	_mobs.push_back(Mob(7, 7));
	_mobs.push_back(Mob(15, 15));
	_mobs.push_back(Mob(23, 23));
	_mobs.push_back(Mob(19, 10));
	_mobs.push_back(Mob(10, 19));
	_mobs.push_back(Mob(19, 30));
	_mobs.push_back(Mob(30, 19));
	_mobs.push_back(Mob(31, 31));
	_mobs.push_back(Mob(33, 7));
	_mobs.push_back(Mob(7, 33));
}

void ar::Bomberman::refreshMobs()
{
	auto it = _mobs.begin();

	while (it != _mobs.end()) {
		if (!(*it).live(_map)) {
			_mobs.erase(it);
			_score += 1000;
		} else
			it++;
	}
}

void ar::Bomberman::checkWin()
{
	if (_mobs.empty())
		_end = true;
}

void ar::Bomberman::updateDirection()
{
	switch (_direction) {
	case ar::AR_DOWN:
		_player = PLAYER_DOWN;
		break;
	case ar::AR_UP:
		_player = PLAYER_UP;
		break;
	case ar::AR_LEFT:
		_player = PLAYER_LEFT;
		break;
	case ar::AR_RIGHT:
		_player = PLAYER_RIGHT;
		break;
	default:
		break;
	}
}

extern "C" ar::Bomberman *createGame()
{
	return new ar::Bomberman;
}

extern "C" void destroyGame(ar::Bomberman *Bomberman)
{
	delete Bomberman;
}
