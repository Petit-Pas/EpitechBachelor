/*
** EPITECH PROJECT, 2021
** cpp_arcade
** File description:
** Created by angevil,
*/

#include <iostream>
#include <memory>
#include "Qix.hpp"

ar::Qix::Qix() : _score(0), _direction(ar::AR_UNKNOWN), _map(60, 40), _posX(_map.getWidth() / 2),
	_posY(_map.getHeight() - 1), _gameOver(false), _isDirectionValidated(true),
	_start(time(nullptr)), _paused(true), _old(BORDER), _trailing(false), _flame(nullptr), _lives(3)
{
	initMap();
	_step = clock();
	_pause = time(nullptr);
	initColorsVector();
	initSpriteVector();
	initPlayer();
	_sparks.push_back(std::unique_ptr<Spark>(new Spark(_map, 0, 0, 1, 0)));
	_sparks.push_back(std::unique_ptr<Spark>(new Spark(_map, 0, 0, 0, 1)));
	_monster = std::unique_ptr<Monster>(new Monster(_map));
	_monster->live();
	updateScore();
	_map.setPlayerX(_posX);
	_map.setPlayerY(_posY);
}

void ar::Qix::initMap()
{
	for (int i = 0; i < _map.getHeight(); ++i) {
		_map[i][0] = BORDER; //border
		for (int j = 1; j < _map.getWidth(); ++j) {
			if (i != 0 && i != _map.getHeight() - 1)
				_map[i][j] = EMPTY;
			else
				_map[i][j] = BORDER;
		}
		_map[i][_map.getWidth() - 1] = BORDER;
		_map[i][_map.getWidth()] = '\0';
	}
	_map[_map.getHeight()] = nullptr;
}

void ar::Qix::initPlayer()
{
	_map[_posY][_posX] = PLAYER;
}

void ar::Qix::initColorsVector()
{
	_mapColors.insert(std::pair<unsigned char, colorVector>(EMPTY, (colorVector){0, 0, 0}));
	_mapColors.insert(std::pair<unsigned char, colorVector>(BORDER, (colorVector){255, 0, 0}));
	_mapColors.insert(std::pair<unsigned char, colorVector>(PLAYER, (colorVector){0, 0, 255}));
	_mapColors.insert(std::pair<unsigned char, colorVector>(QIXHEAD, (colorVector){0, 255, 0}));
	_mapColors.insert(std::pair<unsigned char, colorVector>(QIXBODY1, (colorVector){0, 255, 0}));
	_mapColors.insert(std::pair<unsigned char, colorVector>(QIXBODY2, (colorVector){0, 255, 0}));
	_mapColors.insert(std::pair<unsigned char, colorVector>(QIXBODY3, (colorVector){0, 255, 0}));
	_mapColors.insert(std::pair<unsigned char, colorVector>(QIXBODY4, (colorVector){0, 255, 0}));
	_mapColors.insert(std::pair<unsigned char, colorVector>(QIXBODY5, (colorVector){0, 255, 0}));
	_mapColors.insert(std::pair<unsigned char, colorVector>(QIXBODY6, (colorVector){0, 255, 0}));
	_mapColors.insert(std::pair<unsigned char, colorVector>(QIXBODY7, (colorVector){0, 255, 0}));
	_mapColors.insert(std::pair<unsigned char, colorVector>(QIXBODY8, (colorVector){0, 255, 0}));
	_mapColors.insert(std::pair<unsigned char, colorVector>(QIXBODY9, (colorVector){0, 255, 0}));
	_mapColors.insert(std::pair<unsigned char, colorVector>(QIXLEGRIGHT, (colorVector){0, 255, 0}));
	_mapColors.insert(std::pair<unsigned char, colorVector>(QIXLEGLEFT, (colorVector){0, 255, 0}));
	_mapColors.insert(std::pair<unsigned char, colorVector>(QIXARMLEFT, (colorVector){0, 255, 0}));
	_mapColors.insert(std::pair<unsigned char, colorVector>(QIXARMRIGHT, (colorVector){0, 255, 0}));
	_mapColors.insert(std::pair<unsigned char, colorVector>(TRAIL, (colorVector){255, 255, 255}));
	_mapColors.insert(std::pair<unsigned char, colorVector>(EATEN, (colorVector){0, 0, 0}));
	_mapColors.insert(std::pair<unsigned char, colorVector>(WALL, (colorVector){255, 0, 255}));
	_mapColors.insert(std::pair<unsigned char, colorVector>(SPARK1, (colorVector){255, 255, 0}));
	_mapColors.insert(std::pair<unsigned char, colorVector>(SPARK2, (colorVector){255, 255, 255}));
	_mapColors.insert(std::pair<unsigned char, colorVector>(FLAME1, (colorVector){255, 255, 0}));
	_mapColors.insert(std::pair<unsigned char, colorVector>(FLAME2, (colorVector){255, 255, 255}));
}

