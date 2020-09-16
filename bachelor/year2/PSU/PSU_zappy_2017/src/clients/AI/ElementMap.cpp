//
// EPITECH PROJECT, 2018
// zappy
// File description:
// map server
//

#include "ElementMap.hpp"

ElementMap::ElementMap()
{
}

ElementMap::ElementMap(const ElementMap &map)
	: _map(map.getMap())
{
	_size = map.getSize();
}

void ElementMap::setSize(const Size &size)
{
	_size = size;
	_map.resize(size.height, std::vector<Tile>(size.width));
	for (auto &line : _map) {
		for (auto &tile : line) {
			tile.setTileContent("reliability", 0);
		}
	}
}

Position ElementMap::convertPos(const Position &originalPos) const
{
	Position pos = originalPos;

	pos.y = (pos.y + _size.height) % _size.height;
	pos.x = (pos.x + _size.width) % _size.width;
	return (pos);
}

Tile &ElementMap::accessTile(const Position &pos)
{
	const auto &realPos = convertPos(pos);

	return (_map[realPos.y][realPos.x]);
}

Tile &ElementMap::accessTile(int y, int x)
{
	const auto &realPos = convertPos({y, x});

	return (_map[realPos.y][realPos.x]);
}

const Tile &ElementMap::accessTile(size_t y, size_t x) const
{
	const auto realPos = convertPos({static_cast<int>(y), static_cast<int>(x)});

	return (_map.at(realPos.y).at(realPos.x));
}

const Size &ElementMap::getSize() const
{
	return (_size);
}

const std::vector<std::vector<Tile>> &ElementMap::getMap() const
{
	return (_map);
}

std::ostream &operator<<(std::ostream &os, const ElementMap &map)
{
	auto size = map.getSize();

	for (size_t y = 0; y < size.height; y++) {
		os << "[";
		for (size_t x = 0; x < size.width; x++) {
			os << map.accessTile(y, x);
			if (x + 1 < size.width)
				os << ", ";
		}
		os << "]" << std::endl;
	}
	return (os);
}
