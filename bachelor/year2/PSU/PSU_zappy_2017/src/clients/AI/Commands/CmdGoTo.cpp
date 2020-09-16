//
// EPITECH PROJECT, 2018
// Zappy
// File description:
// go to a defined tile
//

#include "CmdGoTo.hpp"
#include "AllCommands.hpp"

Cmd::GoTo::GoTo(const std::shared_ptr<Connection> &connection, const Position &pos, ADrone &drone)
	: AComplexCommand(connection), _target(pos)
{
	while (drone.getTotalCommands() + _actions.size() < 5 && drone.getPosition(ADrone::Reality::SUPPOSED) != _target) {
		setNextAction(drone);
	}
}

void Cmd::GoTo::setNextAction(ADrone &drone)
{
	auto actualPos = drone.getPosition(ADrone::Reality::SUPPOSED);
	auto dir = drone.getDirection(ADrone::Reality::SUPPOSED);
	auto oppositeDir = dir;

	oppositeDir += 2;
	if (dir.getNbMovements(actualPos, _target, drone.getMap()) <=
	    oppositeDir.getNbMovements(actualPos, _target, drone.getMap()) &&
	    dir.getNbMovements(actualPos, _target, drone.getMap()) != 0) {
		_actions.push_back(std::make_shared<Cmd::Forward>(_com, drone));
		_actions.push_back(std::make_shared<Cmd::Look>(_com));
	} else {
		dir--;
		oppositeDir--;
		if (dir.getNbMovements(actualPos, _target, drone.getMap()) == 0) {
			_actions.push_back(std::make_shared<Cmd::Left>(_com, drone));
			_actions.push_back(std::make_shared<Cmd::Look>(_com));
			_actions.push_back(std::make_shared<Cmd::Left>(_com, drone));
			_actions.push_back(std::make_shared<Cmd::Look>(_com));
		} else if (dir.getNbMovements(actualPos, _target, drone.getMap()) <
			   oppositeDir.getNbMovements(actualPos, _target, drone.getMap())) {
			_actions.push_back(std::make_shared<Cmd::Left>(_com, drone));
			_actions.push_back(std::make_shared<Cmd::Look>(_com));
		} else {
			_actions.push_back(std::make_shared<Cmd::Right>(_com, drone));
			_actions.push_back(std::make_shared<Cmd::Look>(_com));
		}
	}
}

void Cmd::GoTo::updateCommands(ADrone &drone)
{
	while (drone.getTotalCommands() + _actions.size() < 5 && drone.getPosition(ADrone::Reality::SUPPOSED) != _target) {
		setNextAction(drone);
	}
	if (drone.getPosition() == _target)
		_toDelete = true;
}

bool Cmd::GoTo::unusedMessage(const std::string &, ADrone &)
{
	return (false);
}
