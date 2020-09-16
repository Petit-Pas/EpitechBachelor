//
// EPITECH PROJECT, 2018
// indie studio
// File description:
// client menu
//

#include <iostream>
#include <stdexcept>
#include <irrlicht.h>
#include "MenuClient.hpp"
#include "Type.hpp"
#include "MainMenu.hpp"
#include "MenuLobbyClient.hpp"
#include "ButtonEasyAdd.hpp"

MenuClient::MenuClient(const std::string &ip, int port) : _client(std::make_shared<ClientTCP>(ip, port))
{
	setEnv();
	EventMenuReceiver receiver(&_graphMenu, _client);
	_graphMenu._device->setEventReceiver(&receiver);
	_receiver = &receiver;

	while (_graphMenu.ok() && _client->isOpen()) {
		getServerInfo();
		_graphMenu.drawWindow();
	}
}

MenuClient::~MenuClient()
{
}

void MenuClient::setEnv()
{
	_graphMenu._env->clear();
	ButtonEasyAdd::addButton(_graphMenu._env, _graphMenu._driver, MenuIds::WALLPAPER_MENU);
	ButtonEasyAdd::addButton(_graphMenu._env, _graphMenu._driver, MenuIds::BUTTON_QUIT);
	ButtonEasyAdd::addButton(_graphMenu._env, _graphMenu._driver, MenuIds::BUTTON_CREATE);
	ButtonEasyAdd::addButton(_graphMenu._env, _graphMenu._driver, MenuIds::BUTTON_JOIN);
	_graphMenu._env->addStaticText(L"Available Lobbies:", irr::core::rect<irr::s32>(1550, 80, 1850, 100), false);
	_graphMenu._listBox = _graphMenu._env->addListBox(irr::core::rect<irr::s32>(1550, 120, 1850, 400));
}

void MenuClient::getServerInfo()
{
	TypesMenu type;

	if (_client->recvData<>(type)) {
		if (type == TypesMenu::LIST_LOBBY) {
			getLobbies();
		} else if (type == TypesMenu::CONFIRM) {
			if (_receiver->isWaiting()) {
				_receiver->setWaiting(false);
				int stat;
				if (!_client->recvData(stat, true))
					return;
				if (stat)
					launchLobbyMenu();
				else {
					warnUser(L"The action has been rejected by the server");
				}
			}
		}
	}
}

void MenuClient::warnUser(const wchar_t *text)
{
	irr::gui::IGUIWindow *window = _graphMenu._env->addWindow(irr::core::rect<irr::s32>(100, 100, 400, 400), true,
		L"warning");

	_graphMenu._env->addStaticText(text, irr::core::rect<irr::s32>(35, 35, 250, 200), false, true, window);
}

void MenuClient::getLobbies()
{
	_lobbies.clear();
	size_t nb;

	if (_client->recvData<>(nb, true)) {
		while (nb > _lobbies.size()) {
			lobby lob;
			if (_client->recvData<>(lob, true)) {
				_lobbies.push_back(lob);
			} else {
				return;
			}
		}
		_graphMenu._listBox->clear();
		for (const auto &lob : _lobbies) {
			std::string str(lob.name);
			str += "   " + std::to_string(lob.nb_persons) + "/" + std::to_string(lob.max_persons);
			_graphMenu._listBox->addItem(std::wstring(str.begin(), str.end()).c_str());
		}
	}
}

void MenuClient::launchLobbyMenu()
{
	MenuLobbyClient menuLobby(_graphMenu, _client, _receiver);
	_receiver->setWaiting(false);
	setEnv();
}
