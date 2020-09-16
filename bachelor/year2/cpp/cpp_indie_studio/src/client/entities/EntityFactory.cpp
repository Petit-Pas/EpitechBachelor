/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Internal functions
*/

#include "EntityFactory.hpp"
#include "Fire.hpp"
#include "Bomb.hpp"
#include "BombUp.hpp"
#include "FireUp.hpp"
#include "HardWall.hpp"
#include "PierceBomb.hpp"
#include "Player.hpp"
#include "SoftWall.hpp"
#include "SpeedUp.hpp"
#include "WalkThrough.hpp"

ind::display::EntityFactory::EntityFactory(irr::video::IVideoDriver *_driver, irr::scene::ISceneManager *_smgr,
	irrklang::ISoundEngine *_soundEngine
) : _driver(_driver), _smgr(_smgr), _soundEngine(_soundEngine),
	_dico({{Element::Type::BOMB, &EntityFactory::createBomb},
		{Element::Type::EMPTY, &EntityFactory::createEmpty},
		{Element::Type::BOMB_UP, &EntityFactory::createBombUp},
		{Element::Type::FIRE, &EntityFactory::createFire},
		{Element::Type::FIRE_UP, &EntityFactory::createFireUp},
		{Element::Type::HARDWALL, &EntityFactory::createHardWall},
		{Element::Type::SOFTWALL, &EntityFactory::createSoftWall},
		{Element::Type::PIERCE_BOMB, &EntityFactory::createPierceBomb},
		{Element::Type::PLAYER, &EntityFactory::createPlayer},
		{Element::Type::AI, &EntityFactory::createAI},
		{Element::Type::SPEED_UP, &EntityFactory::createSpeedUp},
		{Element::Type::WALK_THROUGH, &EntityFactory::createWalkThrough}})
{
}

std::shared_ptr<ind::display::AEntityClient> ind::display::EntityFactory::createBomb(const irr::core::vector2df &pos)
{
	return std::shared_ptr<ind::display::AEntityClient>(new Bomb(_driver, _smgr, _soundEngine, pos));
}

std::shared_ptr<ind::display::AEntityClient> ind::display::EntityFactory::createEmpty(const irr::core::vector2df &pos)
{
	return std::shared_ptr<ind::display::AEntityClient>(new Fire(_driver, _smgr, _soundEngine, pos));
}

std::shared_ptr<ind::display::AEntityClient> ind::display::EntityFactory::createBombUp(const irr::core::vector2df &pos)
{
	return std::shared_ptr<ind::display::AEntityClient>(new BombUp(_driver, _smgr, _soundEngine, pos));
}

std::shared_ptr<ind::display::AEntityClient> ind::display::EntityFactory::createFire(const irr::core::vector2df &pos)
{
	return std::shared_ptr<ind::display::AEntityClient>(new Fire(_driver, _smgr, _soundEngine, pos));
}

std::shared_ptr<ind::display::AEntityClient> ind::display::EntityFactory::createFireUp(const irr::core::vector2df &pos)
{
	return std::shared_ptr<ind::display::AEntityClient>(new FireUp(_driver, _smgr, _soundEngine, pos));
}

std::shared_ptr<ind::display::AEntityClient> ind::display::EntityFactory::createHardWall(const irr::core::vector2df &pos
)
{
	return std::shared_ptr<ind::display::AEntityClient>(new HardWall(_driver, _smgr, _soundEngine, pos));
}

std::shared_ptr<ind::display::AEntityClient> ind::display::EntityFactory::createPierceBomb(
	const irr::core::vector2df &pos
)
{
	return std::shared_ptr<ind::display::AEntityClient>(new PierceBomb(_driver, _smgr, _soundEngine, pos));
}

std::shared_ptr<ind::display::AEntityClient> ind::display::EntityFactory::createPlayer(const irr::core::vector2df &pos
)
{
	return std::shared_ptr<ind::display::AEntityClient>(new Player(_driver, _smgr, _soundEngine, pos));
}

std::shared_ptr<ind::display::AEntityClient> ind::display::EntityFactory::createAI(const irr::core::vector2df &pos
)
{
	return std::shared_ptr<ind::display::AEntityClient>(new Player(_driver, _smgr, _soundEngine, pos));
}

std::shared_ptr<ind::display::AEntityClient> ind::display::EntityFactory::createSoftWall(const irr::core::vector2df &pos
)
{
	return std::shared_ptr<ind::display::AEntityClient>(new SoftWall(_driver, _smgr, _soundEngine, pos));
}

std::shared_ptr<ind::display::AEntityClient> ind::display::EntityFactory::createSpeedUp(const irr::core::vector2df &pos
)
{
	return std::shared_ptr<ind::display::AEntityClient>(new SpeedUp(_driver, _smgr, _soundEngine, pos));
}

std::shared_ptr<ind::display::AEntityClient> ind::display::EntityFactory::createWalkThrough(
	const irr::core::vector2df &pos
)
{
	return std::shared_ptr<ind::display::AEntityClient>(new WalkThrough(_driver, _smgr, _soundEngine, pos));
}

std::shared_ptr<ind::display::AEntityClient> ind::display::EntityFactory::createEntity(Element::Type type,
	const irr::core::vector2df &pos
)
{
	if (_dico.find(type) == _dico.end())
		throw std::runtime_error("Entity Type");
	return (this->*(_dico[type]))(pos);
}
