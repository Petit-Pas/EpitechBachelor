/*
** EPITECH PROJECT, 2018
** Graphical
** File description:
** Created by martin.van-elslande@epitech.eu,
*/

#include <sstream>
#include <iostream>
#include <Direction.hpp>
#include "BackEnd.hpp"

BackEnd::BackEnd(const std::string &addr, int port, sf::Vector2i &_mapSize,
	std::map<std::string, Tile> &_tiles,
	std::map<int, std::shared_ptr<Player>> &_players,
	std::map<int, Egg> &eggs, std::vector<Incantation> &incantations,
	std::vector<std::string> &_teams, int &_timeUnit, bool &_gameFinished,
	std::string &_winningTeam, float &_tileWidth, Log &log
) : _connection(addr, port), _mapSize(_mapSize), _tiles(_tiles),
	_players(_players), _eggs(eggs), _incantations(incantations),
	_teams(_teams), _timeUnit(_timeUnit), _gameFinished(_gameFinished),
	_winningTeam(_winningTeam), _tileWidth(_tileWidth), _log(log)
{
	sf::Clock clock;
	float elapsed;
	std::string msg;
	bool ret = _connection.receiveMsg();

	if (!ret)
		throw std::runtime_error("Unable to read on the server");
	while (ret) {
		elapsed = clock.getElapsedTime().asSeconds();
		if (elapsed >= 10.0f)
			throw std::runtime_error("Connection timed out.");
		if (_connection.hasMessages() &&
			_connection.getNextMessage() == "WELCOME")
			break;
		ret = _connection.receiveMsg();
	}
	_connection.sendMsg("GRAPHIC");
	if (!_grass.loadFromFile("resources/sprites/grass.jpg"))
		throw std::runtime_error("Cannot open file 'grass.jpg'");
	if (!_grassIncantation.loadFromFile(
		"resources/sprites/incantation.png"))
		throw std::runtime_error("Cannot open file 'incantation.png'");
	if (!_egg.loadFromFile("resources/sprites/eggs.png"))
		throw std::runtime_error("Cannot open file 'eggs.png'");
	if (!_resources.loadFromFile("resources/sprites/items.png"))
		throw std::runtime_error("Cannot open file 'items.png'");
	if (!_character.loadFromFile("resources/sprites/Soldiers.png"))
		throw std::runtime_error("Cannot open file 'Soldiers.png'");
}

void BackEnd::refresh()
{
	if (_connection.receiveMsg()) {
		while (_connection.hasMessages()) {
			std::string msg = _connection.getNextMessage();
			try {
				parseMsg(msg);
			} catch (std::exception &e) {
				std::cerr << e.what() << std::endl;
				exit(0);
			}
		}
	}
}

bool BackEnd::isMapSet() const
{
	return _mapSize.x != -1 && _mapSize.y != -1;
}

std::string BackEnd::getNextBroadcast()
{
	std::string nextBc(_broadcasts.front());

	_broadcasts.pop();
	return nextBc;
}

void BackEnd::parseMsg(const std::string &msg)
{
	std::istringstream iss(msg);
	std::string cmd;

	if (!(iss >> cmd))
		return;
	if (_parse.find(cmd) != _parse.end()) {
		auto func(_parse.at(cmd));
		(this->*(func))(iss);
	}
}

void BackEnd::parseMsz(std::istringstream &iss)
{
	int x;
	int y;
	int err;

	if (!(iss >> x >> y) || iss >> err)
		return;
	_mapSize.x = x;
	_mapSize.y = y;

	float width = WIDTH / (float)_mapSize.x;
	float height = HEIGHT / (float)_mapSize.y;
	if (width < height)
		_tileWidth = width;
	else
		_tileWidth = height;
}

void BackEnd::addResourcesToTile(int *q, Tile &tile)
{
	for (int i = 0; i < 7; i++) {
		tile.resources.insert(std::pair<int, Resource>(i, {q[i],
			sf::RectangleShape(
				sf::Vector2f(_tileWidth / 5, _tileWidth / 5)),
			&_resources, sf::IntRect(i * 48, 48, 48, 48),
			sf::IntRect(i * 48, 0, 48, 48)}));
		if (i < 4)
			tile.resources[i].shape.setPosition(
				tile.pos.x * _tileWidth,
				tile.pos.y * _tileWidth +
					(i * (_tileWidth / 5)));
		else
			tile.resources[i].shape.setPosition(
				tile.pos.x * _tileWidth + (4 * _tileWidth / 5),
				tile.pos.y * _tileWidth +
					((i % 4) * (_tileWidth / 5)));
		tile.resources[i].shape.setTexture(tile.resources[i].texture);
		if (tile.resources[i].quantity > 1)
			tile.resources[i].shape.setTextureRect(
				tile.resources[i].multiple);
		else
			tile.resources[i].shape.setTextureRect(
				tile.resources[i].single);
		_log.addLog("%i %s was added to the tile (%i;%i)\n",
			tile.resources[i].quantity, intToResource(i),
			tile.pos.x, tile.pos.y);
	}
}

