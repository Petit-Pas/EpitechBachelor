/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Internal functions
*/

#include "HardWall.hpp"

ind::display::HardWall::HardWall(irr::video::IVideoDriver *driver, irr::scene::ISceneManager *smgr,
	irrklang::ISoundEngine *_soundEngine, const irr::core::vector2df &pos
) : AEntityClient(_soundEngine, pos, driver->getTexture(RESOURCE_DIR "media/iron_block.png"),
	smgr->addAnimatedMeshSceneNode(smgr->getMesh(RESOURCE_DIR "media/block.obj")), {12, 12, 12}, false)
{
}
