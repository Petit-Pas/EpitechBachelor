//
// EPITECH PROJECT, 2018
// indie studio
// File description:
// definition of ias
//

#include "IADefinition.hpp"

IADefinition::IADefinition(ind::ia::Types type) : _type(type), _skinId(0)
{
}

void IADefinition::setType(ind::ia::Types type)
{
	_type = type;
}

ind::ia::Types IADefinition::getType() const
{
	return (_type);
}

size_t IADefinition::getSkinId() const
{
	return (_skinId);
}
