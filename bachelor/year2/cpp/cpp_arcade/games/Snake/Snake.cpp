/*
** EPITECH PROJECT, 2021
** cpp_arcade
** File description:
** Created by angevil,
*/

#include <iostream>
#include <memory>
#include <algorithm>
#include "Snake.hpp"

ar::Snake::Snake() : _score(0), _direction(ar::AR_DOWN), _map(40, 50), _gameOver(false), _length(4),
	_isDirectionValidated(true), _askedRules(true), _start(time(nullptr)), _paused(true)
{
	initMap();
	_step = clock();
	_pause = time(nullptr);
	_posX = _map.getWidth() / 2;
	_posY = _map.getHeight() / 2;
	initColorsVector();
	initSpriteVector();
	initSnake();
	spawnFood();
	_bonus.posX = 1;
	_bonus.posY = 1;
	_bonus.span = 0;
	_map.setPlayerX(_posX);
	_map.setPlayerY(_posY);
}

void ar::Snake::initMap()
{
	for (int i = 0; i < _map.getHeight(); ++i) {
		_map[i][0] = WALL;
		for (int j = 1; j < _map.getWidth(); ++j) {
			if (i != 0 && i != _map.getHeight() - 1)
				_map[i][j] = EMPTY;
			else
				_map[i][j] = WALL;
		}
		_map[i][_map.getWidth() - 1] = WALL;
		_map[i][_map.getWidth()] = '\0';
	}
	_map[_map.getHeight()] = nullptr;
}

void ar::Snake::initSnake()
{
	_body.push_back((Body){_posX, _posY - 3, 1, AR_DOWN});
	_body.push_back((Body){_posX, _posY - 2, 2, AR_DOWN});
	_body.push_back((Body){_posX, _posY - 1, 3, AR_DOWN});
	_body.push_back((Body){_posX, _posY, 4, AR_DOWN});
	_map[_posY][_posX] = DOWN_HEAD;
	_map[_posY - 1][_posX] = BODY_VERT;
	_map[_posY - 2][_posX] = BODY_VERT;
	_map[_posY - 3][_posX] = DOWN_TAIL;
}

void ar::Snake::initColorsVector()
{
	_mapColors.insert(std::pair<unsigned char, colorVector>(WALL, (colorVector){255, 255, 255}));
	_mapColors.insert(std::pair<unsigned char, colorVector>(EMPTY, (colorVector){0, 0, 0}));
	_mapColors.insert(std::pair<unsigned char, colorVector>(FOOD, (colorVector){255, 0, 0}));
	_mapColors.insert(std::pair<unsigned char, colorVector>(BONUS, (colorVector){255, 0, 255}));
	_mapColors.insert(std::pair<unsigned char, colorVector>(UP_HEAD, (colorVector){255, 255, 0}));
	_mapColors.insert(std::pair<unsigned char, colorVector>(DOWN_HEAD, (colorVector){255, 255, 0}));
	_mapColors.insert(std::pair<unsigned char, colorVector>(LEFT_HEAD, (colorVector){255, 255, 0}));
	_mapColors.insert(std::pair<unsigned char, colorVector>(RIGHT_HEAD, (colorVector){255, 255, 0}));
	_mapColors.insert(std::pair<unsigned char, colorVector>(BODY_VERT, (colorVector){0, 255, 0}));
	_mapColors.insert(std::pair<unsigned char, colorVector>(BODY_HORIZ, (colorVector){0, 255, 0}));
	_mapColors.insert(std::pair<unsigned char, colorVector>(UP_TAIL, (colorVector){0, 255, 0}));
	_mapColors.insert(std::pair<unsigned char, colorVector>(DOWN_TAIL, (colorVector){0, 255, 0}));
	_mapColors.insert(std::pair<unsigned char, colorVector>(LEFT_TAIL, (colorVector){0, 255, 0}));
	_mapColors.insert(std::pair<unsigned char, colorVector>(RIGHT_TAIL, (colorVector){0, 255, 0}));
	_mapColors.insert(std::pair<unsigned char, colorVector>(DOWN_LEFT, (colorVector){0, 255, 0}));
	_mapColors.insert(std::pair<unsigned char, colorVector>(UP_LEFT, (colorVector){0, 255, 0}));
	_mapColors.insert(std::pair<unsigned char, colorVector>(UP_RIGHT, (colorVector){0, 255, 0}));
	_mapColors.insert(std::pair<unsigned char, colorVector>(DOWN_RIGHT, (colorVector){0, 255, 0}));
}

