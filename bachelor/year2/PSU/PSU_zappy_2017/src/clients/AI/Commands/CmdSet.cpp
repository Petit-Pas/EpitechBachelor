//
// EPITECH PROJECT, 2018
// Zappy
// File description:
// Set
//

#include "CmdSet.hpp"

const size_t Cmd::Set::DEFAULT_TIME = 7;

Cmd::Set::Set(const std::shared_ptr<Connection> &connection, const std::string &args, ADrone &drone, const std::string &name) : SimpleCmd(connection, name, DEFAULT_TIME, args), _item(args)
{
	drone.removeFromInventory(_item, ADrone::Reality::SUPPOSED);
	drone.addToTile(_item, ADrone::Reality::SUPPOSED);
}

void Cmd::Set::okCase(ADrone &drone)
{
	drone.removeFromInventory(_item);
	drone.addToTile(_item);
}