ar::Qix::~Qix()
{
	_mapSprites.clear();
	_mapColors.clear();
	_sparks.clear();
}

const std::string ar::Qix::getGameName() const
{
	return "Qix";
}

void ar::Qix::initSpriteVector()
{
	_mapSprites.insert(std::pair<unsigned char, spriteCoords>(BORDER, (spriteCoords){64, 64, 64, 64}));
	_mapSprites.insert(std::pair<unsigned char, spriteCoords>(EMPTY, (spriteCoords){0, 128, 64, 64}));
	_mapSprites.insert(std::pair<unsigned char, spriteCoords>(PLAYER, (spriteCoords){128, 64, 64, 64}));
	_mapSprites.insert(std::pair<unsigned char, spriteCoords>(TRAIL, (spriteCoords){0, 64, 64, 64}));
	_mapSprites.insert(std::pair<unsigned char, spriteCoords>(EATEN, (spriteCoords){128, 0, 64, 64}));
	_mapSprites.insert(std::pair<unsigned char, spriteCoords>(WALL, (spriteCoords){192, 0, 64, 64}));
	_mapSprites.insert(std::pair<unsigned char, spriteCoords>(SPARK1, (spriteCoords){0, 0, 64, 64}));
	_mapSprites.insert(std::pair<unsigned char, spriteCoords>(SPARK2, (spriteCoords){64, 0, 64, 64}));
	_mapSprites.insert(std::pair<unsigned char, spriteCoords>(FLAME1, (spriteCoords){0, 0, 64, 64}));
	_mapSprites.insert(std::pair<unsigned char, spriteCoords>(FLAME2, (spriteCoords){64, 0, 64, 64}));
	_mapSprites.insert(std::pair<unsigned char, spriteCoords>(QIXHEAD, (spriteCoords){256, 0, 64, 64}));
	_mapSprites.insert(std::pair<unsigned char, spriteCoords>(QIXBODY1, (spriteCoords){192, 64, 64, 64}));
	_mapSprites.insert(std::pair<unsigned char, spriteCoords>(QIXBODY2, (spriteCoords){256, 64, 64, 64}));
	_mapSprites.insert(std::pair<unsigned char, spriteCoords>(QIXBODY3, (spriteCoords){320, 64, 64, 64}));
	_mapSprites.insert(std::pair<unsigned char, spriteCoords>(QIXBODY4, (spriteCoords){192, 128, 64, 64}));
	_mapSprites.insert(std::pair<unsigned char, spriteCoords>(QIXBODY5, (spriteCoords){256, 128, 64, 64}));
	_mapSprites.insert(std::pair<unsigned char, spriteCoords>(QIXBODY6, (spriteCoords){320, 128, 64, 64}));
	_mapSprites.insert(std::pair<unsigned char, spriteCoords>(QIXBODY7, (spriteCoords){192, 192, 64, 64}));
	_mapSprites.insert(std::pair<unsigned char, spriteCoords>(QIXBODY8, (spriteCoords){256, 192, 64, 64}));
	_mapSprites.insert(std::pair<unsigned char, spriteCoords>(QIXBODY9, (spriteCoords){320, 192, 64, 64}));
	_mapSprites.insert(std::pair<unsigned char, spriteCoords>(QIXARMLEFT, (spriteCoords){128, 128, 64, 64}));
	_mapSprites.insert(std::pair<unsigned char, spriteCoords>(QIXARMRIGHT, (spriteCoords){384, 128, 64, 64}));
	_mapSprites.insert(std::pair<unsigned char, spriteCoords>(QIXLEGRIGHT, (spriteCoords){320, 256, 64, 64}));
	_mapSprites.insert(std::pair<unsigned char, spriteCoords>(QIXLEGLEFT, (spriteCoords){192, 256, 64, 64}));

}