void ar::Snake::initSpriteVector()
{
	_mapSprites.insert(std::pair<unsigned char, spriteCoords>(EMPTY, (spriteCoords){0, 128, 64, 64}));
	_mapSprites.insert(std::pair<unsigned char, spriteCoords>(WALL, (spriteCoords){64, 192, 64, 64}));
	_mapSprites.insert(std::pair<unsigned char, spriteCoords>(FOOD, (spriteCoords){0, 192, 64, 64}));
	_mapSprites.insert(std::pair<unsigned char, spriteCoords>(BONUS, (spriteCoords){64, 128, 64, 64}));
	_mapSprites.insert(std::pair<unsigned char, spriteCoords>(UP_HEAD, (spriteCoords){192, 0, 64, 64}));
	_mapSprites.insert(std::pair<unsigned char, spriteCoords>(LEFT_HEAD, (spriteCoords){192, 64, 64, 64}));
	_mapSprites.insert(std::pair<unsigned char, spriteCoords>(RIGHT_HEAD, (spriteCoords){256, 0, 64, 64}));
	_mapSprites.insert(std::pair<unsigned char, spriteCoords>(DOWN_HEAD, (spriteCoords){256, 64, 64, 64}));
	_mapSprites.insert(std::pair<unsigned char, spriteCoords>(BODY_VERT, (spriteCoords){128, 64, 64, 64}));
	_mapSprites.insert(std::pair<unsigned char, spriteCoords>(BODY_HORIZ, (spriteCoords){64, 0, 64, 64}));
	_mapSprites.insert(std::pair<unsigned char, spriteCoords>(UP_TAIL, (spriteCoords){192, 128, 64, 64}));
	_mapSprites.insert(std::pair<unsigned char, spriteCoords>(DOWN_TAIL, (spriteCoords){256, 192, 64, 64}));
	_mapSprites.insert(std::pair<unsigned char, spriteCoords>(LEFT_TAIL, (spriteCoords){192, 192, 64, 64}));
	_mapSprites.insert(std::pair<unsigned char, spriteCoords>(RIGHT_TAIL, (spriteCoords){256, 128, 64, 64}));
	_mapSprites.insert(std::pair<unsigned char, spriteCoords>(DOWN_RIGHT, (spriteCoords){0, 0, 64, 64}));
	_mapSprites.insert(std::pair<unsigned char, spriteCoords>(DOWN_LEFT, (spriteCoords){128, 0, 64, 64}));
	_mapSprites.insert(std::pair<unsigned char, spriteCoords>(UP_RIGHT, (spriteCoords){0, 64, 64, 64}));
	_mapSprites.insert(std::pair<unsigned char, spriteCoords>(UP_LEFT, (spriteCoords){128, 128, 64, 64}));
}

ar::Snake::~Snake()
{
	_mapSprites.clear();
	_mapColors.clear();
	_body.clear();
}

const std::string ar::Snake::getGameName() const
{
	return "Snake";
}

const std::map<unsigned char, ar::spriteCoords> &ar::Snake::getSprites() const
{
	return _mapSprites;
}

const std::map<unsigned char, ar::colorVector> &ar::Snake::getColors() const
{
	return _mapColors;
}

void ar::Snake::handlePause()
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

void ar::Snake::manageKey(const ar::Event &key)
{
	if (key == ar::AR_ACTION)
		_askedRules = !_askedRules;
	if (key == ar::AR_PAUSE)
		handlePause();
	if (_paused)
		return;
	if (_isDirectionValidated) {
		if (!_askedRules) {
			if (key == ar::AR_UP && _direction != ar::AR_DOWN && _direction != ar::AR_UP)
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
		} else
			askedDirection(key);
	}
}