void BackEnd::parseBct(std::istringstream &iss)
{
	sf::Vector2i pos;
	int q[7];
	std::string err;

	if (!(iss >> pos.x >> pos.y >> q[0] >> q[1] >> q[2] >> q[3] >> q[4]
		>> q[5] >> q[6]) || iss >> err)
		return;
	std::string posStr =
		std::to_string(pos.x) + ";" + std::to_string(pos.y);
	if (_tiles.find(posStr) == _tiles.end()) {
		_tiles.insert({posStr, {pos, std::map<int, Resource>(),
			sf::RectangleShape(
				sf::Vector2f(_tileWidth, _tileWidth)),
			sf::FloatRect(pos.x * _tileWidth, pos.y * _tileWidth,
				_tileWidth, _tileWidth), _grass,
			_grassIncantation}});
		_log.addLog("Tile (%i;%i) was created\n", pos.x, pos.y);
	} else {
		for (int i = 0; i < 7; ++i) {
			_tiles.at((posStr)).resources[i].quantity = q[i];
		}
	}
	Tile &tile = _tiles.at(posStr);
	addResourcesToTile(q, tile);
	tile.shape.setPosition(
		sf::Vector2f(pos.x * _tileWidth, pos.y * _tileWidth));
	tile.shape.setTexture(&tile.texture);
	tile.shape.setTextureRect(sf::IntRect(0, 0, 512, 512));
}

void BackEnd::parseTna(std::istringstream &iss)
{
	std::string teamName;
	std::string err;

	if (!(iss >> teamName) || iss >> err)
		return;
	if (std::find(_teams.begin(), _teams.end(), teamName) == _teams.end())
		_teams.push_back(teamName);
	_log.addLog("Team %s was created\n", teamName.c_str());
}

void BackEnd::parsePnw(std::istringstream &iss)
{
	std::string number, teamName, err;
	int orientation = 0;
	int level = 0;
	int id;
	sf::Vector2i pos;

	if (!(iss >> number >> pos.x >> pos.y >> orientation >> level
		>> teamName) || iss >> err)
		return;
	if (number[0] == '#')
		number.erase(0, 1);
	id = atoi(number.c_str());
	if (_players.find(id) != _players.end())
		return;
	for (size_t idx = 0; idx < _teams.size(); idx++) {
		if (teamName == _teams[idx]) {
			_players.insert({id,
				std::make_unique<Player>(id, orientation, level,
					teamName, idx, pos,
					std::vector<int>(7, 0), false, false,
					_tileWidth, &_character)});
			_players.at(id)->setShapePos(pos);
		}
	}
	_log.addLog("Player %i in team %s was summoned\n", id,
		teamName.c_str());
}

void BackEnd::parsePpo(std::istringstream &iss)
{
	int id;
	sf::Vector2i pos;
	int orientation;
	std::string err;

	if (!(iss >> id >> pos.x >> pos.y >> orientation) || iss >> err)
		return;
	if (_players.find(id) == _players.end())
		return;
	if (pos == _players.at(id)->getPos()) {
		_log.addLog("Player %i now look %s\n", id,
			_players.at(id)->intToDirection(orientation));
	} else {
		_log.addLog("Player %i moved from (%i;%i) to (%i;%i)\n", id,
			_players.at(id)->getPos().x,
			_players.at(id)->getPos().y, pos.x, pos.y);
	}
	_players.at(id)->setPos(pos);
	_players.at(id)->setOrientation(orientation);
	_players.at(id)->move();
}

void BackEnd::parsePlv(std::istringstream &iss)
{
	int id, level;
	std::string err;

	if (!(iss >> id >> level) || iss >> err)
		return;
	if (_players.find(id) == _players.end())
		return;
	_players.at(id)->setLevel(level);
	_log.addLog("Player %i reached level %i\n", id, level);
}

void BackEnd::parsePin(std::istringstream &)
{
}

