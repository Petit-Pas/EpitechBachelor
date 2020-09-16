/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** Internal functions
*/

#ifndef ZAPPY_PLAYER_HPP
# define ZAPPY_PLAYER_HPP

#include <SFML/Graphics.hpp>
#include "Resources.hpp"

struct SkinInfo {
	sf::Vector2i pos;
	sf::Vector2i size;
};

struct PlayerSkin {
	std::vector<SkinInfo> idle;
	std::vector<SkinInfo> moveRight;
	std::vector<SkinInfo> moveLeft;
	std::vector<SkinInfo> moveUp;
	std::vector<SkinInfo> moveDown;
};

enum Move {
	NONE = -1,
	TOUP = 0,
	TORIGHT,
	TODOWN,
	TOLEFT,
};

class Player {
public:
	Player(int id, int orientation, int level, const std::string &teamName, int teamId, const sf::Vector2i &pos,
		const std::vector<int> &inventory, bool incantating, bool layingEgg, float tileWidth, sf::Texture *texture
	);
	void initSkin(int teamId);
	int getId() const;
	int getOrientation() const;
	void setOrientation(int orientation);
	int getLevel() const;
	void setLevel(int level);
	void levelUp();
	const std::string &getTeamName() const;
	void setTeamName(const std::string &teamName);
	const sf::Vector2i &getPos() const;
	void setPos(const sf::Vector2i &pos);
	void setShapePos(const sf::Vector2i &pos);
	void setRect(size_t idx);
	const std::vector<int> &getInventory() const;
	void setInventory(const std::vector<int> &inventory);
	bool isIncantating() const;
	void setIncantating(bool incantating);
	bool isLayingEgg() const;
	void setLayingEgg(bool layingEgg);
	void take(Resources resources);
	void set(Resources resources);
	void move();
	void stepMove();
	void eat();
	void dump() const;
	const char *intToDirection(int direction) const;
	void dumpInventory() const;
	const sf::RectangleShape &getShape() const;
	void setOutlineColor(const sf::Color &color);
	void setOutlineThickness(float f);
	const std::string &getLastBroadcast() const;
	void setLastBroadcast(const std::string &lastBroadcast);
private:
	int id;
	int orientation;
	int level;
	std::string teamName;
	std::string lastBroadcast;
	sf::Vector2i pos;
	std::vector<int> inventory;
	bool incantating;
	bool layingEgg;
	float tileWidth;
	sf::RectangleShape shape;
	sf::Texture *texture;
	PlayerSkin skin;
	Move moving;
	sf::Vector2f nextPos;
	sf::Vector2f moveSize;
	size_t moveIdx;
	//region Skins vector

	std::vector<PlayerSkin> skins {
		{
			{{{48, 0}, {48, 48}}},
			{{{48, 96}, {48, 48}}, {{96, 96}, {48, 48}}, {{0, 96}, {48, 48}}},
			{{{48, 48}, {48, 48}}, {{96, 48}, {48, 48}}, {{0, 48}, {48, 48}}},
			{{{48, 144}, {48, 48}}, {{96, 144}, {48, 48}}, {{0, 144}, {48, 48}}},
			{{{48, 0}, {48, 48}}, {{96, 0}, {48, 48}}, {{0, 0}, {48, 48}}}
		},{
			{{{192, 0}, {48, 48}}},
			{{{192, 96}, {48, 48}}, {{240, 96}, {48, 48}}, {{144, 96}, {48, 48}}},
			{{{192, 48}, {48, 48}}, {{240, 48}, {48, 48}}, {{144, 48}, {48, 48}}},
			{{{192, 144}, {48, 48}}, {{240, 144}, {48, 48}}, {{144, 144}, {48, 48}}},
			{{{192, 0}, {48, 48}}, {{240, 0}, {48, 48}}, {{144, 0}, {48, 48}}}
		}, {
			{{{336, 0}, {48, 48}}},
			{{{336, 96}, {48, 48}}, {{384, 96}, {48, 48}}, {{288, 96}, {48, 48}}},
			{{{336, 48}, {48, 48}}, {{384, 48}, {48, 48}}, {{288, 48}, {48, 48}}},
			{{{336, 144}, {48, 48}}, {{384, 144}, {48, 48}}, {{288, 144}, {48, 48}}},
			{{{336, 0}, {48, 48}}, {{384, 0}, {48, 48}}, {{288, 0}, {48, 48}}}
		}, {
			{{{480, 0}, {48, 48}}},
			{{{480, 96}, {48, 48}}, {{528, 96}, {48, 48}}, {{432, 96}, {48, 48}}},
			{{{480, 48}, {48, 48}}, {{528, 48}, {48, 48}}, {{432, 48}, {48, 48}}},
			{{{480, 144}, {48, 48}}, {{528, 144}, {48, 48}}, {{432, 144}, {48, 48}}},
			{{{480, 0}, {48, 48}}, {{528, 0}, {48, 48}}, {{432, 0}, {48, 48}}},
		}, {
			{{{48, 192}, {48, 48}}},
			{{{48, 288}, {48, 48}}, {{96, 288}, {48, 48}}, {{0, 299}, {48, 48}}},
			{{{48, 240}, {48, 48}}, {{96, 240}, {48, 48}}, {{0, 240}, {48, 48}}},
			{{{48, 336}, {48, 48}}, {{96, 336}, {48, 48}}, {{0, 336}, {48, 48}}},
			{{{48, 192}, {48, 48}}, {{96, 192}, {48, 48}}, {{0, 192}, {48, 48}}}
		},{
			{{{192, 192}, {48, 48}}},
			{{{192, 288}, {48, 48}}, {{240, 288}, {48, 48}}, {{144, 288}, {48, 48}}},
			{{{192, 240}, {48, 48}}, {{240, 240}, {48, 48}}, {{144, 240}, {48, 48}}},
			{{{192, 336}, {48, 48}}, {{240, 336}, {48, 48}}, {{144, 336}, {48, 48}}},
			{{{192, 192}, {48, 48}}, {{240, 192}, {48, 48}}, {{144, 192}, {48, 48}}}
		}, {
			{{{336, 192}, {48, 48}}},
			{{{336, 288}, {48, 48}}, {{384, 288}, {48, 48}}, {{288, 288}, {48, 48}}},
			{{{336, 240}, {48, 48}}, {{384, 240}, {48, 48}}, {{288, 240}, {48, 48}}},
			{{{336, 336}, {48, 48}}, {{384, 366}, {48, 48}}, {{288, 336}, {48, 48}}},
			{{{336, 192}, {48, 48}}, {{384, 192}, {48, 48}}, {{288, 192}, {48, 48}}}
		}, {
			{{{480, 192}, {48, 48}}},
			{{{480, 288}, {48, 48}}, {{528, 288}, {48, 48}}, {{432, 288}, {48, 48}}},
			{{{480, 240}, {48, 48}}, {{528, 240}, {48, 48}}, {{432, 240}, {48, 48}}},
			{{{480, 336}, {48, 48}}, {{528, 336}, {48, 48}}, {{432, 336}, {48, 48}}},
			{{{480, 192}, {48, 48}}, {{528, 192}, {48, 48}}, {{432, 192}, {48, 48}}},

		}
	};
	//endregion
};

#endif //ZAPPY_PLAYER_HPP