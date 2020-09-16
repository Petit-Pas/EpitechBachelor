//
// EPITECH PROJECT, 2018
// indie studio
// File description:
// menu for lobby
//

#include <iostream>
#include "MenuLobbyClient.hpp"
#include "MainMenu.hpp"
#include "Type.hpp"
#include "Client.hpp"
#include "ButtonEasyAdd.hpp"

MenuLobbyClient::MenuLobbyClient(IrrlichtMenu &graphMenu, std::shared_ptr<ClientTCP> client, EventMenuReceiver *receiver
) : _graphMenu(&graphMenu), _client(client), _receiver(receiver), _kicked(false), _admin(false),
	_lobby(graphMenu, client)
{
	int admin;
	_client->recvData<>(admin, true);
	_admin = admin;
	_lobby.setAdmin(_admin);
	setEnv();
	while (_graphMenu->ok() && _client->isOpen() && !_kicked) {
		_graphMenu->drawWindow();
		getServerInfo();
	}
	if (!_receiver->isWaiting()) {
		irr::gui::IGUIWindow *window = _graphMenu->_env->addWindow(
			irr::core::rect<irr::s32>(100, 100, 600, 250), true, L"Warning");

		_graphMenu->_env->addStaticText(L"You have been kicked from the lobby",
			irr::core::rect<irr::s32>(30, 30, 470, 90), false, true, window);
		window->getCloseButton()->setVisible(false);

		_graphMenu->_env->addButton(irr::core::rect<irr::s32>(100, 100, 400, 100 + 32), window,
			MenuLobbyIds::BUTTON_ACCEPT_FATE, L"Accept fate", L"returns to menu");
		_receiver->setWaiting(true);
		while (_graphMenu->ok() && _receiver->isWaiting() && _client->isOpen()) {
			_graphMenu->drawWindow();
		}
	}
	_graphMenu->_players.clear();
}

MenuLobbyClient::~MenuLobbyClient()
{
}

void MenuLobbyClient::getServerInfo()
{
	TypesLobby type;

	if (_client->recvData<TypesLobby>(type)) {
		switch (type) {
		case (TypesLobby::KICKED):
			_kicked = true;
			break;
		case (TypesLobby::LIST_LOBBY_PARAMS):
			_lobby.update();
			break;
		case (TypesLobby::LAUNCH_GAME): {
			_graphMenu->closeDevice();
			ind::display::Client client(_lobby.getId(), "Bomberman", _client, _lobby.getSkins());
			_kicked = true;
			_receiver->setWaiting(true);
			_graphMenu->createDevice();
			_graphMenu->_device->setEventReceiver(_receiver);
			break;
		}
		default:
			break;
		}
	}
}

void MenuLobbyClient::setEnv()
{
	_graphMenu->_env->clear();
	ButtonEasyAdd::addButton(_graphMenu->_env, _graphMenu->_driver, MenuLobbyIds::WALLPAPER_LOBBY);
	ButtonEasyAdd::addButton(_graphMenu->_env, _graphMenu->_driver, MenuLobbyIds::BUTTON_QUIT_LOBBY);
	if (_admin) {
		auto editBox = _graphMenu->_env->addEditBox(L"Lobby", irr::core::rect<irr::s32>(800, 10, 1100, 50));
		_receiver->addEdit(editBox);
		editBox->setMax(31);
		editBox->setDrawBackground(false);
		ButtonEasyAdd::addButton(_graphMenu->_env, _graphMenu->_driver, MenuLobbyIds::BUTTON_LAUNCH);
	}
	_lobby.setEnv();
}
