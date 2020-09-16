//
// EPITECH PROJECT, 2018
// Zappy
// File description:
// leveling
//

#include <string>
#include "CmdLevelUp.hpp"
#include "AllCommands.hpp"
#include "Levels.hpp"

Cmd::LevelUp::LevelUp(const std::shared_ptr<Connection> &con, ADrone &drone, const std::vector<std::pair<std::string, Tile>> &incantationTeam)
	: AComplexCommand(con)
{
	if (incantationTeam.size() == 1) {
		_actions.push_back(std::make_shared<Cmd::CleanTile>(_com, drone, LEVELS_REQUIREMENT.at(2)));
		_toDelete = true;
	} else {
		std::vector<std::pair<std::size_t, std::unordered_map<std::string, size_t>>> teamIncantation;
		for (const auto &mate : incantationTeam) {
			teamIncantation.emplace_back(std::pair<std::size_t, std::unordered_map<std::string, size_t>>(std::stoul(mate.first), mate.second.getElements()));
		}
		_actions.push_back(std::make_shared<Cmd::JoinPeople>(_com, drone, teamIncantation));
		_toDelete = true;
	}
}

/*bool Cmd::LevelUp::isDone() const
{
	return (true);
	}*/

void Cmd::LevelUp::updateCommands(ADrone &)
{
}

bool Cmd::LevelUp::unusedMessage(const std::string &, ADrone &)
{
	return (false);
}
