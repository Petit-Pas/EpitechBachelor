//
// EPITECH PROJECT, 2018
// Zappy
// File description:
// Tiles
//

#include <iostream>
#include "Tile.hpp"
#include "SplitUtils.hpp"

const size_t Tile::DEFAULT_RELIABILITY = 5;

Tile::Tile(const Tile &tile) : _tile(tile.getElements())
{
}

Tile Tile::createTile(const std::string &line)
{
	auto elems = SplitUtils::split(line, ' ');
	Tile tile;

	for (const auto &elem : elems) {
		tile.addTileContent(elem, 1);
	}
	tile.setTileContent("reliability", DEFAULT_RELIABILITY);
	return (tile);
}

void Tile::setTileContent(const std::string &content, size_t nb)
{
	_tile[content] = nb;
}

void Tile::setTileContent(const Tile &tile)
{
	_tile = tile.getElements();
}

void Tile::addTileContent(const std::string &content, size_t nb)
{
	setTileContent(content, getNbContent(content) + nb);
}

void Tile::withdrawItem(const std::string &item)
{
	auto it = _tile.find(item);
	if (it != _tile.end() && it->second > 0) {
		_tile[item]--;
	}
}

void Tile::withdrawItem(const std::string &item, size_t quantity)
{
	auto it = _tile.find(item);
	if (it != _tile.end()) {
		_tile[item] = quantity;
	}
}

void Tile::update()
{
	if (_tile.find("reliability") == _tile.end())
		_tile["reliability"] = 0;
	if (_tile["reliability"] != 0) {
		_tile["reliability"] -= 1;
		if (_tile["reliability"] == 0) {
			_tile.clear();
			_tile["reliability"] = 0;
		}
	}
}

const std::unordered_map<std::string, size_t> &Tile::getElements() const
{
	return (_tile);
}

size_t Tile::getNbContent(const std::string &content) const
{
	if (_tile.find(content) != _tile.end())
		return (_tile.at(content));
	return (0);
}

std::ostream &operator<<(std::ostream &os, const Tile &tile)
{
	for (const auto &elem : tile.getElements()) {
		os << elem.first << " " << elem.second << ", ";
	}
	return (os);
}
