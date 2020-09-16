/*
** EPITECH PROJECT, 2018
** Graphical
** File description:
** Created by martin.van-elslande@epitech.eu,
*/

#ifndef GRAPHICAL_INTERFACE_HPP
#define GRAPHICAL_INTERFACE_HPP

#include <string>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <memory>
#include "Connection.hpp"
#include "BackEnd.hpp"
#include "Log.hpp"
#include "PlayerTracker.hpp"

class Interface {
public:
	Interface(const std::string &addr, int port);
	~Interface();

	void run();
private:
	void displayManager();
	void eventManager();
	void keyboardManager(sf::Event &event);
	void simpleKeyManager(sf::Event &event);
	void clickManager(const sf::Event::MouseButtonEvent &);
	void dumpResourcesOnTile(const std::map<int, Resource> &resources);
	void dumpPlayerOnTile(const Tile *tile);
	void dumpEggOnTile(const Tile *tile);

	/* Shared part */
	sf::Vector2i _mapSize;
	std::map<std::string, Tile> _tiles;
	std::map<int, std::shared_ptr<Player>> _players;
	std::map<int, Egg> _eggs;
	std::vector<Incantation> _incantations;
	std::vector<std::string> _teams;
	int _timeUnit;
	bool _gameFinished;
	std::string _winningTeam;
	float _tileWidth;
	std::unique_ptr<Tile> _lastTileClicked;

	Log _log;
	PlayerTracker _tracker;
	BackEnd _backend;
	sf::RenderWindow _window;
	sf::View _view;
	sf::Font _font;
	sf::Clock _clock;
	sf::Clock _moveClock;
	int _zoomIdx;
	bool _showTracker;
	bool _showLog;
	bool _showHelp;
};

#endif //GRAPHICAL_INTERFACE_HPP