const std::map<unsigned char, ar::spriteCoords> &ar::Qix::getSprites() const
{
	return _mapSprites;
}

const std::map<unsigned char, ar::colorVector> &ar::Qix::getColors() const
{
	return _mapColors;
}

void ar::Qix::handlePause()
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

void ar::Qix::manageKey(const ar::Event &key)
{
	if (key == ar::AR_PAUSE)
		handlePause();
	if (_paused)
		return;
	if (_isDirectionValidated) {
		if (key == ar::AR_UP && _direction != ar::AR_UP)
			_direction = key;
		else if (key == ar::AR_DOWN && _direction != ar::AR_DOWN)
			_direction = key;
		else if (key == ar::AR_LEFT && _direction != ar::AR_LEFT)
			_direction = key;
		else if (key == ar::AR_RIGHT && _direction != ar::AR_RIGHT)
			_direction = key;
		else if (key == ar::AR_ACTION)
			_direction = AR_UNKNOWN;
		else
			return;
		_isDirectionValidated = false;
	}
}

int ar::Qix::refreshScore()
{
	return _score;
}

bool ar::Qix::isGameOver()
{
	return _gameOver;
}

void ar::Qix::checkTrailCell(int x, int y)
{
	static int pos[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
	int amount = 0;

	for (int i = 0; i != 4; i ++)
		if (checkIfCellIsInside(x + pos[i][0], y + pos[i][1]) && _map[y + pos[i][1]][x + pos[i][0]] == BORDER)
			amount += 1;
	if (amount == 2)
		_map[y][x] = BORDER;
}

void ar::Qix::checkTrailBorder()
{
	int y = 0;
	int x;

	while (y != _map.getHeight()) {
		x = 0;
		while (x != _map.getWidth()) {
			if (_map[y][x] == TRAIL)
				checkTrailCell(x, y);
			x += 1;
		}
		y += 1;
	}
}

void ar::Qix::loop()
{
	clock_t temp = clock();
	static int tic = 0;

	if (temp - _step > 100000 && !_gameOver && !_paused) {
		tic += 1;
		if (!_monster->live() && _trailing)
			goBack();
		if (tic == 4) {
			tic = 0;
			_step = temp;
			if (_flame != nullptr)
				_flame->live();
			liveSparks();
			if (_map[_posY][_posX] == ar::TextureQix::SPARK1 || _map[_posY][_posX] == ar::TextureQix::SPARK2)
				_gameOver = true;
			if (_map[_posY][_posX] == ar::TextureQix::FLAME1 || _map[_posY][_posX] == ar::TextureQix::FLAME2)
				goBack();
			setBorder();
			movePlayer();
			if (_map[_posY][_posX] == ar::TextureQix::SPARK1 || _map[_posY][_posX] == ar::TextureQix::SPARK2)
				_gameOver = true;
			if (_map[_posY][_posX] == ar::TextureQix::FLAME1 || _map[_posY][_posX] == ar::TextureQix::FLAME2)
				goBack();
			_isDirectionValidated = true;
			if (_gameOver)
				_end = time(nullptr);
			_map.setPlayerX(_posX);
			_map.setPlayerY(_posY);
			checkTrailBorder();
		}
	}
}

bool ar::Qix::checkAround(int posY, int posX)
{
	int amount = 0;
	static int array[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
	int i = 0;

	while (i != 8) {
		if (_map[posY + array[i][1]][posX + array[i][0]] == TRAIL)
			amount += 1;
		i += 1;
	}
	if (amount != 1 && amount != 0 && amount != 2) {
		spawnFlame();
		return false;
	}
	if (amount == 2) {
		if (_map[posY][posX + 1] == TRAIL && _map[posY + 1][posX + 1] == TRAIL)
			return true;
		if (_map[posY - 1][posX + 1] == TRAIL && _map[posY][posX + 1] == TRAIL)
			return true;
		if (_map[posY - 1][posX - 1] == TRAIL && _map[posY][posX - 1] == TRAIL)
			return true;
		if (_map[posY][posX - 1] == TRAIL && _map[posY + 1][posX - 1] == TRAIL)
			return true;
		if (_map[posY - 1][posX - 1] == TRAIL && _map[posY - 1][posX] == TRAIL)
			return true;
		if (_map[posY - 1][posX] == TRAIL && _map[posY - 1][posX + 1] == TRAIL)
			return true;
		if (_map[posY + 1][posX - 1] == TRAIL && _map[posY + 1][posX] == TRAIL)
			return true;
		if (_map[posY + 1][posX] == TRAIL && _map[posY + 1][posX + 1] == TRAIL)
			return true;
		spawnFlame();
		return false;
	}
	return true;
}

void ar::Qix::checkFlame()
{
	if (_direction == AR_UNKNOWN && _flame == nullptr) {
		_flame = std::unique_ptr<Flame>(new Flame(_map, _posY, _posX));
	}
}

void ar::Qix::checkMove(int addonX, int addonY)
{
	int x = _posX + addonX;
	int y = _posY + addonY;

	if (checkIfCellIsInside(x, y)) {
		if (_map[y][x] == BORDER
			|| (_map[y][x] == EMPTY && checkAround(y, x))) {
			_posY = y;
			_posX = x;
			if (checkIfCellIsInside(x + addonX, y + addonY)
				&& _map[y][x] == BORDER && _map[y + addonY][ x + addonX] == EMPTY)
				_direction = AR_UNKNOWN;
		}
		else if (_map[y][x] == TRAIL)
			spawnFlame();
	}
}

void ar::Qix::movePlayer()
{
	TextureQix st = _old;
	_old = static_cast<TextureQix>(_map[_posY][_posX]);
	if (st == EMPTY) {
		_map[_posY][_posX] = TRAIL;
		_trailing = true;
		checkFlame();
	} else
		_map[_posY][_posX] = st;
	switch (_direction) {
	case ar::AR_DOWN:
		checkMove(0, 1);
		break;
	case ar::AR_UP:
		checkMove(0, -1);
		break;
	case ar::AR_LEFT:
		checkMove(-1, 0);
		break;
	case ar::AR_RIGHT:
		checkMove(1, 0);
		break;
	default:
		break;
	}
	_old = static_cast<TextureQix>(_map[_posY][_posX]);
	_map[_posY][_posX] = PLAYER;
	fillEmptyArea();
}

void ar::Qix::findEmptyCell(int &x, int &y)
{
	while (_map[y] != nullptr) {
		x = 0;
		while (_map[y][x] != '\0') {
			if (_map[y][x] == EMPTY)
				return;
			x += 1;
		}
		y += 1;
	}
}

void ar::Qix::fillEmptyArea()
{
	int x = 0;
	int y = 0;
	findEmptyCell(x, y);
	std::vector<Qix::Cell> set1 = findSet(x, y, EMPTY1);
	x = 0;
	y = 0;
	findEmptyCell(x, y);

	if ((x != 0 || y != 0) && (_map[y] != nullptr && _map[y][x] != 0)) {
		std::vector<Qix::Cell> set2 = findSet(x, y, EMPTY2);
		if (isQixInSet(set1)) {
			replaceInMap(EMPTY1, EMPTY);
			replaceInMap(EMPTY2, EATEN);
		} else {
			replaceInMap(EMPTY2, EMPTY);
			replaceInMap(EMPTY1, EATEN);
		}
		validatePolygon();
	} else {
		replaceInMap(EMPTY1, EMPTY);
		if (isPlayerNextToBorder() && isPlayerNextToTrail()) {
			replaceInMap(TRAIL, WALL);
			_old = BORDER;
			validatePolygon();
		}
	}
	_monster->putMonster();
}

void ar::Qix::validatePolygon()
{
	_trailing = false;
	if (_flame != nullptr) {
		_flame.reset(nullptr);
	}
	replaceInMap(BORDER, WALL);
	replaceInMap(TRAIL, WALL);
	setBorder();
	updateScore();
}

std::vector<ar::Qix::Cell> ar::Qix::findSet(int x, int y, TextureQix emptyness)
{
	static int pos[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
	Cell toAdd{x, y};
	std::vector<Cell> vector;
	vector.push_back(toAdd);
	_map[y][x] = emptyness;
	int i = 0;
	while (i != static_cast<int>(vector.size())) {
		for (int j = 0; j != 4; j += 1) {
			if (_map[vector[i].posY + pos[j][1]][vector[i].posX + pos[j][0]] == EMPTY) {
				_map[vector[i].posY + pos[j][1]][vector[i].posX + pos[j][0]] = emptyness;
				toAdd.posY = vector[i].posY + pos[j][1];
				toAdd.posX = vector[i].posX + pos[j][0];
				vector.push_back(toAdd);
			} else if (isQuix(vector[i].posX + pos[j][0], vector[i].posY + pos[j][1])) {
				_map[vector[i].posY + pos[j][1]][vector[i].posX + pos[j][0]] = QIXUTIL;
				toAdd.posY = vector[i].posY + pos[j][1];
				toAdd.posX = vector[i].posX + pos[j][0];
				vector.push_back(toAdd);
			}
		}
		i += 1;
	}
	return vector;
}

int ar::Qix::refreshTimer()
{
	if (!_gameOver) {
		if (_paused)
			return static_cast<int>(
				_pause - _start);
		return static_cast<int>(time(nullptr) - _start);
	}
	return static_cast<int>(_end - _start);
}

void ar::Qix::setPause()
{
	if (!_paused)
		manageKey(ar::AR_PAUSE);
}

const std::string ar::Qix::getSpritesPath() const
{
	return "./resources/qix-texture.png";
}

bool ar::Qix::isQixInSet(std::vector<ar::Qix::Cell> set)
{
	for (auto &it : set) {
		if (_map[it.posY][it.posX] == QIXUTIL)
			return true;
		if (_map[it.posY][it.posX + 1] == QIXUTIL)
			return true;
		if (_map[it.posY][it.posX - 1] == QIXUTIL)
			return true;
		if (_map[it.posY + 1][it.posX] == QIXUTIL)
			return true;
		if (_map[it.posY - 1][it.posX] == QIXUTIL)
			return true;
	}
	return false;
}

void ar::Qix::replaceInMap(ar::TextureQix from, ar::TextureQix to)
{
	int x = 0;
	int y = 0;

	while (_map[y] != nullptr) {
		x = 0;
		while (_map[y][x] != '\0') {
			if (_map[y][x] == from)
				_map[y][x] = to;
			x += 1;
		}
		y += 1;
	}
}

void ar::Qix::setBorder()
{
	int x = 0;
	int y = 0;

	while (_map[y] != nullptr) {
		x = 0;
		while (_map[y][x] != '\0') {
			if (_map[y][x] == WALL || _map[y][x] == EATEN)
				if (checkIfBorder(x, y))
					_map[y][x] = BORDER;
			x += 1;
		}
		y += 1;
	}
}

bool ar::Qix::checkIfBorder(int x, int y)
{
	static int array[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
	int i = 0;

	while (i != 8) {
		if (y + array[i][1] > 0 && _map[y + array[i][1]] != nullptr && x + array[i][0] > 0 &&
			_map[y + array[i][1]][x + array[i][0]] == EMPTY)
			return true;
		i += 1;
	}
	return false;
}

ar::Map &ar::Qix::getMap()
{
	return _map;
}

bool ar::Qix::isQuix(int x, int y)
{
	return _map[y][x] >= QIXHEAD && _map[y][x] <= QIXBODY9;
}

bool ar::Qix::isPlayerNextToBorder()
{
	static int pos[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

	for (int i = 0; i != 4; i += 1) {
		if (_posY + pos[i][1] >= 0 && _posY + pos[i][1] < _map.getHeight()
			&& _posX + pos[i][0] >= 0 && _posX + pos[i][0] < _map.getWidth()
			&& _map[_posY + pos[i][1]][_posX + pos[i][0]] == BORDER)
			return true;
	}
	return false;
}

bool ar::Qix::isPlayerNextToTrail()
{
	static int pos[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

	for (int i = 0; i != 4; i += 1) {
		if (_posY + pos[i][1] >= 0 && _posY + pos[i][1] < _map.getHeight()
			&& _posX + pos[i][0] >= 0 && _posX + pos[i][0] < _map.getWidth()
			&& _map[_posY + pos[i][1]][_posX + pos[i][0]] == TRAIL)
			return true;
	}
	return false;
}

void ar::Qix::updateScore()
{
	int empty = 0;

	for (int y = 0; y != _map.getHeight(); y += 1) {
		for (int x = 0; x != _map.getWidth(); x += 1) {
			if (_map[y][x] == EMPTY)
				empty += 1;
		}
	}
	_score = static_cast<int>(
		10000 - ((empty) / (static_cast<float>(_map.getWidth() - 2) *
			(static_cast<float>(_map.getHeight() - 2))) * 10000));
	if (_score > 7500)
		_gameOver = true;
	if (_score > 2500 && _sparks.size() < 3) {
		_sparks.push_back(std::unique_ptr<Spark>(new Spark(_map, _map.getWidth() - 1,
			_map.getHeight() - 1, _map.getWidth() - 1, _map.getHeight() - 2)));
	}
	if (_score > 5000 && _sparks.size() < 4) {
		_sparks.push_back(std::unique_ptr<Spark>(new Spark(_map, _map.getWidth() - 1,
			_map.getHeight() - 1, _map.getWidth() - 2, _map.getHeight() - 1)));
	}

}

void ar::Qix::goBack()
{
	static int pos[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
	int prevX = -1;
	int prevY = -1;

	_lives -= 1;
	if (_lives == 0) {
		_gameOver = true;
		return;
	}
	_map[_posY][_posX] = EMPTY;
	if (_flame != nullptr) {
		_flame.reset(nullptr);
	}
	while (_map[_posY][_posX] != BORDER && _map[_posY][_posX] != WALL) {
		for (int i = 0; i != 4; i += 1) {
			if (checkIfCellIsInside(_posX + pos[i][0], _posY + pos[i][1]) &&
				!(_posX + pos[i][0] == prevX && _posY + pos[i][1] == prevY) &&
				(_map[_posY + pos[i][1]][_posX + pos[i][0]] == TRAIL
					|| _map[_posY + pos[i][1]][_posX + pos[i][0]] == BORDER
					|| _map[_posY + pos[i][1]][_posX + pos[i][0]] == WALL)) {
				prevX = _posX;
				prevY = _posY;
				_posX += pos[i][0];
				_posY += pos[i][1];
				break;
			}
			if (checkIfCellIsInside(_posX + pos[i][0], _posY + pos[i][1]) &&
				!(_posX + pos[i][0] == prevX && _posY + pos[i][1] == prevY) &&
				(_map[_posY + pos[i][1]][_posX + pos[i][0]] == SPARK1
					|| _map[_posY + pos[i][1]][_posX + pos[i][0]] == SPARK2)) {
				_map[_posY + pos[i][1]][_posX + pos[i][0]] = BORDER;
				prevX = _posX;
				prevY = _posY;
				_posX += pos[i][0];
				_posY += pos[i][1];
				resetSparks();
				break;
			}
		}
	}
	replaceInMap(TRAIL, EMPTY);
	_direction = AR_UNKNOWN;
	_old = BORDER;
	setBorder();
}

bool ar::Qix::checkIfCellIsInside(int x, int y)
{
	return (x >= 0 && x <= _map.getWidth() && y >= 0 && y < _map.getHeight());
}

void ar::Qix::spawnFlame()
{
	if (_flame == nullptr) {
		_flame = std::unique_ptr<Flame>(new Flame(_map, _posY, _posX));
	}
}

void ar::Qix::liveSparks()
{
	for (auto &it : _sparks) {
		it->live();
	}
}

void ar::Qix::resetSparks()
{
	int amount = static_cast<int>(_sparks.size());

	_sparks.clear();
	_sparks.push_back(std::unique_ptr<Spark>(new Spark(_map, 0, 0, 1, 0)));
	_sparks.push_back(std::unique_ptr<Spark>(new Spark(_map, 0, 0, 0, 1)));
	if (amount >= 3) {

		_sparks.push_back(std::unique_ptr<Spark>(new Spark(_map, _map.getWidth() - 1,
			_map.getHeight() - 1, _map.getWidth() - 1, _map.getHeight() - 2)));
	}
	if (amount == 4) {
		_sparks.push_back(std::unique_ptr<Spark>(new Spark(_map, _map.getWidth() - 1,
			_map.getHeight() - 1, _map.getWidth() - 2, _map.getHeight() - 1)));
	}
}

extern "C" ar::Qix *createGame()
{
	return new ar::Qix;
}

extern "C" void destroyGame(ar::Qix *qix)
{
	delete qix;
}
