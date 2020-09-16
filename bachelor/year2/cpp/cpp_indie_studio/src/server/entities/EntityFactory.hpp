//
// EPITECH PROJECT, 2018
// cpp_arcade
// File description:
// Factory of entities
//

#ifndef ENTITY_FACTORY_HPP_
# define ENTITY_FACTORY_HPP_

#include <unordered_map>
#include "IEntity.hpp"

class EntityFactory {
public:
	EntityFactory() = default;
	EntityFactory(const EntityFactory &);
	EntityFactory &operator=(const EntityFactory &);

	~EntityFactory() = default;

	void addEntity(const char &, IEntity *(*)(const std::pair<float, float> &));
	IEntity *createEntity(const char &, const std::pair<float, float> &);

	const std::unordered_map<char, IEntity *(*)(const std::pair<float, float> &)> &getMap() const;

private:
	std::unordered_map<char, IEntity *(*)(const std::pair<float, float> &)> _factoryMap;
};

#endif /* !ENTITY_FACTORY_HPP_ */
