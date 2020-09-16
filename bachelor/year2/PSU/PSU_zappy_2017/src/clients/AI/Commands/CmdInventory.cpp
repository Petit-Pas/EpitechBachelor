//
// EPITECH PROJECT, 2018
// Zappy
// File description:
// Inventory command
//

#include <vector>
#include "CmdInventory.hpp"
#include "SplitUtils.hpp"

Cmd::Inventory::Inventory(const std::shared_ptr<Connection> &connection, const std::string &name)
	: SimpleCmd(connection, name, 7)
{
}

bool Cmd::Inventory::handleServerResponse(const std::string &serv, ADrone &drone)
{
	if (serv.find("[") != 0 || serv.find("]") != serv.size() - 1 || serv.find_first_of("0123456789") == std::string::npos) {
		return (false);
	}
	drone.setInventory(drone.getInventoryFromParams(serv));
	drone.setInventory(drone.getInventoryFromParams(serv), ADrone::Reality::SUPPOSED);
	_toDelete = true;
	return (true);
}
