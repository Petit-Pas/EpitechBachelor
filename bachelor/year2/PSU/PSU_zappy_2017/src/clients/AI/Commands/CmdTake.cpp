//
// EPITECH PROJECT, 2018
// Zappy
// File description:
// Take
//

#include "CmdTake.hpp"

const size_t Cmd::Take::DEFAULT_TIME = 7;

Cmd::Take::Take(const std::shared_ptr<Connection> &connection, const std::string &args, ADrone &drone, const std::string &name) : SimpleCmd(connection, name, DEFAULT_TIME, args), _item(args)
{
	drone.addToInventory(_item, ADrone::Reality::SUPPOSED);
	drone.removeFromTile(_item, ADrone::Reality::SUPPOSED);
}

void Cmd::Take::okCase(ADrone &drone)
{
	drone.addToInventory(_item);
	drone.removeFromTile(_item);
}

void Cmd::Take::koCase(ADrone &drone)
{
	drone.removeFromTile(_item, 0);
	drone.removeFromTile(_item, 0, ADrone::Reality::SUPPOSED);
}
