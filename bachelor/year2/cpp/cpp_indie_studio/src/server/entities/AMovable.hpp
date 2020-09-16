/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Created by vincent.larcher@epitech.eu,
*/

#ifndef CPP_ARCADE_AMOVABLE_HPP
#define CPP_ARCADE_AMOVABLE_HPP

#include "AEntity.hpp"
#include "Element.hpp"

class AMovable : public AEntity {
public:
	AMovable(const std::pair<float, float> &, Element::Type type, int id);

	const std::pair<float, float> &getDirVector() const;
	void setDirVector(float, float);
	void setDirVector(const std::pair<float, float> &);

	void setPos(const std::pair<float, float> &);

	void setDir(int dir);
	int getDir();

	packageServerClient entityToPackage(const PackageType &type) override;

protected:
	std::pair<float, float> _dirVector;
	int _dir;
};

#endif //CPP_ARCADE_AMOVABLE_HPP
