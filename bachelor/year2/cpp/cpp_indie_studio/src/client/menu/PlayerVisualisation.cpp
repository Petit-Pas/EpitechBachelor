//
// EPITECH PROJECT, 2018
// indie studio
// File description:
// player visu for lobby
//

#include <iostream>
#include <stdexcept>
#include "PlayerVisualisation.hpp"
#include "SkinPicker.hpp"

PlayerVisualisation::PlayerVisualisation(irr::scene::ISceneManager *smgr, irr::video::IVideoDriver *driver, size_t skinId, int human, size_t nbPlayer)
	: _smgr(smgr), _driver(driver), _skinId(skinId), _human(human)
{
	auto mesh = smgr->getMesh(RESOURCE_DIR "media/CharacterAnimated.ms3d");
	if (mesh == nullptr)
		throw std::runtime_error("Cannot open : media/CharacterAnimated.ms3d");
	_node = _smgr->addAnimatedMeshSceneNode(mesh);
	if (_node == nullptr)
		throw std::runtime_error("Cannot open : media/CharacterAnimated.ms3d");

	_node->setMaterialFlag(irr::video::EMF_NORMALIZE_NORMALS, true);
        _node->setMaterialFlag(irr::video::EMF_ANISOTROPIC_FILTER, true);
        _node->setMaterialFlag(irr::video::EMF_BACK_FACE_CULLING, false);
	_node->setMaterialType(irr::video::EMT_SOLID);
        _node->setMaterialFlag(irr::video::EMF_LIGHTING, false);

	_node->setAnimationSpeed(20);
	_node->setFrameLoop(18, 37);
	setTexture(skinId, human);
	_node->setPosition({-5.0f, -1.5f, 15.0f - 9.5f * nbPlayer});
}

PlayerVisualisation::~PlayerVisualisation()
{
	_smgr->addToDeletionQueue(_node);
}

void PlayerVisualisation::setTexture(size_t skinId, int human)
{
	_skinId = skinId;
	_human = human;
	auto skins = (human) ? (ind::SKINS_PATH) : (ind::AI_SKINS);
	auto texturePath = skins[skinId % skins.size()];
	auto texture = _driver->getTexture(texturePath.c_str());
	if (texture == nullptr)
		throw std::runtime_error("Cannot open : " + texturePath);
	_node->setMaterialTexture(0, texture);
        _node->getMaterial(0).TextureLayer->TextureWrapU = irr::video::ETC_CLAMP_TO_EDGE;
        _node->getMaterial(0).TextureLayer->TextureWrapV = irr::video::ETC_CLAMP_TO_EDGE;
}

void PlayerVisualisation::modifyTexture(size_t skinId, int human)
{
	if (_human != human || skinId != _skinId)
		setTexture(skinId, human);
}

void PlayerVisualisation::rotate(irr::core::vector3df rot)
{
	irr::core::matrix4 m;
	irr::core::matrix4 n;
	m.setRotationDegrees(_node->getRotation());
	n.setRotationDegrees(rot);
	m *= n;
	_node->setRotation( m.getRotationDegrees());
	_node->updateAbsolutePosition();
}
