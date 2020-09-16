//
// EPITECH PROJECT, 2018
// Zappy
// File description:
// get a defined object
//

#include "CmdGetObject.hpp"
#include "CmdGoTo.hpp"
#include "CmdLook.hpp"
#include "CmdTake.hpp"

Cmd::GetObject::GetObject(const std::shared_ptr<Connection> &connection, const std::string &target, ADrone &drone)
	: AComplexCommand(connection), _target(target),
	  _nb(drone.getInventory().getNbContent(target) + 1)
{
}

void Cmd::GetObject::updateCommands(ADrone &drone)
{
	if (_nb >= drone.getInventory().getNbContent(target)) {//or group's inventory
		_toDelete = true;
	} else if (_actions.empty() && drone.getMap().accessTile(drone.getPosition()).getNbContent(_target) == 0) {
		Position nearest = findBestSpot();//pseudo code
		_actions.push_back(std::make_shared<Cmd::GoTo>(_com, nearest, drone));
		if (drone.getMap().accessTile(nearest).getNbContent("reliability") < 50)
			_actions.push_back(std::make_shared<Cmd::Look>(_com));
	} else if (_actions.empty()) {
		_actions.push_back(std::make_shared<Cmd::Take>(_com, _target, drone));
	}
}

bool unusedMessage(const std::string &, ADrone &)
{
	return (false);
}
