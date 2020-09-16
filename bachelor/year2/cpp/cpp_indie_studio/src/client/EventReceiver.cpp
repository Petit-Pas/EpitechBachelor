/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Internal functions
*/

#include "EventReceiver.hpp"
#include "ClientReceiveUpdate.hpp"

bool ind::display::EventReceiver::IsKeyDown(ind::EKEY_CODE keyCode) const
{
	return KeyIsDown[keyCode];
}

bool ind::display::EventReceiver::OnEvent(const irr::SEvent &event)
{
	if (event.EventType == irr::EET_KEY_INPUT_EVENT) {
		KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
	}
	if (event.EventType == irr::EET_GUI_EVENT) {
		irr::s32 id = event.GUIEvent.Caller->getID();
		if (event.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED) {
			switch (id) {
			case 10:
				_device->closeDevice();
			default:
				break;
			}
		}
	}
	return false;
}

ind::display::EventReceiver::EventReceiver(irr::IrrlichtDevice *device) : _device(device)
{
	for (bool &i : KeyIsDown)
		i = false;
}
