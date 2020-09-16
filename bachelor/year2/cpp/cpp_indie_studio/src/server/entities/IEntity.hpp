/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Created by vincent.larcher@epitech.eu,
*/

#ifndef CPP_ARCADE_IENTITY_HPP
#define CPP_ARCADE_IENTITY_HPP

#include "Element.hpp"

class IEntity {
public:

	virtual ~IEntity() = default;
	/**
	 * Return the positions of the entity
	 * @return (float y, float x)
	 */
	virtual const std::pair<float, float> &getPos() const = 0;

	/**
	 * Return his type of entity (ally, enemy ...)
	 * @return enum Type
	 */
	virtual Element::Type getType() const = 0;

	/**
	 * Return his state (weak, pray, bonus, malus, invulnerable ...)
	 * @return enum State
	 */
	virtual Element::State getState() const = 0;
	virtual void setState(const Element::State &) = 0;
};

#endif //CPP_ARCADE_IENTITY_HPP
