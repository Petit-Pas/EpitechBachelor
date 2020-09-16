//
// EPITECH PROJECT, 2018
// zappy
// File description:
// zappy commands
//

#include "ACommand.hpp"

ACommand::ACommand(const std::shared_ptr<Connection> &com)
	: _done(false), _toDelete(false), _com(com)
{
}

ACommand::~ACommand()
{
}

bool ACommand::isDone() const
{
	return (_done);
}

bool ACommand::isToDelete() const
{
	return (_toDelete);
}
