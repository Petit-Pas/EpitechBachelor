//
// EPITECH PROJECT, 2018
// Zappy
// File description:
// Right
//

#include "CmdRight.hpp"

const size_t Cmd::Right::DEFAULT_TIME = 7;

Cmd::Right::Right(const std::shared_ptr<Connection> &connection, ADrone &drone, const std::string &name)
	: SimpleCmd(connection, name, DEFAULT_TIME, "")
{
	drone.getOrientation(ADrone::Reality::SUPPOSED)++;
}

void Cmd::Right::okCase(ADrone &drone)
{
	drone.getOrientation()++;
}
