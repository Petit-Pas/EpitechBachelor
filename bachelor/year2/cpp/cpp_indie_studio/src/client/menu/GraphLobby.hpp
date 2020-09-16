//
// EPITECH PROJECT, 2018
// indie studio
// File description:
// graphical lobby
//

#ifndef GRAPH_LOBBY_HPP_
#define GRAPH_LOBBY_HPP_

#include <memory>
#include <irrlicht.h>

#include "IrrlichtMenu.hpp"
#include "ClientTCP.hpp"
#include "MenuStruct.hpp"

class GraphLobby {
public:
	GraphLobby(IrrlichtMenu &, std::shared_ptr<ClientTCP>);
	~GraphLobby();

	void update();
	void setAdmin(bool);
	void setEnv();

	size_t getId() const;
	const std::vector<size_t> &getSkins() const;
private:
	void updatePlayers(const fullLobby &, const int i);

private:
	IrrlichtMenu *_graphMenu;
	std::shared_ptr<ClientTCP> _client;
	irr::gui::IGUIStaticText *_lobbyName;
	std::vector<irr::gui::IGUIStaticText *> _text;
	std::vector<irr::gui::IGUIComboBox *> _boxes;
	std::vector<size_t> _skins;
	irr::gui::IGUIButton *_nextBtn;
	irr::gui::IGUIButton *_prevBtn;
	bool _admin;
	size_t _id;

	const std::vector<irr::core::position2di> POS_BTN_PREV = {
		{165, 600},
		{590, 600},
		{1025, 600},
		{1450, 600},
	};

	const std::vector<irr::core::position2di> POS_BTN_NEXT = {
		{285, 600},
		{715, 600},
		{1150, 600},
		{1575, 600},
	};
};

#endif /* !GRAPH_LOBBY_HPP_ */
