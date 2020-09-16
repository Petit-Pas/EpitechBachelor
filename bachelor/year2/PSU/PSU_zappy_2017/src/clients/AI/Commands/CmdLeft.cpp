//
// EPITECH PROJECT, 2018
// Zappy
// File description:
// Left
//

#include "CmdLeft.hpp"

const size_t Cmd::Left::DEFAULT_TIME = 7;

Cmd::Left::Left(const std::shared_ptr<Connection> &connection, ADrone &drone, const std::string &name)
	: SimpleCmd(connection, name, DEFAULT_TIME, "")
{
	drone.getOrientation(ADrone::Reality::SUPPOSED)--;
}

void Cmd::Left::okCase(ADrone &drone)
{
	drone.getOrientation()--;
}
