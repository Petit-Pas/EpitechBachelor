//
// EPITECH PROJECT, 2018
// indie studio
// File description:
// menu
//

#include <iostream>
#include "Menu.hpp"
#include "Type.hpp"

Menu::Menu() : _server("any", 256, 4242), _newLobby(false)
{
	lobbyHandling();
}

Menu::~Menu()
{
}

void Menu::lobbyHandling()
{
	while (true) {
		if (_server.acceptClient(false) != -1) {
			_players.push_back(_server.popClient());
			sendLobbies(_players.back());
		}
		checkClients();
		checkLobbies();
		checkGamesEnded();
	}
}

void Menu::checkClients()
{
	for (size_t i = 0; _players.size() > i; i++) {
		TypesMenu type;
		bool info = _players[i].recvData<TypesMenu>(type);

		if (info && type == TypesMenu::JOIN_LOBBY) {
			joinLobby(i);
			break;
		} else if ((info && type == TypesMenu::QUIT) || !_players[i].isOpen()) {
			playerQuit(i);
			break;
		}
	}
}

void Menu::playerQuit(size_t i)
{
	_players[i].clear();
	_players.erase(_players.begin() + i);
}

void Menu::joinLobby(size_t i)
{
	int nb;
	bool info = _players[i].recvData<int>(nb, true);

	if (info && nb >= 0) {
		if (static_cast<int>(_lobbies.size()) > nb && _lobbies[nb].addPlayer(_players[i])) {
			_players.erase(_players.begin() + i);
			_newLobby = true;
		} else {
			_players[i].sendData<>(TypesMenu::CONFIRM);
			_players[i].sendData<int>(false);
		}
	} else if (info && nb == -1) {
		_lobbies.push_back(Lobby(_players[i]));
		_players[i].sendData<>(TypesMenu::CONFIRM);
		_players[i].sendData<int>(true);
		_players[i].sendData<int>(true);
		_players.erase(_players.begin() + i);
		_newLobby = true;
	} else {
		playerQuit(i);
	}
}

void Menu::checkLobbies()
{
	bool status = _newLobby;

	for (size_t i = 0; _lobbies.size() > i; i++) {
		_lobbies[i].update();
		while (_lobbies[i].playerQuit()) {
			status = true;
			_players.push_back(_lobbies[i].extractPlayer());
		}
		if (_lobbies[i].valid() == false) {
			_lobbies.erase(_lobbies.begin() + i);
			break;
		}
		if (_lobbies[i].gameLaunch()) {
			status = true;
			_lobbies[i].launchGame();
			_ingame.push_back(_lobbies[i]);
			_lobbies.erase(_lobbies.begin() + i);
		}
		if (!_lobbies[i].isUpToDate()) {
			status = true;
		}
	}
	if (status) {
		sendLobbiesToAll();
		_newLobby = false;
	}
}

void Menu::checkGamesEnded()
{
	for (size_t i = 0; i < _ingame.size(); i++) {
		if (!_ingame[i].isRunning()) {
			auto add = _ingame[i].getAllPlayers();
			_players.insert(_players.end(), add.begin(), add.end());
			_newLobby = true;
		}
	}
}

void Menu::sendLobbies(PlayerCommunication &player)
{
	player.sendData<>(TypesMenu::LIST_LOBBY);
	player.sendData<>(_lobbies.size());
	for (const auto &lobby : _lobbies) {
		player.sendData<>(lobby.serialize());
	}
}

void Menu::sendLobbiesToAll()
{
	for (auto &player : _players) {
		sendLobbies(player);
	}
}
