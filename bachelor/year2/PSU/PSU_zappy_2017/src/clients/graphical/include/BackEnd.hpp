/*
** EPITECH PROJECT, 2018
** Graphical
** File description:
** Created by martin.van-elslande@epitech.eu,
*/

#ifndef GRAPHICAL_BACKEND_HPP
#define GRAPHICAL_BACKEND_HPP

#include <SFML/Graphics.hpp>
#include <memory>
#include "Resources.hpp"
#include "Connection.hpp"
#include "Player.hpp"
#include "Tile.hpp"
#include "Log.hpp"
#include "Egg.hpp"
#include "Incantation.hpp"

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

const float WIDTH = 1920.0f;

const float HEIGHT = 1080.0f;

class BackEnd {
public:
	BackEnd(const std::string &addr, int port, sf::Vector2i &_mapSize,
		std::map<std::string, Tile> &_tiles,
		std::map<int, std::shared_ptr<Player>> &_players, std::map<int, Egg> &eggs,
		std::vector<Incantation> &incantations,
		std::vector<std::string> &_teams,
		int &_timeUnit, bool &_gameFinished, std::string &_winningTeam,
		float &_tileWidth, Log &log
	);
	~BackEnd() = default;

	void refresh();

	//region Getters / Setters

	bool isMapSet() const;

	const std::map<std::string, Tile> &getTiles() const
	{
		return _tiles;
	};

	const std::vector<std::string> &getTeams() const
	{
		return _teams;
	};

	int getTimeUnit() const
	{
		return _timeUnit;
	};

	bool isGameFinished() const
	{
		return _gameFinished;
	};

	const std::string &getWinningTeam() const
	{
		return _winningTeam;
	};

	float getTileWidth() const
	{
		return _tileWidth;
	};

	const sf::Vector2i &getMapSize() const
	{
		return _mapSize;
	};
	bool hasBroadcast() const
	{
		return !_broadcasts.empty();
	};
	std::string getNextBroadcast();
	//endregion

private:
	Connection _connection;

	sf::Vector2i &_mapSize;
	std::map<std::string, Tile> &_tiles;
	std::map<int, std::shared_ptr<Player>> &_players;
	std::map<int, Egg> &_eggs;
	std::vector<Incantation> &_incantations;
	std::vector<std::string> &_teams;
	int &_timeUnit;
	bool &_gameFinished;
	std::string &_winningTeam;
	float &_tileWidth;
	Log &_log;
	std::queue<std::string> _broadcasts;
	sf::Texture _grass;
	sf::Texture _grassIncantation;
	sf::Texture _egg;
	sf::Texture _resources;
	sf::Texture _character;

	const char *intToResource(int i);
	void addResourcesToTile(int *q, Tile &tile);

	//region Server messages parsing

	void parseMsg(const std::string &msg);
	void parseMsz(std::istringstream &iss);
	void parseBct(std::istringstream &iss);
	void parseTna(std::istringstream &iss);
	void parsePnw(std::istringstream &iss);
	void parsePpo(std::istringstream &iss);
	void parsePlv(std::istringstream &iss);
	void parsePin(std::istringstream &iss);
	void parsePex(std::istringstream &iss);
	void parsePbc(std::istringstream &iss);
	void parsePic(std::istringstream &iss);
	void parsePie(std::istringstream &iss);
	void parsePfk(std::istringstream &iss);
	void parsePdr(std::istringstream &iss);
	void parsePgt(std::istringstream &iss);
	void parsePdi(std::istringstream &iss);
	void parseEnw(std::istringstream &iss);
	void parseEht(std::istringstream &iss);
	void parseEbo(std::istringstream &iss);
	void parseEdi(std::istringstream &iss);
	void parseSgt(std::istringstream &iss);
	void parseSst(std::istringstream &iss);
	void parseSeg(std::istringstream &iss);
	void parseSmg(std::istringstream &iss);
	void parseSuc(std::istringstream &iss);
	void parseSbp(std::istringstream &iss);
	void parseFed(std::istringstream &iss);
	//endregion

	std::map<std::string, void (BackEnd::*)(std::istringstream &)> _parse{
		{"msz", &BackEnd::parseMsz}, {"bct", &BackEnd::parseBct},
		{"tna", &BackEnd::parseTna}, {"pnw", &BackEnd::parsePnw},
		{"ppo", &BackEnd::parsePpo}, {"plv", &BackEnd::parsePlv},
		{"pin", &BackEnd::parsePin}, {"pex", &BackEnd::parsePex},
		{"pbc", &BackEnd::parsePbc}, {"pic", &BackEnd::parsePic},
		{"pie", &BackEnd::parsePie}, {"pfk", &BackEnd::parsePfk},
		{"pdr", &BackEnd::parsePdr}, {"pgt", &BackEnd::parsePgt},
		{"pdi", &BackEnd::parsePdi}, {"enw", &BackEnd::parseEnw},
		{"eht", &BackEnd::parseEht}, {"ebo", &BackEnd::parseEbo},
		{"edi", &BackEnd::parseEdi}, {"sgt", &BackEnd::parseSgt},
		{"sst", &BackEnd::parseSst}, {"seg", &BackEnd::parseSeg},
		{"smg", &BackEnd::parseSmg}, {"suc", &BackEnd::parseSuc},
		{"sbp", &BackEnd::parseSbp}, {"fed", &BackEnd::parseFed}
	};
};

#endif //GRAPHICAL_BACKEND_HPP
