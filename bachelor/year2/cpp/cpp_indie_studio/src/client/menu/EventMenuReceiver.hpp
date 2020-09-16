//
// EPITECH PROJECT, 2018
// indie studio
// File description:
// menu event for irrlicht (ya !)
//

#ifndef EVENT_MENU_RECEIVER_HPP_
#define EVENT_MENU_RECEIVER_HPP_

#include <memory>
#include <irrlicht.h>

#include "IrrlichtMenu.hpp"
#include "ClientTCP.hpp"

class EventMenuReceiver : public irr::IEventReceiver {
public:
	EventMenuReceiver(IrrlichtMenu *, std::shared_ptr<ClientTCP>);
	virtual ~EventMenuReceiver();

	virtual bool OnEvent(const irr::SEvent &);
	bool isWaiting() const;
	void setWaiting(bool);
	void addEdit(irr::gui::IGUIEditBox *);

private:
	void joinLobby(int);
	void changeIaLevel(size_t, irr::gui::IGUIComboBox *);

	void updateRotation(irr::core::position2di);
	void rotateObj(irr::core::vector3df rot);

	bool OnMouseEvent(const irr::SEvent &);

private:
	std::shared_ptr<ClientTCP> _client;
	IrrlichtMenu *_graphMenu;
	irr::gui::IGUIEditBox *_lobbyName;
	bool _waitForLobby;
	irr::scene::ISceneNode *_obj;
	irr::core::position2di _cursorPos;
};

#endif /* !EVENT_MENU_RECEIVER_HPP_ */
