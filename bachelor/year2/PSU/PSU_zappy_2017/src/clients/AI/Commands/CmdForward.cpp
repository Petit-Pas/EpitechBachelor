//
// EPITECH PROJECT, 2018
// Zappy
// File description:
// Forward
//

#include "CmdForward.hpp"

const size_t Cmd::Forward::DEFAULT_TIME = 7;

Cmd::Forward::Forward(const std::shared_ptr<Connection> &connection, ADrone &drone,
	const std::string &name)
	: SimpleCmd(connection, name, DEFAULT_TIME, "")
{
	drone.move(ADrone::Reality::SUPPOSED);
}

void Cmd::Forward::okCase(ADrone &drone)
{
	drone.move();
}
