/*
** EPITECH PROJECT, 2021
** cpp_arcade
** File description:
** Created by angevil,
*/

#include <iostream>
#include <iomanip>
#include <memory>
#include <algorithm>
#include "SolarFox.hpp"

ar::SolarFox::SolarFox()
	: _score(0), _width(39), _height(40), _direction(ar::AR_DOWN), _map(40, 40),
	  _gameOver(false), _isDirectionValidated(true), _start(time(nullptr)), _paused(true)
{
	coinMap();
	initMap();
	_step = clock();
	_pause = time(nullptr);
	initColorsVector();
	initSpriteVector();
	_vessel = new Vessel({_width / 2, _height / 2, ar::Event::AR_UNKNOWN, EMPTY}, _width, _height, &_map);
	_enemy[0] = new Enemy({1, 0, AR_RIGHT, EMPTY}, _width, &_map, ENEMY_T1);
	_enemy[1] = new Enemy({_width - 2, _height - 1, AR_LEFT, EMPTY}, _width, &_map, ENEMY_B1);
	_enemy[2] = new Enemy({0, 1, AR_DOWN, EMPTY}, _height - 1, &_map, ENEMY_L1);
	_enemy[3] = new Enemy({_width, _height - 3, AR_UP, EMPTY}, _height - 1, &_map, ENEMY_R1);
}

void ar::SolarFox::coinMap()
{
	for (int i = 12; i >= 0; i -= 2) {
		for (int j = 12 - i; j <= i + 2; j += 2) {
			_coins.insert(_coins.begin(), (ar::spriteCoords){i, 12 + j, 0, 0});
			_coins.insert(_coins.begin(), (ar::spriteCoords){12 + j, i, 0, 0});
		}
	}
	for (int i = 26; i <= 32; i += 2) {
		for (int j = 12 + (i - 26); j < 54 - i; j += 2) {
			_coins.insert(_coins.begin(), (ar::spriteCoords){j, i, 0, 0});
			_coins.insert(_coins.begin(), (ar::spriteCoords){i, j, 0, 0});
		}
	}
}

void ar::SolarFox::initMap()
{
       	for (int i = 0; i < _height; ++i) {
		_map[i][0] = WALL_V;
		for (int j = 1; j < _width; ++j) {
			if (i != 0 && i != _height - 1)
				_map[i][j] = EMPTY;
			else
				_map[i][j] = WALL_H;
		}
		_map[i][_width] = WALL_V;
		_map[i][_width + 1] = '\0';
	}
	_map[0][0] = WALL_C1;
	_map[0][_width] = WALL_C2;
	_map[_height - 1][0] = WALL_C3;
	_map[_height - 1][_width] = WALL_C4;
	for (size_t i = 0; i < _coins.size(); i++)
		_map[_coins.at(i).y][_coins.at(i).x] = COIN;
	_map[_height] = nullptr;
}

void ar::SolarFox::initColorsVector()
{
	for (int i = WALL_V; i <= WALL_C4; i++)
		_mapColors.insert(std::pair<unsigned char, colorVector>(i, (colorVector){255, 0, 0}));
	_mapColors.insert(std::pair<unsigned char, colorVector>(EMPTY, (colorVector){0, 0, 0}));
	_mapColors.insert(std::pair<unsigned char, colorVector>(COIN, (colorVector){255, 0, 255}));
	for (int i = VESSEL_B; i <= VESSEL_L; i++)
		_mapColors.insert(std::pair<unsigned char, colorVector>(i, (colorVector){255, 255, 0}));
	_mapColors.insert(std::pair<unsigned char, colorVector>(ENEMY_SHOOT_V, (colorVector){255, 0, 0}));
	_mapColors.insert(std::pair<unsigned char, colorVector>(ENEMY_SHOOT_H, (colorVector){255, 0, 0}));
	_mapColors.insert(std::pair<unsigned char, colorVector>(SHOOT_V, (colorVector){0, 255, 0}));
	_mapColors.insert(std::pair<unsigned char, colorVector>(SHOOT_H, (colorVector){0, 255, 0}));
	for (int i = ENEMY_B1; i <= ENEMY_L2; i++)
		_mapColors.insert(std::pair<unsigned char, colorVector>(i, (colorVector){0, 255, 255}));
}

