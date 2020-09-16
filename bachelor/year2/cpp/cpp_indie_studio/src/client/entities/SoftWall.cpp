/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Internal functions
*/

#include <iostream>
#include "SoftWall.hpp"

ind::display::SoftWall::SoftWall(irr::video::IVideoDriver *driver, irr::scene::ISceneManager *smgr,
	irrklang::ISoundEngine *_soundEngine, const irr::core::vector2df &pos
) : AEntityClient(_soundEngine, pos, driver->getTexture(RESOURCE_DIR "media/stone01.png"),
	smgr->addAnimatedMeshSceneNode(smgr->getMesh(RESOURCE_DIR "media/block.obj")), {12, 12, 12}, false)
{
	int nb = std::rand() % 7 + 1;
	char buff[128];
	sprintf(buff, RESOURCE_DIR "media/stone%02i.png", nb);
	_node->setMaterialTexture(0, driver->getTexture(buff));
}
