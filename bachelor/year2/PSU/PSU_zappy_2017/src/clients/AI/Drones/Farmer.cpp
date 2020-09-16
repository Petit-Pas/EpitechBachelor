//
// EPITECH PROJECT, 2018
// zappy
// File description:
// This drone goal is to gather the most food he can
//

#include "Farmer.hpp"
#include "AllCommands.hpp"
#include "Levels.hpp"

Drone::Farmer::Farmer(const std::string &ip, int port, const std::string &name)
	: ADrone(ip, port, name)
{
}

Drone::Farmer::Farmer(const std::shared_ptr<ADrone> drone) : ADrone(drone)
{
}

void Drone::Farmer::findNextAction()
{
	if (getTotalCommands() < 1 && _actions.size() < 5) {
		std::vector<std::pair<std::string, Tile>> ids = findIncantationBuddies(Level::getRequirementsForPeoples2(_level / 2 * 2));
		if (!ids.empty() && _actions.empty() && _state == State::IDLE && _inventory.getNbContent("food") > _level * 14) {
			_actions.push_back(std::make_shared<Cmd::LevelUp>(_com, *this, ids));
			return;
		}
		for (const auto &elem : _need) {
			for (size_t nb = _map.accessTile(_position).getNbContent(elem.first); nb > 0; nb--) {
				if (nb > elem.second) {
					nb = elem.second;
				}
				if (nb == 0)
					break;
				_actions.push_back(std::make_shared<Cmd::Take>(_com, elem.first, *this));
			}
		}
		if (_actions.size() < 2) {

			_actions.push_back(std::make_shared<Cmd::Inventory>(_com));
			initNeed();
			if (_id != 0) {
				_actions.push_back(std::make_shared<Cmd::SharedInventory>(_com, *this));
			}
			auto pos = findBestSpot(_need, _objectif);
			_actions.push_back(std::make_shared<Cmd::GoTo>(_com, pos, *this));
			if (pos == _position)
				_actions.push_back(std::make_shared<Cmd::Look>(_com));
		}
	}
}

/*
bool Drone::Farmer::canIncantate()
{
	auto req = Levels::getRequirementsForPeoples(LEVELS_REQUIREMENT.at(_level + 1).at("player"));
	for (const auto &elem : req) {
		if (elem.first != "player" && elem.second >
		    _inventory.getNbContent(elem.first)) {
			return (false);
		} else if (elem.first == "player") {
		}
	}
	return (true);
}
*/

/*			if (_commonInventory.size() == 5 && _state == State::IDLE && _id != 0) {
				std::vector<size_t> ids;
				for (auto it = _commonInventory.begin(); it != _commonInventory.end() && ids.size() < 5; ++it) {
					ids.push_back(std::stoul(it->first));
				}
				if (_id < ids[0] && _id < ids[1] && _id < ids[2] &&
				    _id < ids[3] && _id < ids[4]) {
					_actions.push_back(std::make_shared<Cmd::JoinPeople>(_com, *this, ids));
					return;
				}
			}*/
