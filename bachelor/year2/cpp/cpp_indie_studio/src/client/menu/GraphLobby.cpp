//
// EPITECH PROJECT, 2018
// indie studio
// File description:
// graphical lobby
//

#include <iostream>
#include "GraphLobby.hpp"
#include "IASetting.hpp"
#include "MainMenu.hpp"
#include "ButtonEasyAdd.hpp"

GraphLobby::GraphLobby(IrrlichtMenu &graphMenu, std::shared_ptr<ClientTCP> client) : _graphMenu(&graphMenu),
	_client(client), _admin(false), _id(10)
{
}

GraphLobby::~GraphLobby()
{
}

void GraphLobby::setEnv()
{
	if (!_admin) {
		_lobbyName = _graphMenu->_env->addStaticText(L"", irr::core::rect<irr::s32>(800, 10, 1100, 50), false, false);
		_lobbyName->setTextAlignment(irr::gui::EGUIA_CENTER, irr::gui::EGUIA_CENTER);
	}
	for (int i = 0; i < 4; i++) {
		_text.push_back(_graphMenu->_env->addStaticText(L"",
			irr::core::rect<irr::s32>(100 + i * 425, 150, 100 + i * 425 + 350, 200), false, false));
		_text.back()->setTextAlignment(irr::gui::EGUIA_CENTER, irr::gui::EGUIA_CENTER);
		if (_admin && i != 0) {
			_boxes.push_back(_graphMenu->_env->addComboBox(irr::core::rect<irr::s32>(100 + i * 425, 200, 100 + i * 425 + 350, 230), nullptr, MenuLobbyIds::COMBO_FIRST + i));
			for (auto &x: ind::ia::IA_MAPPING) {
				_boxes[i - 1]->addItem(std::wstring(x.second.begin(), x.second.end()).c_str(), x.first);
			}
		}
	}
	_prevBtn = ButtonEasyAdd::addButton(_graphMenu->_env, _graphMenu->_driver, MenuLobbyIds::BUTTON_DEC);
	_nextBtn = ButtonEasyAdd::addButton(_graphMenu->_env, _graphMenu->_driver, MenuLobbyIds::BUTTON_INC);
}

void GraphLobby::update()
{
	fullLobby lob;

	if (_client->recvData<>(lob, true)) {
		if (!_admin) {
			std::string str(lob.name);
			_lobbyName->setText(std::wstring(str.begin(), str.end()).c_str());
		}
		_skins.clear();
		for (int i = 0; i < lob.nb_persons; i++) {
			updatePlayers(lob, i);
		}
		for (int i = lob.nb_persons; i < 4; i++) {
			_text[i]->setText(L"Waiting Player...");

			_graphMenu->unsetPlayer(i + 10);
			if (_admin) {
				_boxes[i - 1]->setSelected(ind::ia::PLAYER - ind::ia::PLAYER);
			}
		}
		_id = lob.playId;
	}
}

void GraphLobby::updatePlayers(const fullLobby &lob, const int i)
{
	playerSerial player;
	std::string str;

	if (_client->recvData<>(player, true)) {
		if (lob.playId == player.id) {
			str = "You";
			_prevBtn->setRelativePosition(POS_BTN_PREV.at(i));
			_nextBtn->setRelativePosition(POS_BTN_NEXT.at(i));
		} else {
			str = ind::ia::IA_MAPPING.at(player.type) + " ";
			str += std::to_string(i + 1);
		}
		_text[i]->setText(std::wstring(str.begin(), str.end()).c_str());
		if (_admin && i != 0) {
			_boxes[i - 1]->setSelected(player.type);
		}
		_skins.push_back(player.skinId);
		_graphMenu->setPlayer(player.id, player.skinId, player.human);
	}
}

void GraphLobby::setAdmin(bool admin)
{
	_admin = admin;
}

size_t GraphLobby::getId() const
{
	return (_id);
}

const std::vector<size_t> &GraphLobby::getSkins() const
{
	return (_skins);
}