void ar::Snake::askedDirection(ar::Event key)
{
	if (key == ar::AR_LEFT) {
		if (_direction == ar::AR_UP)
			_direction = AR_LEFT;
		else if (_direction == ar::AR_LEFT)
			_direction = AR_DOWN;
		else if (_direction == ar::AR_DOWN)
			_direction = AR_RIGHT;
		else if (_direction == ar::AR_RIGHT)
			_direction = AR_UP;
		_isDirectionValidated = false;
	} else if (key == ar::AR_RIGHT) {
		if (_direction == ar::AR_UP)
			_direction = AR_RIGHT;
		else if (_direction == ar::AR_RIGHT)
			_direction = AR_DOWN;
		else if (_direction == ar::AR_DOWN)
			_direction = AR_LEFT;
		else if (_direction == ar::AR_LEFT)
			_direction = AR_UP;
		_isDirectionValidated = false;
	}
}

int ar::Snake::refreshScore()
{
	return _score;
}

bool ar::Snake::isGameOver()
{
	return _gameOver;
}

void ar::Snake::loop()
{
	clock_t temp = clock();

	if (temp - _step > 100000 && !_gameOver && !_paused) {
		_step = temp;
		moveSnake();
		checkEat();
		manageBonus();
		if (_map[_posY][_posX] != FOOD && _map[_posY][_posX] != BONUS && _map[_posY][_posX] != EMPTY)
			_gameOver = true;
		refreshSnake();
		_isDirectionValidated = true;
		if (_gameOver)
			_end = time(nullptr);
		_map.setPlayerY(_posY);
	}
}

void ar::Snake::refreshSnake()
{
	_body.push_back((Body){_posX, _posY, _length + 1, _direction});
	auto it = _body.begin();
	int i = 0;
	int size = static_cast<int>(_body.size());
	while (i != size) {
		if ((*it).direction == AR_DOWN || (*it).direction == AR_UP)
			_map[(*it).posY][(*it).posX] = BODY_VERT;
		else
			_map[(*it).posY][(*it).posX] = BODY_HORIZ;
		(*it).span -= 1;
		if ((*it).span == 0 || (*it).span == -1)
			_map[(*it).posY][(*it).posX] = EMPTY;
		if ((*it).span == -1) {
			_body.erase(it);
			it--;
		}
		i += 1;
		it++;
	}
	putCorner();
}

bool ar::Snake::checkCorner(std::vector<struct Body>::iterator &it, ar::Event a, ar::Event b, ar::Event c)
{
	return ((*(it - 1)).direction == a && (*it).direction == b && (*(it + 1)).direction == c);
}

void ar::Snake::checkCorners(std::vector<struct Body>::iterator it)
{
	while ((*it).span != _length) {
		if (checkCorner(it, AR_RIGHT, AR_RIGHT, AR_DOWN) || checkCorner(it, AR_UP, AR_UP, AR_LEFT) ||
			checkCorner(it, AR_DOWN, AR_RIGHT, AR_DOWN) || checkCorner(it, AR_LEFT, AR_UP, AR_LEFT) ||
			checkCorner(it, AR_UP, AR_RIGHT, AR_DOWN) || checkCorner(it, AR_RIGHT, AR_UP, AR_LEFT))
			_map[(*it).posY][(*it).posX] = DOWN_LEFT;
		else if (checkCorner(it, AR_UP, AR_UP, AR_RIGHT) || checkCorner(it, AR_LEFT, AR_LEFT, AR_DOWN) ||
			checkCorner(it, AR_RIGHT, AR_UP, AR_RIGHT) || checkCorner(it, AR_DOWN, AR_LEFT, AR_DOWN) ||
			checkCorner(it, AR_UP, AR_LEFT, AR_DOWN) || checkCorner(it, AR_LEFT, AR_UP, AR_RIGHT))
			_map[(*it).posY][(*it).posX] = DOWN_RIGHT;
		else if (checkCorner(it, AR_DOWN, AR_DOWN, AR_RIGHT) || checkCorner(it, AR_LEFT, AR_LEFT, AR_UP) ||
			checkCorner(it, AR_DOWN, AR_RIGHT, AR_DOWN) || checkCorner(it, AR_UP, AR_LEFT, AR_UP) ||
			checkCorner(it, AR_DOWN, AR_LEFT, AR_UP) || checkCorner(it, AR_LEFT, AR_DOWN, AR_RIGHT) ||
			checkCorner(it, AR_RIGHT, AR_DOWN, AR_RIGHT))
			_map[(*it).posY][(*it).posX] = UP_RIGHT;
		else if (checkCorner(it, AR_DOWN, AR_DOWN, AR_LEFT) || checkCorner(it, AR_RIGHT, AR_RIGHT, AR_UP) ||
			checkCorner(it, AR_UP, AR_RIGHT, AR_UP) || checkCorner(it, AR_DOWN, AR_LEFT, AR_DOWN) ||
			checkCorner(it, AR_DOWN, AR_RIGHT, AR_UP) || checkCorner(it, AR_RIGHT, AR_DOWN, AR_LEFT) ||
			checkCorner(it, AR_LEFT, AR_DOWN, AR_LEFT))
			_map[(*it).posY][(*it).posX] = UP_LEFT;
		it++;
	}
}

