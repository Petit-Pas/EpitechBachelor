/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Created by vincent.larcher@epitech.eu,
*/

#ifndef CPP_ARCADE_AENTITY_HPP
#define CPP_ARCADE_AENTITY_HPP

#include <vector>
#include "IEntity.hpp"
#include "Element.hpp"
#include "Packet.hpp"

class AEntity : public IEntity {
public:
	AEntity(const std::pair<float, float> &, Element::Type, int id);
	~AEntity() override = default;

	const std::pair<float, float> &getPos() const override;

	Element::Type getType() const override;

	Element::State getState() const override;
	void setState(const Element::State &) override;

	int getId() const;

	virtual bool isHitBigHitBox(std::pair<float, float> pos) const;
	virtual bool isHitNormalHitBox(std::pair<float, float> pos) const;

	virtual packageServerClient entityToPackage(const PackageType &type);

protected:
	int _id;
	Element::Type _type;
	Element::State _state;
	std::pair<float, float> _pos;
	std::pair<float, float> _hitboxY;
	std::pair<float, float> _hitboxX;
};

template<typename T, typename U>
std::pair<T, U> operator+(const std::pair<T, U> &l, const std::pair<T, U> &r)
{
	return {l.first + r.first, l.second + r.second};
}

#endif //CPP_ARCADE_AENTITY_HPP
