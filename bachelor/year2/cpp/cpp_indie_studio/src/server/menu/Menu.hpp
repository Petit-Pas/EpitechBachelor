//
// EPITECH PROJECT, 2018
// indie studio
// File description:
// menu
//

#ifndef MENU_HPP_
#define MENU_HPP_

#include "Server.hpp"
#include "PlayerCommunication.hpp"
#include "Lobby.hpp"
#include "MenuStruct.hpp"

class Menu {
public:
	Menu();
	~Menu();

private:

	void lobbyHandling();

	void checkClients();
	void playerQuit(size_t);
	void joinLobby(size_t);

	void checkLobbies();

	void checkGamesEnded();

	void sendLobbies(PlayerCommunication &);
	void sendLobbiesToAll();

private:
	ServerTCP _server;
	std::vector<Lobby> _lobbies;
	std::vector<Lobby> _ingame;
	std::vector<PlayerCommunication> _players;
	bool _newLobby;
};

#endif /* !MENU_HPP_ */
