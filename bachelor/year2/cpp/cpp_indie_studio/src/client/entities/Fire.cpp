/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Internal functions
*/

#include "Fire.hpp"

ind::display::Fire::Fire(irr::video::IVideoDriver *driver, irr::scene::ISceneManager *smgr,
	irrklang::ISoundEngine *_soundEngine, const irr::core::vector2df &pos
) : AEntityClient(_soundEngine, pos, nullptr,
	smgr->addAnimatedMeshSceneNode(smgr->getMesh(RESOURCE_DIR "media/Fire.obj")), {20, 25, 20}, true)
{
	irr::core::array<irr::video::ITexture *> textureVector = {};
	for (int j = 1; j <= 32; ++j) {
		char buff[128];
		sprintf(buff, RESOURCE_DIR "media/Fire/fire_%04i.png", j);
		auto texture = driver->getTexture(buff);
		textureVector.push_back(texture);
	}
	auto fireAnimation = smgr->createTextureAnimator(textureVector, 50, true);
	_node->addAnimator(fireAnimation);
	_soundEngine->play2D(RESOURCE_DIR "sounds/block/fire/ignite.ogg");
	_fireSound = _soundEngine->play2D(RESOURCE_DIR "sounds/block/fire/fire.ogg", true, false, true);
	_fireSound->setVolume(0.1);
}

ind::display::Fire::~Fire()
{
	if (_fireSound)
		_fireSound->stop();
	auto sound = _soundEngine->play2D(RESOURCE_DIR "sounds/block/fire/fizz.ogg", false, false, true);
	sound->setVolume(0.1);
}