void BackEnd::parsePex(std::istringstream &iss)
{
	int id;
	std::string err;

	if (!(iss >> id) || iss >> err)
		return;
	if (_players.find(id) == _players.end())
		return;
	_log.addLog("Player %i in team %s was ejected\n", id,
		_players.at(id)->getTeamName().c_str());
}

void BackEnd::parsePbc(std::istringstream &iss)
{
	int id;
	std::string message;

	if (!(iss >> id))
		return;
	std::getline(iss, message);
	if (_players.find(id) == _players.end())
		return;
	_players.at(id)->setLastBroadcast(message);
	std::string team(_players.at(id)->getTeamName());
	std::ostringstream oss;

	oss << id << " (" << team << "): ";
	_broadcasts.push(oss.str());
	_log.addLog("Player %i in team %s just said [%s]\n", id,
		_players.at(id)->getTeamName().c_str(), message.c_str());
}

void BackEnd::parsePic(std::istringstream &iss)
{
	sf::Vector2i pos;
	int level;
	int id;
	int check;
	std::vector<int> players;

	if (!(iss >> pos.x >> pos.y >> level >> id))
		return;
	if (_players.find(id) == _players.end())
		return;
	while (iss >> check) {
		if (_players.find(check) == _players.end())
			return;
		players.push_back(check);
	}
	_players.at(id)->setIncantating(true);
	Tile &tile = _tiles.at(
		std::to_string(pos.x) + ';' + std::to_string(pos.y));
	tile.shape.setTexture(&_grassIncantation);
	_incantations.push_back({pos, level, id, players, ON_HOLD});
	_log.addLog("An incantation was started at (%i;%i)\n", pos.x, pos.y);
}

void BackEnd::parsePie(std::istringstream &iss)
{
	sf::Vector2i pos;
	int result;
	std::string err;

	if (!(iss >> pos.x >> pos.y >> result) || iss >> err)
		return;
	if (result != 1 && result != 0)
		return;
	for (auto &tmp : _incantations)
		if (tmp.pos == pos) {
			tmp.state = (result) ? SUCCESS : FAILURE;
			_log.addLog("The incantation at (%i;%i) %s\n", pos.x,
				pos.y, (result) ? "Succeed" : "Failed");
		}
	for (auto &player : _players) {
		if (player.second->getPos() == pos && result)
			player.second->levelUp();
		if (player.second->getPos() == pos)
			player.second->setIncantating(false);
	}
	Tile &tile = _tiles.at(
		std::to_string(pos.x) + ';' + std::to_string(pos.y));
	tile.shape.setTexture(&_grass);
}

void BackEnd::parsePfk(std::istringstream &iss)
{
	int id;
	std::string err;

	if (!(iss >> id) || iss >> err)
		return;
	if (_players.find(id) == _players.end())
		return;
	_players.at(id)->setLayingEgg(true);
	_log.addLog("Player %i in team %s is laying an egg\n", id,
		_players.at(id)->getTeamName().c_str());
}

void BackEnd::parsePdr(std::istringstream &iss)
{
	int id;
	int resource;
	std::string err;

	if (!(iss >> id >> resource) || iss >> err)
		return;
	if (_players.find(id) == _players.end())
		return;
	sf::Vector2i pos(_players.at(id)->getPos());
	_players.at(id)->set(static_cast<Resources>(resource));
	Tile &tile = _tiles.at(
		std::to_string(pos.x) + ';' + std::to_string(pos.y));
	tile.resources[resource].quantity += 1;
	_log.addLog("Player %i dropped %s at (%i;%i)\n", id,
		intToResource(resource), pos.x, pos.y);
	if (tile.resources[resource].quantity > 1)
		tile.resources[resource].shape.setTextureRect(
			tile.resources[resource].multiple);
	else
		tile.resources[resource].shape.setTextureRect(
			tile.resources[resource].single);
}

void BackEnd::parsePgt(std::istringstream &iss)
{
	int id;
	int resource;
	std::string err;

	if (!(iss >> id >> resource) || iss >> err)
		return;
	if (_players.find(id) == _players.end())
		return;

	sf::Vector2i pos(_players.at(id)->getPos());
	Tile &tile = _tiles.at(
		std::to_string(pos.x) + ';' + std::to_string(pos.y));
	tile.resources[resource].quantity -= 1;
	if (tile.resources[resource].quantity > 1)
		tile.resources[resource].shape.setTextureRect(
			tile.resources[resource].multiple);
	else
		tile.resources[resource].shape.setTextureRect(
			tile.resources[resource].single);
	_log.addLog("Player %i gathered %s from (%i;%i)\n", id,
		intToResource(resource), pos.x, pos.y);
	_players.at(id)->take(static_cast<Resources>(resource));
}

