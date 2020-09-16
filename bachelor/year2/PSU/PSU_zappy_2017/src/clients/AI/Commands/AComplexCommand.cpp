//
// EPITECH PROJECT, 2018
// Zappy
// File description:
// complex commands handler
//

#include "AComplexCommand.hpp"

Cmd::AComplexCommand::AComplexCommand(const std::shared_ptr<Connection> &connect)
	: ACommand(connect), _done(true), _ticks(0)
{
}

void Cmd::AComplexCommand::update(ADrone &drone)
{
	eraseCmds();
	for (const auto &action : _actions) {
		action->update(drone);
	}
	eraseCmds();
	updateCommands(drone);
	eraseCmds();
}

bool Cmd::AComplexCommand::handleServerResponse(const std::string &serv, ADrone &drone)
{
	bool used = false;
	size_t i = 0;

	while (!used && i < _actions.size()) {
		used = _actions[i]->handleServerResponse(serv, drone);
		i++;
	}
	if (used) {
		updateCommands(drone);
		eraseCmds();
	} else {
		return (unusedMessage(serv, drone));
	}
	return (used);
}

void Cmd::AComplexCommand::eraseCmds()
{
	for (size_t i = 0; i < _actions.size(); ++i) {
		if (_actions[i]->isToDelete()) {
			_ticks += _actions[i]->getTicksPassed();
			_actions.erase(_actions.begin() + i);
			break;
		}
	}
}

bool Cmd::AComplexCommand::isDone() const
{
	bool done = _done;
	size_t i = 0;

	while (done && i < _actions.size()) {
		done = _actions[i]->isDone();
		i++;
	}
	return (done);
}

bool Cmd::AComplexCommand::isToDelete() const
{
	return (_actions.empty() && _toDelete);
}

bool Cmd::AComplexCommand::sendCommand(ADrone &drone)
{
	for (auto &action : _actions) {
		if (!action->isDone()) {
			if (action->sendCommand(drone)) {
				drone.addCommand(action);
			}
			break;
		}
	}
	return (false);
}

size_t Cmd::AComplexCommand::getTicksPassed() const
{
	size_t ticks = _ticks;

	for (const auto &action : _actions) {
		ticks += action->getTicksPassed();
	}
	return (ticks);
}
