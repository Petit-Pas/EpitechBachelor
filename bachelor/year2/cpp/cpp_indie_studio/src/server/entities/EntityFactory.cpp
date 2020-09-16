//
// EPITECH PROJECT, 2018
// cpp_arcade
// File description:
// Factory of entities
//

#include "EntityFactory.hpp"

EntityFactory::EntityFactory(const EntityFactory &other)
{
	_factoryMap = other.getMap();
}

EntityFactory &EntityFactory::operator=(const EntityFactory &other)
{
	_factoryMap = other.getMap();
	return (*this);
}

void EntityFactory::addEntity(const char &id, IEntity *(*createFunction)(const std::pair<float, float> &))
{
	_factoryMap[id] = createFunction;
}

IEntity *EntityFactory::createEntity(const char &id, const std::pair<float, float> &pos)
{
	if (_factoryMap.find(id) == _factoryMap.end())
		return (nullptr);
	return (_factoryMap[id](pos));
}

const std::unordered_map<char, IEntity *(*)(const std::pair<float, float> &)> &EntityFactory::getMap() const
{
	return (_factoryMap);
}
