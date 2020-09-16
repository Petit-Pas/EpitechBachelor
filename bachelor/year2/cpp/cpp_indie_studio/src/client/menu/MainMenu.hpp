//
// EPITECH PROJECT, 2018
// indie studio
// File description:
// main menu params
//

#ifndef MAIN_MENU_HPP_
#define MAIN_MENU_HPP_

enum MenuIds {
	WALLPAPER_MENU = 100,
	BUTTON_QUIT,
	BUTTON_CREATE,
	BUTTON_JOIN,
	/* insert more ids above */
	MENU_LAST_ID
};

enum MenuLobbyIds {
	WALLPAPER_LOBBY = MenuIds::MENU_LAST_ID,
	BUTTON_QUIT_LOBBY,
	BUTTON_LAUNCH,
	BUTTON_ACCEPT_FATE,
	BUTTON_RENAME,
	BUTTON_DEC,
	BUTTON_INC,
	COMBO_FIRST,
	/* 3 more for other players */
};

enum GameIds {
	WALLPAPER_GAME = COMBO_FIRST + 3,
};

#endif /* !MAIN_MENU_HPP_ */
