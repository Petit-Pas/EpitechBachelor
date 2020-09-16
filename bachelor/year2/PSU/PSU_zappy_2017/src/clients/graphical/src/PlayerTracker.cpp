/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** Internal functions
*/

#include "PlayerTracker.hpp"

void PlayerTracker::draw(const char *title, sf::Vector2i size, sf::Vector2i pos)
{
	ImGui::SetNextWindowSize(size);
	ImGui::SetNextWindowPos(pos);
	ImGui::Begin(title, nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);
	ImGui::SameLine();
	ImGui::SameLine();
	_filter.Draw("Filter", -100.0f);
	ImGui::Separator();
	ImGui::BeginChild("scrolling", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);
	if (ImGui::TreeNode("Players")) {
		if (_filter.IsActive()) {
			for (auto &player : _players) {
				char buff[256];
				sprintf(buff, "Player %i", player.second->getId());
				if (_filter.PassFilter(buff)) {
					player.second->setOutlineColor(sf::Color::Green);
					player.second->setOutlineThickness(2);
					player.second->dump();
				} else {
					player.second->setOutlineColor(sf::Color::Transparent);
					player.second->setOutlineThickness(2);
				}
			}
		} else {
			for (auto &player : _players) {
				player.second->setOutlineColor(sf::Color::Transparent);
				player.second->setOutlineThickness(2);
				player.second->dump();
			}
		}
		ImGui::TreePop();
	}
	ImGui::EndChild();
	ImGui::End();
}

PlayerTracker::PlayerTracker(std::map<int, std::shared_ptr<Player>> &_players) : _players(_players)
{
}

