/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Internal functions
*/

#include <ClientReceiveUpdate.hpp>
#include "AEntityClient.hpp"
#include "Client.hpp"

ind::display::AEntityClient::AEntityClient(irrklang::ISoundEngine *_soundEngine, const irr::core::vector2df &pos,
	irr::video::ITexture *texture, irr::scene::IAnimatedMeshSceneNode *node, const irr::core::vector3df &scale,
	bool hasAlpha, bool needCulling
) : _pos(pos), _texture(texture), _soundEngine(_soundEngine), _node(node)
{
	if (_texture)
		_node->setMaterialTexture(0, _texture);
	_node->setPosition({static_cast<irr::f32>((pos.X - 0.5) * 24 - X_OFFSET), abs(node->getBoundingBox().MinEdge.Y),
		static_cast<irr::f32>((pos.Y - 0.5) * 24 - Y_OFFSET)});
	_node->setScale(scale);
	_node->setMaterialFlag(irr::video::EMF_NORMALIZE_NORMALS, true);
	_node->setMaterialFlag(irr::video::EMF_ANISOTROPIC_FILTER, true);
	_node->setMaterialFlag(irr::video::EMF_BACK_FACE_CULLING, needCulling);
	if (hasAlpha) {
		_node->setMaterialFlag(irr::video::EMF_BACK_FACE_CULLING, false);
		_node->setMaterialType(irr::video::EMT_TRANSPARENT_ALPHA_CHANNEL);
	} else
		_node->setMaterialType(irr::video::EMT_SOLID);
	_node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	_node->getMaterial(0).TextureLayer->TextureWrapU = irr::video::ETC_CLAMP_TO_EDGE;
	_node->getMaterial(0).TextureLayer->TextureWrapV = irr::video::ETC_CLAMP_TO_EDGE;
	_node->setMD2Animation(irr::scene::EMAT_STAND);
}

ind::display::AEntityClient::~AEntityClient()
{
	if (!endG) {
		_node->removeAll();
		_node->remove();
	}
}

void ind::display::AEntityClient::setScale(const irr::core::vector3df &scale)
{
	_node->setScale(scale);
}

void ind::display::AEntityClient::setPos(const irr::core::vector2df &pos)
{
	_node->setPosition(
		{static_cast<irr::f32>((pos.X - 0.5) * 24 - X_OFFSET), abs(_node->getBoundingBox().MinEdge.Y),
			static_cast<irr::f32>((pos.Y - 0.5) * 24 - Y_OFFSET)});
	_pos = pos;
}

const irr::core::vector2df &ind::display::AEntityClient::getPos() const
{
	return _pos;
}

void ind::display::AEntityClient::setRotation(const dir::directions &direction)
{
	switch (direction) {
	case dir::NONE:
		break;
	case dir::UP:
		_node->setRotation({0, 0, 0});
		break;
	case dir::DOWN:
		_node->setRotation({0, 180, 0});
		break;
	case dir::LEFT:
		_node->setRotation({0, -90, 0});
		break;
	case dir::RIGHT:
		_node->setRotation({0, 90, 0});
		break;
	}
}

void ind::display::AEntityClient::setTexture(irr::video::ITexture *_texture)
{
	_node->setMaterialTexture(0, _texture);
	AEntityClient::_texture = _texture;
}

void ind::display::AEntityClient::setIdle()
{
}

void ind::display::AEntityClient::setMoving()
{
}

void ind::display::AEntityClient::setDying()
{
}

int ind::display::AEntityClient::getFrame()
{
	return static_cast<int>(_node->getFrameNr());
}

void ind::display::AEntityClient::stopAnimation()
{
	_node->setAnimationSpeed(0);
}


