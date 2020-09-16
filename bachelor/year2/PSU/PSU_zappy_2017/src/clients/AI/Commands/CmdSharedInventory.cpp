//
// EPITECH PROJECT, 2018
// Zappy
// File description:
// share inventory with others
//

#include <sstream>
#include "CmdSharedInventory.hpp"
#include "AllCommands.hpp"

Cmd::SharedInventory::SharedInventory(const std::shared_ptr<Connection> &connection, ADrone &drone)
	: AComplexCommand(connection)
{
	std::stringstream os;

	os << "[" << drone.getInventory() << "level " << drone.getLevel() << ", state " << (int)drone.getState() << "]";
	_actions.push_back(std::make_shared<Cmd::Broadcast>(connection, "INVENTORY " + std::to_string(drone.getId()) + " " + os.str()));
	_toDelete = true;
}

void Cmd::SharedInventory::updateCommands(ADrone &)
{
}

bool Cmd::SharedInventory::unusedMessage(const std::string &, ADrone &)
{
	return (false);
}
