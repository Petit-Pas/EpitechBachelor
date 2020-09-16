/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** Internal functions
*/

#ifndef ZAPPY_PLAYERTRACKER_HPP
# define ZAPPY_PLAYERTRACKER_HPP

#include "imgui.hpp"
#include <memory>
#include "Player.hpp"

class PlayerTracker {
public:
	explicit PlayerTracker(std::map<int, std::shared_ptr<Player>> &_players);
	void draw(const char *title, sf::Vector2i size, sf::Vector2i pos);
private:
	std::map<int, std::shared_ptr<Player>> &_players;
	ImGuiTextFilter _filter;
};

#endif //ZAPPY_PLAYERTRACKER_HPP
