//
// EPITECH PROJECT, 2018
// Zappy
// File description:
// join people
//

#include <algorithm>
#include <sstream>
#include "CmdJoinPeople.hpp"
#include "CmdObeyIncatator.hpp"
#include "AllCommands.hpp"
#include "Levels.hpp"
#include "CmdMasterIncantation.hpp"

const int Cmd::JoinPeople::MAX_DELTA = 2;

Cmd::JoinPeople::JoinPeople(const std::shared_ptr<Connection> &con, ADrone &drone, size_t id, int dir)
	: AComplexCommand(con), _initialDir(drone.relativeToAbsoluteReception(dir)), _actualDir(dir), _actualLvl(drone.getLevel()), _idJoin(id),
	  _idBroadcast(1), _lastBroadcast(1), _lastBroadcastTick(0), _mode(Mode::FAR), _peopleJoined(0), _drone(drone)
{
	std::cout << "I Join the band of " << id << " as " << drone.getId() << std::endl;
	drone.setState(ADrone::State::JOIN);
}

/**
 * @param con
 * @param drone
 * @param std::vector<std::pair<std::size_t ID, std::unordered_map<std::string Resource, size_t quantity>>> people
 */
Cmd::JoinPeople::JoinPeople(const std::shared_ptr<Connection> &con, ADrone &drone, std::vector<std::pair<std::size_t, std::unordered_map<std::string, size_t>>> &people)
	: AComplexCommand(con), _initialDir(-1), _actualDir(-1), _actualLvl(drone.getLevel()),
	  _idBroadcast(1), _lastBroadcast(0), _lastBroadcastTick(0), _mode(Mode::FAR), _peopleToJoin(people), _fullPeople(people), _drone(drone)
{
	std::cout << "I create the join" << std::endl;
	drone.setState(ADrone::State::JOIN);
	for (size_t i = 0 ; i < people.size() ; i++) {
		if (people[i].first == drone.getId()) {
			people.erase(people.begin() + i);
			break;
		}
	}
	_peopleToJoin = people;
	std::sort(_peopleToJoin.begin(), _peopleToJoin.end(), compareId);
	_idJoin = _peopleToJoin[0].first;
	for (const auto &id : _peopleToJoin) {
		std::cout << drone.getId() << " Buddies are " << id.first << std::endl;
		sendIncantation(drone, id.first, false);
	}
	std::cout << "Total = " << _peopleToJoin.size() << std::endl;
	_idBroadcast++;
}

Cmd::JoinPeople::~JoinPeople()
{
	_drone.setState(ADrone::State::IDLE);
}
/*bool Cmd::JoinPeople::isDone() const
{
	return (Level::getNbPeopleNeeded(_actualLvl) == _peopleToJoin.size());
}*/

void Cmd::JoinPeople::updateCommands(ADrone &drone)
{
	std::stringstream ss;

	if (_toDelete)
		return;
	if (drone.getTotalCommands() > 1)
		return;
	if (_mode == Mode::PHARE && !isAnyStrangerHere() /* Je voudrais qu'il se calme si il y a un étranger */) {
		if (isEverybodyHere()) {
			_actions.push_back(std::make_shared<Cmd::MasterIncantation>(_com, drone, _fullPeople));
			_toDelete = true;
		}
		else if (_actions.size() < 2) {
			ss << "INCANTATE " << drone.getId() << " " << _idBroadcast << " " << drone.getLevel() + 1;
			_done = false;
		}
	} else if (_mode == Mode::JOIN) {
		joinBroadcast(drone);
	} else if (_mode == Mode::FAR && _lastBroadcastTick + 80 < drone.getTotalTicks()) {
		ss << "INCANTATE " << drone.getId() << " " <<
			_idBroadcast << " " << drone.getLevel() + 1;
	}
	if (!ss.str().empty()) {
		_idBroadcast++;
		_actions.push_back(std::make_shared<Cmd::Broadcast>(_com, ss.str()));
		_lastBroadcastTick = drone.getTotalTicks();
	}
}

void Cmd::JoinPeople::joinBroadcast(ADrone &drone)
{
	if (_actions.empty()) {
		if (_actualDir == 0) {
			_actions.push_back(std::make_shared<Cmd::ObeyIncantator>(_com, drone));
			_toDelete = true;
		} else if (_globalDir == drone.getDirection(ADrone::Reality::SUPPOSED)) {
			_actions.push_back(std::make_shared<Cmd::Forward>(_com, drone));
			_actions.push_back(std::make_shared<Cmd::Take>(_com, "food", drone));
		} else {
			_actions.push_back(std::make_shared<Cmd::Right>(_com, drone));
		}
	}
}

