//
// EPITECH PROJECT, 2018
// indie studio
// File description:
// client menu
//

#ifndef MENU_CLIENT_HPP_
#define MENU_CLIENT_HPP_

#include <memory>
#include <irrlicht.h>

#include "IrrlichtMenu.hpp"
#include "ClientTCP.hpp"
#include "MenuStruct.hpp"
#include "EventMenuReceiver.hpp"

class MenuClient {
public:
	MenuClient(const std::string &ip, int port);
	~MenuClient();

private:
	void setEnv();
	void getServerInfo();
	void getLobbies();
	void warnUser(const wchar_t *);
	void launchLobbyMenu();
private:
	std::shared_ptr<ClientTCP> _client;
	std::vector<lobby> _lobbies;
	IrrlichtMenu _graphMenu;
	EventMenuReceiver *_receiver;
};

#endif /* !MENU_CLIENT_HPP_ */
