//
// EPITECH PROJECT, 2018
// zappy
// File description:
// map of server
//

#ifndef ELEMENT_MAP_HPP_
#define ELEMENT_MAP_HPP_

#include <unordered_map>
#include <string>

class Orientation;

#include "Movement.hpp"
#include "Tile.hpp"

class ElementMap
{
public:
	ElementMap();
	ElementMap(const ElementMap &);

	void setSize(const Size &);
	Position convertPos(const Position &) const;

	Tile &accessTile(int , int);
	Tile &accessTile(const Position &);

	const Tile &accessTile(size_t, size_t) const;

	const Size &getSize() const;

	const std::vector<std::vector<Tile>> &getMap() const;

private:
	std::vector<std::vector<Tile>> _map;
	Size _size;
};

std::ostream &operator<<(std::ostream &, const ElementMap &);

#endif /* !ELEMENT_MAP_HPP_ */
