//
// EPITECH PROJECT, 2018
// indie studio
// File description:
// button setting for simple use
//

#ifndef BUTTONS_SETTING_HPP_
#define BUTTONS_SETTING_HPP_

#include <irrlicht.h>
#include <unordered_map>
#include <string>
#include "MainMenu.hpp"

struct ButtonSetting
{
	irr::core::rect<irr::s32> pos;
	std::string pathToNormal;
	std::string pathToPressed;
	std::wstring text;
};

static const std::unordered_map<size_t, ButtonSetting> DEFINED_BUTTONS = {
	/* menu */
	{MenuIds::WALLPAPER_MENU, {irr::core::rect<irr::s32>(0, 0, 1900, 1000),
				   RESOURCE_DIR "media/GUI/bombermenu.jpg", RESOURCE_DIR "media/GUI/bombermenu.jpg", L""}},
	{MenuIds::BUTTON_QUIT, {irr::core::rect<irr::s32>(80, 820, 560, 890),
				RESOURCE_DIR "media/GUI/button_quit_normal.jpg", RESOURCE_DIR "media/GUI/button_quit_hover.jpg", L""}},
	{MenuIds::BUTTON_CREATE, {irr::core::rect<irr::s32>(710, 820, 1190, 890),
				  RESOURCE_DIR "media/GUI/button_create_normal.jpg", RESOURCE_DIR "media/GUI/button_create_hover.jpg", L""}},
	{MenuIds::BUTTON_JOIN, {irr::core::rect<irr::s32>(1340, 820, 1820, 890),
				RESOURCE_DIR "media/GUI/button_join_normal.jpg", RESOURCE_DIR "media/GUI/button_join_hover.jpg", L""}},

	/* lobby */
	{MenuLobbyIds::WALLPAPER_LOBBY, {irr::core::rect<irr::s32>(0, 0, 1900, 1000),
					 RESOURCE_DIR "media/GUI/minecraft image.jpg", RESOURCE_DIR "media/GUI/minecraft image.jpg", L""}},
	{MenuLobbyIds::BUTTON_LAUNCH, {irr::core::rect<irr::s32>(320, 820, 800, 890),
				       RESOURCE_DIR "media/GUI/button_normal.jpg", RESOURCE_DIR "media/GUI/button_hover.jpg", L"Launch"}},
	{MenuLobbyIds::BUTTON_QUIT_LOBBY, {irr::core::rect<irr::s32>(1100, 820, 1580, 890),
				      RESOURCE_DIR "media/GUI/button_normal.jpg", RESOURCE_DIR "media/GUI/button_hover.jpg", L"Quit"}},
	{MenuLobbyIds::BUTTON_DEC, {irr::core::rect<irr::s32>(10, 0, 110, 32),
				      RESOURCE_DIR "media/GUI/button_normal.jpg", RESOURCE_DIR "media/GUI/button_hover.jpg", L"Prev"}},
	{MenuLobbyIds::BUTTON_INC, {irr::core::rect<irr::s32>(10, 0, 110, 32),
				      RESOURCE_DIR "media/GUI/button_normal.jpg", RESOURCE_DIR "media/GUI/button_hover.jpg", L"Next"}},

	/* game */
	{GameIds::WALLPAPER_GAME, {irr::core::rect<irr::s32>(0, 0, 1900, 1000),
					 RESOURCE_DIR "media/GUI/background_game_blur.jpg", RESOURCE_DIR "media/GUI/background_game_blur.jpg", L""}},
};

#endif /* !BUTTONS_SETTING_HPP_ */
