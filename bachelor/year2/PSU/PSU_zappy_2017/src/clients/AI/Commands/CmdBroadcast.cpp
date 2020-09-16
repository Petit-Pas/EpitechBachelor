//
// EPITECH PROJECT, 2018
// Zappy
// File description:
// Broadcast
//

#include "CmdBroadcast.hpp"

const size_t Cmd::Broadcast::DEFAULT_TIME = 7;

Cmd::Broadcast::Broadcast(const std::shared_ptr<Connection> &connection, const std::string &args, const std::string &name) : SimpleCmd(connection, name, DEFAULT_TIME, args)
{
}
