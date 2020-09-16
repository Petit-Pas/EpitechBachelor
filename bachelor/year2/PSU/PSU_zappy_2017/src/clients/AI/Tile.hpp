//
// EPITECH PROJECT, 2018
// Zappy
// File description:
// tile definition
//

#ifndef TILE_HPP_
#define TILE_HPP_

#include <unordered_map>

class Tile
{
public:
	Tile() = default;
	Tile(const Tile &);

	/* create a tile from string */
	static Tile createTile(const std::string &line);

	void setTileContent(const std::string &, size_t);
	void setTileContent(const Tile &);

	void addTileContent(const std::string &, size_t);

	bool retrieveTileContent(const std::string &, size_t);
	void withdrawItem(const std::string &item);
	void withdrawItem(const std::string &item, size_t quantity);

	void update();

	const std::unordered_map<std::string, size_t> &getElements() const;

	size_t getNbContent(const std::string &) const;
private:
	std::unordered_map<std::string, size_t> _tile;
	static const size_t DEFAULT_RELIABILITY;
};

std::ostream &operator<<(std::ostream &, const Tile &);

#endif /* !TILE_HPP_ */
