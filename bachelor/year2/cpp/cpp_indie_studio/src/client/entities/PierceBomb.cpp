/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Internal functions
*/

#include "PierceBomb.hpp"

ind::display::PierceBomb::PierceBomb(irr::video::IVideoDriver *, irr::scene::ISceneManager *smgr,
	irrklang::ISoundEngine *_soundEngine, const irr::core::vector2df &pos
) : AEntityClient(_soundEngine, pos, nullptr,
	smgr->addAnimatedMeshSceneNode(smgr->getMesh(RESOURCE_DIR "media/GoldPickaxe.obj")), {25, 25, 25}, true)
{
	auto *rotation = smgr->createRotationAnimator({0, 0.5f, 0});
	auto *hover = smgr->createFlyStraightAnimator({_node->getPosition().X, 5, _node->getPosition().Z},
		{_node->getPosition().X, 15, _node->getPosition().Z}, 1000, true, true);
	_node->addAnimator(rotation);
	_node->addAnimator(hover);
}
