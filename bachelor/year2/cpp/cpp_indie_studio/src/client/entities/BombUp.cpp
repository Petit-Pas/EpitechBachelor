/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Internal functions
*/

#include "BombUp.hpp"

ind::display::BombUp::BombUp(irr::video::IVideoDriver *, irr::scene::ISceneManager *smgr,
	irrklang::ISoundEngine *_soundEngine, const irr::core::vector2df &pos
) : AEntityClient(_soundEngine, pos, nullptr,
	smgr->addAnimatedMeshSceneNode(smgr->getMesh(RESOURCE_DIR "media/tntpack.obj")), {4.5, 4.5, 4.5}, false)
{
	auto *rotation = smgr->createRotationAnimator({0, 0.5f, 0});
	auto *hover = smgr->createFlyStraightAnimator({_node->getPosition().X, 5, _node->getPosition().Z},
		{_node->getPosition().X, 15, _node->getPosition().Z}, 1000, true, true);
	_node->addAnimator(rotation);
	_node->addAnimator(hover);
}
