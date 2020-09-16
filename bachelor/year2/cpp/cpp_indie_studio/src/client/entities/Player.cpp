/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Internal functions
*/

#include <iostream>
#include "Player.hpp"

ind::display::Player::Player(irr::video::IVideoDriver *driver, irr::scene::ISceneManager *smgr,
	irrklang::ISoundEngine *_soundEngine, const irr::core::vector2df &pos
	) : AEntityClient(_soundEngine, pos, nullptr,
	smgr->addAnimatedMeshSceneNode(smgr->getMesh(RESOURCE_DIR "media/CharacterAnimated.ms3d")), {10, 10, 10}, false,
	false), _moving(false)
{
	_node->setAnimationSpeed(30);
	auto sound = _soundEngine->play2D(RESOURCE_DIR "sounds/player/prepare_summon.ogg", false, false, true);
	sound->setVolume(0.1);
	setIdle();
}

ind::display::Player::~Player()
{
}

void ind::display::Player::setPos(const irr::core::vector2df &pos)
{
	if (!_moving)
		setMoving();
	_moving = true;
	static int sound = 0;
	if (sound == 5) {
		int nb = std::rand() % 6 + 1;
		char buff[128];
		sprintf(buff, RESOURCE_DIR "sounds/player/step/stone%i.ogg", nb);
		_soundEngine->play2D(buff);
		sound = 0;
	}
	_node->setAnimationSpeed(30);
	AEntityClient::setPos(pos);
	sound++;
}

void ind::display::Player::setIdle()
{
	_moving = false;
	_node->setFrameLoop(18, 37);
}

void ind::display::Player::setMoving()
{
	_node->setFrameLoop(0, 15);
}

void ind::display::Player::setDying()
{
	_moving = false;
	int nb = std::rand() % 2 + 1;
	char buff[128];
	sprintf(buff, RESOURCE_DIR "sounds/player/death%i.ogg", nb);
	_soundEngine->play2D(buff, false, false, true);
	_node->setFrameLoop(40, 100);
}