void ar::Snake::putCorner()
{
	auto it = _body.begin();
	it++;
	if (_direction == ar::AR_DOWN)
		_map[_posY][_posX] = DOWN_HEAD;
	else if (_direction == ar::AR_UP)
		_map[_posY][_posX] = UP_HEAD;
	else if (_direction == ar::AR_LEFT)
		_map[_posY][_posX] = LEFT_HEAD;
	else
		_map[_posY][_posX] = RIGHT_HEAD;
	ar::Event stock = (*(it + 1)).direction;
	if (stock == ar::AR_DOWN)
		_map[(*it).posY][(*it).posX] = DOWN_TAIL;
	if (stock == ar::AR_UP)
		_map[(*it).posY][(*it).posX] = UP_TAIL;
	if (stock == ar::AR_LEFT)
		_map[(*it).posY][(*it).posX] = LEFT_TAIL;
	if (stock == ar::AR_RIGHT)
		_map[(*it).posY][(*it).posX] = RIGHT_TAIL;
	checkCorners(it + 1);
}

void ar::Snake::manageBonus()
{
	if (random() % 50 == 0 && _bonus.span == 0) {
		spawnBonus();
	} else if (_bonus.span != 0) {
		_bonus.span -= 1;
	}
	if (_bonus.span != 0) {
		_map[_bonus.posY][_bonus.posX] = BONUS;
	} else {
		_map[_bonus.posY][_bonus.posX] = EMPTY;
	}
}

void ar::Snake::checkEat()
{
	if (_map[_posY][_posX] == FOOD) {
		_score += 100;
		_length += 1;
		auto it = _body.begin();
		int i = 0;
		int size = static_cast<int>(_body.size());
		while (i != size) {
			(*it).span += 1;
			i += 1;
			it++;
		}
		spawnFood();
	}
	if (_map[_posY][_posX] == BONUS) {
		_score += 300;
		_bonus.span = 0;
	}
}

void ar::Snake::spawnFood()
{
	int x;
	int y;
	int i = 0;

	auto test = static_cast<unsigned int>(time(nullptr));
	srandom(test);
	while (i != 1000000) {
		i += 1;
		x = static_cast<int>(random() % (_map.getWidth() - 1) + 1);
		y = static_cast<int>(random() % (_map.getHeight() - 1) + 1);
		if (_map[y][x] == EMPTY) {
			_map[y][x] = FOOD;
			return;
		}
	}
}

void ar::Snake::moveSnake()
{
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
}

void ar::Snake::spawnBonus()
{
	int x;
	int y;
	int i = 0;

	auto test = static_cast<unsigned int>(time(nullptr));
	srandom(test);
	while (i != 1000000) {
		i += 1;
		x = static_cast<int>(random() % (_map.getWidth() - 1) + 1);
		y = static_cast<int>(random() % (_map.getHeight() - 1) + 1);
		if (_map[y][x] == EMPTY) {
			_bonus.posX = x;
			_bonus.posY = y;
			_bonus.span = 30;
			return;
		}
	}
}

int ar::Snake::refreshTimer()
{
	if (!_gameOver) {
		if (_paused)
			return static_cast<int>(
				_pause - _start);
		return static_cast<int>(time(nullptr) - _start);
	}
	return static_cast<int>(_end - _start);
}

void ar::Snake::setPause()
{
	if (!_paused)
		manageKey(ar::AR_PAUSE);
}

const std::string ar::Snake::getSpritesPath() const
{
	return "./resources/snake-texture.png";
}

ar::Map &ar::Snake::getMap()
{
	return _map;
}

extern "C" ar::Snake *createGame()
{
	return new ar::Snake;
}

extern "C" void destroyGame(ar::Snake *snake)
{
	delete snake;
}
