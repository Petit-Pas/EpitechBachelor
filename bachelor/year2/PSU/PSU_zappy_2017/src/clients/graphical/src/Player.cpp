/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** Internal functions
*/

#include <SFML/Graphics.hpp>
#include <Player.hpp>
#include <Direction.hpp>
#include <iostream>
#include "imgui.hpp"

Player::Player(int id, int orientation, int level,
	const std::__cxx11::basic_string<char> &teamName, int teamId,
	const sf::Vector2<int> &pos, const std::vector<int> &inventory,
	bool incantating, bool layingEgg, float tileWidth, sf::Texture *texture
)
	: id(id), orientation(orientation), level(level), teamName(teamName),
	pos(pos), inventory(inventory), incantating(incantating),
	layingEgg(layingEgg), tileWidth(tileWidth), texture(texture),
	moving(NONE), moveIdx(0)
{
	this->inventory[0] = 10;
	this->shape = sf::RectangleShape(
		sf::Vector2f(tileWidth / 3, tileWidth / 3));
	this->shape.setTexture(this->texture);
	skin = skins[teamId % 8];
}

int Player::getId() const
{
	return id;
}

int Player::getOrientation() const
{
	return orientation;
}

void Player::setOrientation(int orientation)
{
	Player::orientation = orientation;
}

int Player::getLevel() const
{
	return level;
}

const std::string &Player::getTeamName() const
{
	return teamName;
}

void Player::setTeamName(const std::string &teamName)
{
	Player::teamName = teamName;
}

const sf::Vector2i &Player::getPos() const
{
	return pos;
}

void Player::setPos(const sf::Vector2i &pos)
{
	Player::pos = pos;
}

void Player::setRect(size_t idx)
{
	switch (static_cast<Move>(orientation)) {
	case TOUP:
		shape.setTextureRect(sf::IntRect(skin.moveUp[0].pos.x,
			skin.moveUp[idx].pos.y, 48, 48));
		break;
	case TORIGHT:
		shape.setTextureRect(sf::IntRect(skin.moveRight[0].pos.x,
			skin.moveRight[idx].pos.y, 48, 48));
		break;
	case TODOWN:
		shape.setTextureRect(sf::IntRect(skin.moveDown[0].pos.x,
			skin.moveDown[idx].pos.y, 48, 48));
		break;
	case TOLEFT:
		shape.setTextureRect(sf::IntRect(skin.moveLeft[0].pos.x,
			skin.moveLeft[idx].pos.y, 48, 48));
		break;
	default:
		shape.setTextureRect(sf::IntRect(skin.idle[0].pos.x,
			skin.idle[0].pos.y, 48, 48));
		break;
	}
}

void Player::setShapePos(const sf::Vector2i &newPos)
{
	Player::shape.setPosition(
		(newPos.x + 1) * tileWidth - tileWidth / 2 - tileWidth / 6,
		(newPos.y + 1) * tileWidth - tileWidth / 2);
	setRect(0);
}

const std::vector<int> &Player::getInventory() const
{
	return inventory;
}

void Player::setInventory(const std::vector<int> &inventory)
{
	Player::inventory = inventory;
}

bool Player::isIncantating() const
{
	return incantating;
}

void Player::setIncantating(bool incantating)
{
	Player::incantating = incantating;
}

bool Player::isLayingEgg() const
{
	return layingEgg;
}

void Player::setLayingEgg(bool layingEgg)
{
	Player::layingEgg = layingEgg;
}

void Player::take(Resources resources)
{
	inventory[resources] += 1;
}

void Player::set(Resources resources)
{
	inventory[resources] -= 1;
}

void Player::stepMove()
{
	if (moving == NONE)
		return;
	moveIdx += 1;
	setRect(moveIdx % 3);
	shape.move(moveSize);
	if (shape.getPosition() == nextPos || moveIdx >= 6) {
		moving = NONE;
		moveIdx = 0;
		shape.setPosition(nextPos);
	}
}

void Player::move()
{
	moving = static_cast<Move>(orientation);
	float x = 0;
	float y = 0;
	switch (static_cast<Direction>(orientation)) {
	case UP:
		x = (pos.x + 1) * tileWidth - tileWidth / 2 - tileWidth / 6;
		y = (pos.y + 1) * tileWidth - tileWidth / 2 - tileWidth / 3;
		break;
	case RIGHT:
		x = (pos.x + 1) * tileWidth - tileWidth / 2;
		y = (pos.y + 1) * tileWidth - tileWidth / 2 - tileWidth / 6;
		break;
	case DOWN:
		x = (pos.x + 1) * tileWidth - tileWidth / 2 - tileWidth / 6;
		y = (pos.y + 1) * tileWidth - tileWidth / 2;
		break;
	case LEFT:
		x = (pos.x + 1) * tileWidth - tileWidth / 2 - tileWidth / 3;
		y = (pos.y + 1) * tileWidth - tileWidth / 2 - tileWidth / 6;
		break;
	default:
		break;
	}
	nextPos = {x, y};
	moveSize = {(x - shape.getPosition().x) / 6,
		(y - shape.getPosition().y) / 6};
	if (abs((int)(moveSize.x * 6)) >= 2 * tileWidth ||
		abs((int)(moveSize.y * 6)) >= 2 * tileWidth) {
		moving = NONE;
		shape.setPosition(nextPos);
	}
}

void Player::dump() const
{
	if (ImGui::TreeNode(std::to_string(id).c_str(), "Player %i", id)) {
		ImGui::BulletText("LEVEL %i", level);
		if (incantating)
			ImGui::BulletText("INCANTATING");
		if (layingEgg)
			ImGui::BulletText("LAYING AN EGG");
		ImGui::BulletText("LOOKING %s", intToDirection(orientation));
		ImGui::BulletText("LAST BROADCAST [%s]", lastBroadcast.c_str());
		dumpInventory();
		ImGui::TreePop();
	}
}

const char *Player::intToDirection(int direction) const
{
	switch (direction) {
	case 0:
		return "NORTH";
	case 1:
		return "EAST";
	case 2:
		return "SOUTH";
	case 3:
		return "WEST";
	default:
		return "UNKNOWN";
	}
}

void Player::dumpInventory() const
{
	if (ImGui::TreeNode("Inventory")) {
		ImGui::BulletText("%i FOOD", inventory[0]);
		ImGui::BulletText("%i LINEMATE", inventory[1]);
		ImGui::BulletText("%i DERAUMERE", inventory[2]);
		ImGui::BulletText("%i SIBUR", inventory[3]);
		ImGui::BulletText("%i MENDIANE", inventory[4]);
		ImGui::BulletText("%i PHIRAS", inventory[5]);
		ImGui::BulletText("%i THYSTAME", inventory[6]);
		ImGui::TreePop();
	}
}

const sf::RectangleShape &Player::getShape() const
{
	return shape;
}

void Player::setOutlineColor(const sf::Color &color)
{
	shape.setOutlineColor(color);
}

void Player::setOutlineThickness(float f)
{
	shape.setOutlineThickness(f);
}

const std::string &Player::getLastBroadcast() const
{
	return lastBroadcast;
}

void Player::setLastBroadcast(const std::string &lastBroadcast)
{
	Player::lastBroadcast = lastBroadcast;
}

void Player::levelUp()
{
	level += 1;
}

void Player::setLevel(int level)
{
	Player::level = level;
}

void Player::eat()
{
	inventory.at(0) -= 1;
}
