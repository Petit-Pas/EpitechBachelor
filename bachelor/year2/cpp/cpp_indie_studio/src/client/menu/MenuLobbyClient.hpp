//
// EPITECH PROJECT, 2018
// indie studio*
// File description:
// menu for lobby
//

#ifndef MENU_LOBBY_CLIENT_HPP_
#define MENU_LOBBY_CLIENT_HPP_

#include <irrlicht.h>
#include <memory>

#include "ClientTCP.hpp"
#include "GraphLobby.hpp"
#include "EventMenuReceiver.hpp"

class MenuLobbyClient {
public:
	MenuLobbyClient(IrrlichtMenu &, std::shared_ptr<ClientTCP>, EventMenuReceiver *);
	~MenuLobbyClient();

private:
	void setEnv();
	void getServerInfo();

private:
	IrrlichtMenu *_graphMenu;
	std::shared_ptr<ClientTCP> _client;
	EventMenuReceiver *_receiver;
	bool _kicked;
	bool _admin;

	GraphLobby _lobby;
};

#endif /* !MENU_LOBBY_CLIENT_HPP_ */
