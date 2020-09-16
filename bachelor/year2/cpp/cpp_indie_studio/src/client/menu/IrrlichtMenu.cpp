//
// EPITECH PROJECT, 2018
// indie studio
// File description:
// Irrlicht menu
//

#include <iostream>
#include <stdexcept>

#include "IrrlichtMenu.hpp"

IrrlichtMenu::IrrlichtMenu()
{
	createDevice();
}

IrrlichtMenu::~IrrlichtMenu()
{
	closeDevice();
}

void IrrlichtMenu::createDevice()
{
	_device = irr::createDevice(irr::video::EDT_OPENGL, irr::core::dimension2d<irr::u32>(1900, 1080));
	if (_device == nullptr)
		throw std::runtime_error("Cannot create irrlicht graphic driver");
	_device->setWindowCaption(L"Bomberman - Menu");
	_device->setResizable(true);

	_driver = _device->getVideoDriver();
	_env = _device->getGUIEnvironment();

	auto skin = _env->getSkin();
	auto fnt = _env->getFont(RESOURCE_DIR "media/GUI/myfont.xml");

	skin->setFont(fnt);

	skin->setColor(irr::gui::EGDC_BUTTON_TEXT, irr::video::SColor(255, 255, 255, 255));

	_smgr = _device->getSceneManager();
	_camera = _smgr->addCameraSceneNode(nullptr, irr::core::vector3df(-20, 0, 0), irr::core::vector3df(0, 0, 0));
	_camera->setFarValue(10000.0f);
	_smgr->addLightSceneNode(0, irr::core::vector3df(200,200,200),
				 irr::video::SColorf(1.0f,1.0f,1.0f),2000);
	_smgr->setAmbientLight(irr::video::SColorf(0.3f,0.3f,0.3f));
	_soundEngine = irrklang::createIrrKlangDevice();
	_soundEngine->stopAllSounds();
	_soundEngine->setSoundVolume(0.6);
	_soundEngine->play2D(RESOURCE_DIR "sounds/background/Haggstrom.ogg", true);

	_listBox = nullptr;
}

void IrrlichtMenu::closeDevice()
{
	_soundEngine->stopAllSounds();
	_soundEngine->drop();
	_players.clear();
	_device->drop();
}

void IrrlichtMenu::setPlayer(size_t idPlayer, size_t skinId, int human)
{
	if (_players.find(idPlayer) != _players.end()) {
		_players[idPlayer]->modifyTexture(skinId, human);
	} else {
		_players[idPlayer] = std::make_unique<PlayerVisualisation>(_smgr, _driver, skinId, human, idPlayer - 10);
	}
}

void IrrlichtMenu::unsetPlayer(size_t idPlayer)
{
	if (_players.find(idPlayer) != _players.end()) {
		_players.erase(idPlayer);
	}
}

void IrrlichtMenu::drawWindow()
{
	if (_device->isWindowActive()) {
		_driver->beginScene(true, true, irr::video::SColor(255, 66, 66, 66));
		_env->drawAll();
		_smgr->drawAll();
		_driver->endScene();
	}
}

bool IrrlichtMenu::ok() const
{
	return (_device->run() && _driver);
}

irr::scene::ISceneNode *IrrlichtMenu::getObj() const
{
	irr::core::triangle3df tmp;
	irr::core::vector3df tmp2;

	auto cursor = _device->getCursorControl();
	auto ray = _smgr->getSceneCollisionManager()->getRayFromScreenCoordinates(cursor->getPosition(), _camera);
	auto node = _smgr->getSceneCollisionManager()->getSceneNodeFromRayBB(ray);
	return (node);
}