void BackEnd::parsePdi(std::istringstream &iss)
{
	int id;
	std::string err;

	if (!(iss >> id) || iss >> err)
		return;
	if (_players.find(id) == _players.end())
		return;
	_log.addLog("Player %i in team %s starved to death\n", id,
		_players.at(id)->getTeamName().c_str());
	_players.erase(id);
}

void BackEnd::parseEnw(std::istringstream &iss)
{
	int id;
	std::string teamName;
	sf::Vector2i pos;
	std::string err;

	if (!(iss >> id >> teamName >> pos.x >> pos.y) || iss >> err)
		return;
	if (_eggs.find(id) != _eggs.end())
		_eggs.erase(id);
	_eggs.insert({id, {id, false, pos, teamName, sf::RectangleShape(
		sf::Vector2f(_tileWidth / 2, _tileWidth / 2)), _egg}});
	_eggs.at(id).shape.setPosition(pos.x * _tileWidth + (_tileWidth / 1.8),
		pos.y * _tileWidth + (_tileWidth / 2));
	_eggs.at(id).shape.setTexture(&_eggs.at(id).texture);
	_eggs.at(id).shape.setTextureRect(sf::IntRect(0, 0, 48, 48));
	_log.addLog("Player %i in team %s laid an egg\n", id, teamName.c_str());
}

void BackEnd::parseEht(std::istringstream &iss)
{
	int id;
	std::string err;

	if (!(iss >> id) || iss >> err)
		return;
	if (_eggs.find(id) == _eggs.end())
		return;
	_eggs.at(id).hatching = true;
	_log.addLog("Egg %i in team %s is hatching\n", id,
		_eggs.at(id).teamName.c_str());
}

void BackEnd::parseEbo(std::istringstream &iss)
{
	int id;
	std::string err;
	if (!(iss >> id) || iss >> err)
		return;
	if (_eggs.find(id) == _eggs.end())
		return;
	_log.addLog("Player in team %s was hatched from the egg %i\n",
		_eggs.at(id).teamName.c_str(), id);
	_eggs.erase(id);
}

void BackEnd::parseEdi(std::istringstream &iss)
{
	int id;
	std::string err;
	if (!(iss >> id) || iss >> err)
		return;
	if (_eggs.find(id) == _eggs.end())
		return;
	_log.addLog("Egg %i in team %s died\n", id,
		_eggs.at(id).teamName.c_str());
	_eggs.erase(id);
}

void BackEnd::parseSgt(std::istringstream &iss)
{
	int timeUnit;

	if (!(iss >> timeUnit))
		return;
	_timeUnit = timeUnit;
}

void BackEnd::parseSst(std::istringstream &iss)
{
	parseSgt(iss);
}

void BackEnd::parseSeg(std::istringstream &iss)
{
	std::string team;
	std::string err;

	if (!(iss >> team) || iss >> err)
		return;
	_gameFinished = true;
	_winningTeam = team;
}

void BackEnd::parseSmg(std::istringstream &iss)
{
	std::string msg;
	std::string err;

	if (!(iss >> msg) || iss >> err)
		return;
	std::cout << "[SERVER] : " << msg << std::endl;
}

void BackEnd::parseSuc(std::istringstream &)
{
}

void BackEnd::parseSbp(std::istringstream &)
{
}

void BackEnd::parseFed(std::istringstream &iss)
{
	int id;
	std::string err;

	if (!(iss >> id) || iss >> err)
		return;
	if (_players.find(id) == _players.end())
		return;
	_players.at(id)->eat();
	_log.addLog("Player %i in team %s is eating\n", id,
		_players.at(id)->getTeamName().c_str());
}

const char *BackEnd::intToResource(int i)
{
	switch (static_cast<Resources >(i)) {
	case FOOD:
		return "FOOD";
	case LINEMATE:
		return "LINEMATE";
	case DERAUMERE:
		return "DERAUMERE";
	case SIBUR:
		return "SIBUR";
	case MENDIANE:
		return "MENDIANE";
	case PHIRAS:
		return "PHIRAS";
	case THYSTAME:
		return "THYSTAME";
	}
	return "UNKNOWN";
}