bool Cmd::JoinPeople::unusedMessage(const std::string &serverMsg, ADrone &drone)
{
	if (::Broadcast::Broadcast::isMessage(serverMsg)) {
		::Broadcast::Message message(serverMsg);
		const auto &params = message.getParams();

		if (params.size() == 3 && message.getFunction() == "INCANTATE" && params[0] == std::to_string(_idJoin) && params[1] == std::to_string(_lastBroadcast + 1)) {
			_actualDir = message.getOrientation();
			drone.setObjectif(drone.relativeToAbsoluteReception(_actualDir));
			if (_initialDir == -1) {
				_initialDir = drone.relativeToAbsoluteReception(_actualDir);
			}
			auto delta = getChangeDelta(_initialDir, drone.relativeToAbsoluteReception(_actualDir));
			_lastBroadcast++;
			if ((delta >= MAX_DELTA || message.getOrientation() == 0) && _mode == Mode::FAR) {
				_mode = (_idJoin > drone.getId()) ? (Mode::PHARE) : (Mode::JOIN);
				if (_mode == Mode::JOIN) {
					std::stringstream ss;
					ss << "INCANT_NEAR " << drone.getId() << " " <<
						_idJoin << " " << _idBroadcast;
					_actions.push_back(std::make_shared<Cmd::Broadcast>(
						_com, ss.str()));
					_idBroadcast++;
				}
			}
			_globalDir = Orientation(drone.relativeToAbsoluteReception(_actualDir));
		} else if (params.size() == 3 && message.getFunction() == "INCANT_NEAR" &&
			   params[0] == std::to_string(_idJoin) &&
			   params[1] == std::to_string(drone.getId()) &&
			   params[2] == std::to_string(_lastBroadcast + 1)) {
			_mode = Mode::PHARE;
			_actualDir = message.getOrientation();
			drone.setObjectif(drone.relativeToAbsoluteReception(-1));
			_lastBroadcast++;
		} else if (params.size() == 2 && message.getFunction() == "INCANT_END" &&
			   params[0] == std::to_string(drone.getId())) {
			_toDelete = true;
			_actions.clear();
			for (const auto &people : _peopleToJoin) {
				if (std::to_string(people.first) != params[1])
					_actions.push_back(std::make_shared<Cmd::Broadcast>(_com, "INCANT_END " + std::to_string(people.first) + " " + std::to_string(drone.getId())));
			}
		} else if (_mode == Mode::PHARE && message.getFunction() == "INCANT_HERE"
			&& params.size() == 1
			&& isConcern(std::stoul(params[0]))
			&& std::find(_peopleJoined.begin(), _peopleJoined.end(), std::stoul(params[0])) == _peopleJoined.end()) {
			_peopleJoined.push_back(std::stoul(params[0]));
		} else {
			return (false);
		}
		return (true);
	}
	return (false);
}

int Cmd::JoinPeople::getChangeDelta(int initial, int actual)
{
	int delta = initial - actual;

	if (delta < 0)
		delta *= -1;
	if (delta > 4) {
		delta = 8 - delta;
	}
	return (delta);
}

void Cmd::JoinPeople::sendIncantation(ADrone &drone, size_t id, bool inc)
{
	std::stringstream ss;

	ss << "INCANTATE " << drone.getId() << " " << id << " " <<
		_idBroadcast << " " << drone.getLevel() + 1;
	_actions.push_back(std::make_shared<Cmd::Broadcast>(
				   _com, ss.str()));
	if (inc)
		_idBroadcast++;
}

bool Cmd::JoinPeople::isEverybodyHere() const
{
	return (Level::getNbPeopleNeeded(_actualLvl + 1) == _peopleJoined.size() + 1);
}

//TODO checker les étrangers sur la case
bool Cmd::JoinPeople::isAnyStrangerHere() const
{
	return (false);
}

bool Cmd::JoinPeople::compareId(const std::pair<std::size_t, std::unordered_map<std::string, size_t>> &id, const std::pair<std::size_t, std::unordered_map<std::string, size_t>> &nextId)
{
	return (id.first > nextId.first);
}

bool Cmd::JoinPeople::isConcern(size_t id) const
{
	for (const auto &mate : _peopleToJoin) {
		if (mate.first == id)
			return true;

	}
	return false;
}
