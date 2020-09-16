//
// EPITECH PROJECT, 2018
// Zappy
// File description:
// handle the incantation master side
//

#include <algorithm>
#include <sstream>
#include "CmdMasterIncantation.hpp"
#include "AllCommands.hpp"
#include "Levels.hpp"

Cmd::MasterIncantation::MasterIncantation(const std::shared_ptr<Connection> &con,
	ADrone &drone, const std::vector<std::pair<std::size_t , std::unordered_map<std::string, size_t>>> &team) : AComplexCommand(con), _team(team)
{
	prepareNextIncantation(drone);
}

void Cmd::MasterIncantation::updateCommands(ADrone &drone)
{
	if (_actions.empty() && !_toDelete) {
		if (isReadyToIncant(drone)) {
			if (_teamFinished.size() == 0)
				prepareNextIncantation(drone);
		} else {
			for (const auto &teammate : _team) {
				_actions.push_back(std::make_shared<Cmd::Broadcast>(_com,
				"INCANT_OVER " + std::to_string(teammate.first)));
			}
			_toDelete = true;
		}
	}
}

/**
 * Alors il va falloir ici que tu rajoute des méca de broadcast
 * @param serverMsg
 * @param drone
 * @return
 */
bool Cmd::MasterIncantation::unusedMessage(const std::string &serverMsg, ADrone &drone)
{
	bool status = false;

	if (::Broadcast::Broadcast::isMessage(serverMsg)) {
		::Broadcast::Message message(serverMsg);
		const auto &params = message.getParams();

		if (params.size() == 1 && message.getFunction() == "DROP_END"
		    && std::find(_teamFinished.begin(), _teamFinished.end(), std::stoul(params[0])) == _teamFinished.end()) {
			bool isOk = false;
			for (const auto &elem : _team) {
				if (elem.first == std::stoul(params[0]))
					isOk = true;
			}
			if (isOk) {
				_teamFinished.push_back(std::stoul(params[0]));
				status = true;
			}
		}
		if (status && _teamFinished.size() == _team.size()) {
			std::cout << "Everybody ended dropping resources. Ready to incant !!!!" << std::endl;
			auto req = LEVELS_REQUIREMENT.at(drone.getLevel() + 1);
			_actions.push_back(std::make_shared<Cmd::CleanTile>(_com, drone, req));
			_teamFinished.clear();
		}
	}
	return status;
}

/**
 * Protocol : OBEY $ID $Resource $NbResource ...
 * @param drone
 */
void Cmd::MasterIncantation::prepareNextIncantation(ADrone &drone)
{
	auto requirements = LEVELS_REQUIREMENT.at(drone.getLevel() + 1);

	for (const auto &teammate : _team) {
		std::stringstream ss;
		ss << "OBEY " << teammate.first;
		for (auto &requirement : requirements) {
			if (requirement.first != "player" && requirement.second > 0
				&& teammate.second.find(requirement.first) != teammate.second.end()
				&& teammate.second.at(requirement.first)) {
				std::string item = requirement.first;
				std::size_t nb;
				if (requirement.second > teammate.second.at(requirement.first)) {
					nb = teammate.second.at(requirement.first);
					requirement.second -= teammate.second.at(requirement.first);
				} else {
					nb = requirement.second;
					requirement.second = 0;
				}
				if (teammate.first == drone.getId()) {
					for (size_t j = 0; j < nb; ++j)
						_actions.push_back(std::make_shared<Cmd::Set>(_com, item, drone));
				} else {
					ss << " " << requirement.first << " "
					   << requirement.second;
				}
			}
		}
		if (teammate.first != drone.getId()) {
			_actions.push_back(std::make_shared<Cmd::Broadcast>(_com, ss.str()));
		} else {
			_teamFinished.push_back(drone.getId());
		}
	}
}

bool Cmd::MasterIncantation::isReadyToIncant(ADrone &drone)
{
	auto requirements = LEVELS_REQUIREMENT.at(drone.getLevel() + 1);

	return (requirements["player"] == _team.size());
}
