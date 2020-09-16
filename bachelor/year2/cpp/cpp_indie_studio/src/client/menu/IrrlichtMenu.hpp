//
// EPITECH PROJECT, 2018
// indie studio
// File description:
// Irrlicht menu
//

#ifndef INDIE_IRRLICHT_MENU_HPP_
#define INDIE_IRRLICHT_MENU_HPP_

#include <unordered_map>
#include <memory>

#include <irrlicht.h>
#include <irrKlang.h>

#include "PlayerVisualisation.hpp"

class IrrlichtMenu {
public:
	IrrlichtMenu();
	~IrrlichtMenu();

	void createDevice();
	void closeDevice();
	void drawWindow();

	bool ok() const;

	/* scene player managing */
	void setPlayer(size_t idPlayer, size_t skinId, int human);
	void unsetPlayer(size_t idPlayer);
	irr::scene::ISceneNode *getObj() const;
public:
	irr::IrrlichtDevice *_device;
	irr::video::IVideoDriver *_driver;
	irr::gui::IGUIEnvironment *_env;
	irr::gui::IGUIListBox *_listBox;//create device does not set this
	irr::scene::ISceneManager *_smgr;
	irr::scene::ICameraSceneNode *_camera;
	std::unordered_map<size_t, std::unique_ptr<PlayerVisualisation>> _players;
	irrklang::ISoundEngine *_soundEngine;
};

#endif /* !INDIE_IRRLICHT_MENU_HPP_ */
