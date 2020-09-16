//
// EPITECH PROJECT, 2018
// indie studio
// File description:
// menu event for irrlicht (ya!)
//

#include <iostream>
#include "EventMenuReceiver.hpp"
#include "Type.hpp"
#include "MainMenu.hpp"
#include "MenuStruct.hpp"

EventMenuReceiver::EventMenuReceiver(IrrlichtMenu *graphMenu, std::shared_ptr<ClientTCP> client) : _client(client),
												   _graphMenu(graphMenu), _waitForLobby(false), _obj(nullptr)
{
}

EventMenuReceiver::~EventMenuReceiver()
{
}

void EventMenuReceiver::addEdit(irr::gui::IGUIEditBox *edit)
{
	_lobbyName = edit;
}

bool EventMenuReceiver::OnEvent(const irr::SEvent &event)
{
	if (event.EventType == irr::EET_GUI_EVENT) {
		irr::s32 id = event.GUIEvent.Caller->getID();
		switch (event.GUIEvent.EventType) {
		case (irr::gui::EGET_BUTTON_CLICKED):

			switch (id) {
			case (MenuIds::BUTTON_QUIT):
				_graphMenu->_device->closeDevice();
				break;
			case (MenuIds::BUTTON_CREATE):
				joinLobby(-1);
				break;
			case (MenuIds::BUTTON_JOIN): {
				auto lobId = _graphMenu->_listBox->getSelected();
				if (lobId != -1)
					joinLobby(lobId);
				break;
			}
			case (MenuLobbyIds::BUTTON_QUIT_LOBBY):
				_client->sendData<>(TypesLobby::QUIT);
				setWaiting(true);
				break;
			case (MenuLobbyIds::BUTTON_ACCEPT_FATE):
				setWaiting(false);
				break;
			case (MenuLobbyIds::BUTTON_LAUNCH):
				_client->sendData<>(TypesLobby::LAUNCH_GAME);
				break;
			case (MenuLobbyIds::BUTTON_DEC):
				_client->sendData<>(TypesLobby::SKIN_DOWN);
				break;
			case (MenuLobbyIds::BUTTON_INC):
				_client->sendData<>(TypesLobby::SKIN_UP);
				break;
			default:
				return (false);
				break;
			}
			return (true);
			break;
		case (irr::gui::EGET_COMBO_BOX_CHANGED):
			if (id > MenuLobbyIds::COMBO_FIRST && id < MenuLobbyIds::COMBO_FIRST + 4) {
				changeIaLevel(id - MenuLobbyIds::COMBO_FIRST, (irr::gui::IGUIComboBox *)(event.GUIEvent.Caller));
			}
			break;
		case (irr::gui::EGET_EDITBOX_CHANGED): {
			_client->sendData<>(TypesLobby::RENAME);
			irr::core::stringw name = _lobbyName->getText();
			char c_name[32];
			memset(c_name, 0, sizeof(c_name));
			if (name.size() != 0)
				std::wcstombs(c_name, name.c_str(), name.size());
			_client->sendData<char[32]>(c_name);
			break;
		}

		default:
			return (false);
		}
		return (true);
	} else if (event.EventType == irr::EET_MOUSE_INPUT_EVENT) {
		return (OnMouseEvent(event));
	}
	return (false);
}

bool EventMenuReceiver::OnMouseEvent(const irr::SEvent &event)
{
	switch(event.MouseInput.Event) {
	case irr::EMIE_LMOUSE_PRESSED_DOWN:
		_obj = _graphMenu->getObj();
		_cursorPos.X = event.MouseInput.X;
		_cursorPos.Y = event.MouseInput.Y;
		break;

	case irr::EMIE_LMOUSE_LEFT_UP:
		if (_obj != nullptr) {
			_obj->setRotation(irr::core::vector3df(0, 0, 0));
			_obj = nullptr;
		}
		break;

	case irr::EMIE_MOUSE_MOVED:
		if (_obj != nullptr) {
			updateRotation({event.MouseInput.X, event.MouseInput.Y});
			_cursorPos.X = event.MouseInput.X;
			_cursorPos.Y = event.MouseInput.Y;
		}
		break;

	default:
		return (false);
		break;
	}
	return (false);
}

void EventMenuReceiver::updateRotation(irr::core::position2di newPos)
{
	auto cursorDelta = newPos - _cursorPos;

	if (cursorDelta.X || cursorDelta.Y) {
		auto deltaYaw = cursorDelta.X;
		rotateObj(irr::core::vector3df(0, deltaYaw, 0));
		//uncomment following part for full rotation
		//auto deltaPitch = -cursorDelta.Y;
		//rotateObj(irr::core::vector3df(deltaPitch, 0, 0));
	}
}

void EventMenuReceiver::rotateObj(irr::core::vector3df rot)
{
	irr::core::matrix4 m;
        irr::core::matrix4 n;

        m.setRotationDegrees(_obj->getRotation());
        n.setRotationDegrees(rot);
        m *= n;
        _obj->setRotation(m.getRotationDegrees());
}

void EventMenuReceiver::changeIaLevel(size_t id, irr::gui::IGUIComboBox *combo)
{
	_client->sendData<>(TypesLobby::CHANGE_IA);
	iaInfo ia;

	memset(&ia, 0, sizeof(ia));
	ia.id = id;
	ia.type = static_cast<ind::ia::Types>(combo->getItemData(combo->getSelected()));
	_client->sendData<>(ia);
}

void EventMenuReceiver::joinLobby(int id)
{
	_client->sendData<TypesMenu>(TypesMenu::JOIN_LOBBY);
	_client->sendData<int>(id);
	setWaiting(true);
}

bool EventMenuReceiver::isWaiting() const
{
	return (_waitForLobby);
}

void EventMenuReceiver::setWaiting(bool status)
{
	_waitForLobby = status;
}