void ar::SolarFox::initSpriteVector()
{
	_mapSprites.insert(std::pair<unsigned char, spriteCoords>(VESSEL_T, (spriteCoords){0, 0, 64, 64}));
	_mapSprites.insert(std::pair<unsigned char, spriteCoords>(VESSEL_R, (spriteCoords){0, 64, 64, 64}));
	_mapSprites.insert(std::pair<unsigned char, spriteCoords>(VESSEL_B, (spriteCoords){0, 128, 64, 64}));
	_mapSprites.insert(std::pair<unsigned char, spriteCoords>(VESSEL_L, (spriteCoords){0, 192, 64, 64}));
	_mapSprites.insert(std::pair<unsigned char, spriteCoords>(ENEMY_T1, (spriteCoords){64, 0, 64, 64}));
	_mapSprites.insert(std::pair<unsigned char, spriteCoords>(ENEMY_T2, (spriteCoords){128, 0, 64, 64}));
	_mapSprites.insert(std::pair<unsigned char, spriteCoords>(ENEMY_B1, (spriteCoords){64, 64, 64, 64}));
	_mapSprites.insert(std::pair<unsigned char, spriteCoords>(ENEMY_B2, (spriteCoords){128, 64, 64, 64}));
	_mapSprites.insert(std::pair<unsigned char, spriteCoords>(ENEMY_L1, (spriteCoords){64, 128, 64, 64}));
	_mapSprites.insert(std::pair<unsigned char, spriteCoords>(ENEMY_L2, (spriteCoords){64, 192, 64, 64}));
	_mapSprites.insert(std::pair<unsigned char, spriteCoords>(ENEMY_R1, (spriteCoords){128, 128, 64, 64}));
	_mapSprites.insert(std::pair<unsigned char, spriteCoords>(ENEMY_R2, (spriteCoords){128, 192, 64, 64}));
	_mapSprites.insert(std::pair<unsigned char, spriteCoords>(ENEMY_SHOOT_V, {192, 0, 64, 64}));
	_mapSprites.insert(std::pair<unsigned char, spriteCoords>(ENEMY_SHOOT_H, {192, 64, 64, 64}));
	_mapSprites.insert(std::pair<unsigned char, spriteCoords>(SHOOT_V, {192, 128, 64, 64}));
	_mapSprites.insert(std::pair<unsigned char, spriteCoords>(SHOOT_H, {192, 192, 64, 64}));
	_mapSprites.insert(std::pair<unsigned char, spriteCoords>(COIN, (spriteCoords){256, 0, 64, 64}));
	_mapSprites.insert(std::pair<unsigned char, spriteCoords>(WALL_H, (spriteCoords){256, 64, 64, 64}));
	_mapSprites.insert(std::pair<unsigned char, spriteCoords>(WALL_V, (spriteCoords){256, 128, 64, 64}));
	_mapSprites.insert(std::pair<unsigned char, spriteCoords>(EMPTY, (spriteCoords){256, 192, 64, 64}));
	_mapSprites.insert(std::pair<unsigned char, spriteCoords>(WALL_C1, (spriteCoords){320, 0, 64, 64}));
	_mapSprites.insert(std::pair<unsigned char, spriteCoords>(WALL_C2, (spriteCoords){320, 64, 64, 64}));
	_mapSprites.insert(std::pair<unsigned char, spriteCoords>(WALL_C3, (spriteCoords){320, 192, 64, 64}));
	_mapSprites.insert(std::pair<unsigned char, spriteCoords>(WALL_C4, (spriteCoords){320, 128, 64, 64}));
}

ar::SolarFox::~SolarFox()
{
	_mapSprites.clear();
	_mapColors.clear();
}

const std::string ar::SolarFox::getGameName() const
{
	return "SolarFox";
}

const std::map<unsigned char, ar::spriteCoords> &ar::SolarFox::getSprites() const
{
	return _mapSprites;
}

const std::map<unsigned char, ar::colorVector> &ar::SolarFox::getColors() const
{
	return _mapColors;
}

void ar::SolarFox::handlePause()
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

void ar::SolarFox::manageKey(const ar::Event &key)
{

	if (key == ar::AR_PAUSE)
		handlePause();
	if (_paused)
		return;
	if (_isDirectionValidated) {
		if (_vessel && key == ar::AR_ACTION)
			_vessel->shoot(_direction);
		else if (key == ar::AR_UP && _direction != ar::AR_DOWN && _direction != ar::AR_UP)
			_direction = key;
		else if (key == ar::AR_DOWN && _direction != ar::AR_UP && _direction != ar::AR_DOWN)
			_direction = key;
		else if (key == ar::AR_LEFT && _direction != ar::AR_RIGHT && _direction != ar::AR_LEFT)
			_direction = key;
		else if (key == ar::AR_RIGHT && _direction != ar::AR_LEFT && _direction != ar::AR_RIGHT)
			_direction = key;
		else
			return;
		_isDirectionValidated = false;
	}
}

int ar::SolarFox::refreshScore()
{
	return _score;
}

bool ar::SolarFox::isGameOver()
{
	return _gameOver;
}

void ar::SolarFox::loop()
{
	clock_t temp = clock();
	static clock_t tmp = 0;
	static clock_t tmp2 = 0;

	if (_vessel && temp - tmp2 > 50000 && !_gameOver && !_paused) {
		tmp2 = temp;
		_vessel->moveMissil();
		for (int i = 0; i < 4; i ++)
			_enemy[i]->moveShoot();
	}
	if (temp - tmp > 130000 && !_gameOver && !_paused) {
		tmp = temp;
		for (int i = 0; i < 4; i ++)
			_enemy[i]->move();
	}
	if (_vessel && temp - _step > 100000 && !_gameOver && !_paused) {
		_step = temp;
		_vessel->move(_direction);
		_isDirectionValidated = true;
		if (_vessel->isGameOver() || _gameOver) {
			_end = time(nullptr);
			_gameOver = true;
		}
	}
	if (_vessel)
		_score = _vessel->getScore();
	if (_coins.size() == 4)
		_gameOver = true;
}

int ar::SolarFox::refreshTimer()
{
	if (!_gameOver) {
		if (_paused)
			return static_cast<int>(
				_pause - _start);
		return static_cast<int>(time(nullptr) - _start);
	}
	return static_cast<int>(_end - _start);
}

void ar::SolarFox::setPause()
{
	if (!_paused)
		manageKey(ar::AR_PAUSE);
}

const std::string ar::SolarFox::getSpritesPath() const
{
	return "./resources/solarfox-texture.png";
}

ar::Map &ar::SolarFox::getMap()
{
	return _map;
}

extern "C" ar::SolarFox *createGame()
{
	return new ar::SolarFox;
}

extern "C" void destroyGame(ar::SolarFox *solarFox)
{
	delete solarFox;
}
