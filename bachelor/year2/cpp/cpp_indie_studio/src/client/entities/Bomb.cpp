/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Internal functions
*/

#include <iostream>
#include "Bomb.hpp"

ind::display::Bomb::Bomb(irr::video::IVideoDriver *, irr::scene::ISceneManager *smgr,
	irrklang::ISoundEngine *_soundEngine, const irr::core::vector2df &pos
) : AEntityClient(_soundEngine, pos, nullptr,
	smgr->addAnimatedMeshSceneNode(smgr->getMesh(RESOURCE_DIR "media/tnt.obj")), {12, 12, 12}, false)
{
	_soundEngine->play2D(RESOURCE_DIR "sounds/block/bomb/fuse.ogg");
}

ind::display::Bomb::~Bomb()
{
	int nb = std::rand() % 3 + 1;
	char buff[128];
	sprintf(buff, RESOURCE_DIR "sounds/block/bomb/explode%i.ogg", nb);
	auto sound = _soundEngine->play2D(buff, false, false, true);
	sound->setVolume(0.2);
}
