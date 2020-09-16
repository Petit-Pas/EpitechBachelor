//
// EPITECH PROJECT, 2018
// zappy
// File description:
// zappy IA definition
//

#include <thread>
#include <sstream>
#include <regex>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>

#include "ADrone.hpp"
#include "Levels.hpp"
#include "AllCommands.hpp"
#include "Commands/CmdTake.hpp"
#include "MapOperators.hpp"

ADrone::ADrone(const std::string &ip, int port, const std::string &name)
	: _com(std::make_shared<Connection>(ip, port)), _teamName(name),
	  _remainingSlots(0), _position({0, 0}), _supposedPosition(_position),
	  _orientation(Direction::UP), _supposedOrientation(_orientation),
	  _objectif(-1),
	  _sharedPosition(false),
	  _level(1), _id(0), _globalId(0), _ticks(0), _connected(false), _dead(false),
	  _state(State::IDLE)
{
	initNeed();
	_actions.push_back(std::make_shared<CmdConnection>(_com, name));
	_actions.push_back(std::make_shared<Cmd::FindOrigins>(_com));
}

ADrone::ADrone(const std::shared_ptr<ADrone> &drone)
	: _com(drone->getConnection()), _map(drone->getMap()), _supposedMap(drone->getMap(Reality::SUPPOSED)),
	  _teamName(drone->getTeamName()), _remainingSlots(drone->getRemainingSlots()),
	  _position(drone->getPosition()), _supposedPosition(drone->getPosition(Reality::SUPPOSED)),
	  _actions(drone->getActions()),
	  _orientation(drone->getDirection()),
	  _supposedOrientation(drone->getDirection(Reality::SUPPOSED)),
	  _objectif(-1),
	  _sharedPosition(drone->getSharedPosition()),
	  _inventory(drone->getInventory()), _supposedInventory(drone->getInventory(Reality::SUPPOSED)),
	  _commonInventory(drone->getCommonInventory()),
	  _level(drone->getLevel()), _id(drone->getId()), _globalId(drone->getGlobalId()),
	  _ticks(drone->getTicks()), _connected(drone->isConnected()), _dead(drone->isDead()),
	  _state(State::IDLE)
{
	initNeed();
}

void ADrone::simulate()
{
	while (_com->isConnected() && _com->receiveMsg() && !_dead) {
		if (_com->hasMessages()) {
			handleServerMessage(_com->getNextMessage());
		}
		executeCommand();
		for (size_t i = 0; i < _actions.size(); i++) {
			if (_actions[i]->isToDelete()) {
				_ticks += _actions[i]->getTicksPassed();
				_actions.erase(_actions.begin() + i);
				break;
			}
		}
		if (getTotalCommands() < 5 && isConnected()) {
			findNextAction();
		}
	}
}

void ADrone::connect()
{
	_connected = true;
}

void ADrone::executeCommand()
{
	auto nb_actions = getTotalCommands();

	for (auto &action : _actions) {
		if (nb_actions < 5 && !action->isDone()) {
			if (action->sendCommand(*this)) {
				addCommand(action);
			}
			break;
		}
	}
}

/**
* broadcast correspond à la direction d'où vient le son, -1 si à ignorer
*/
Position ADrone::findBestSpot(const std::map<std::string, std::size_t> &goal, int broadcast) const
{
	std::vector<std::vector<std::size_t>> map(getMap().getSize().height);
	int soundOrigin = broadcast;

	for (std::size_t i = 0 ; i < getMap().getSize().height ; ++i) {
		map[i].resize(getMap().getSize().width);
	}
	for (std::size_t y = 0 ; y < getMap().getSize().height ; ++y) {
		for (std::size_t x = 0 ; x < getMap().getSize().width ; ++x) {
			if (getMap().accessTile(y, x).getNbContent("reliability") == 0 && desiredDirection(soundOrigin, y, x)) {
				map[y][x] = TILE_DEFAULT_VALUE;
			} else if (desiredDirection(soundOrigin, y, x)) {
				map[y][x] = usefulResourcesCount(getMap().accessTile(y, x), goal);
			}
			map[y][x] *= distanceRatio(abs(getDist(y, getPosition().y, _map.getSize().height)) +
				abs(getDist(x, getPosition().x, _map.getSize().width)), MAX_DISTANCE_PRECISION_LOSS, TILE_DISTANCE_PRECISION_LOSS);
		}
	}
	auto aliasedMap = map;
	for (std::size_t y = 0 ; y < getMap().getSize().height ; ++y) {
		for (std::size_t x = 0 ; x < getMap().getSize().width ; ++x) {
			aliasedMap[y][x] += map[(y - 1 + _map.getSize().height) % _map.getSize().height][x] / 5;
			aliasedMap[y][x] += map[(y + 1) % _map.getSize().height][x] / 5;
			aliasedMap[y][x] += map[y][(x - 1 + _map.getSize().width) % _map.getSize().width] / 5;
			aliasedMap[y][x] += map[y][(x + 1) % _map.getSize().width] / 5;
		}
	}
	Position bestSpot = { 0, 0 };
	std::size_t bestValue = 0;
	for (std::size_t y = 0 ; y < getMap().getSize().height ; ++y) {
		for (std::size_t x = 0 ; x < getMap().getSize().width ; ++x) {
			if (aliasedMap[y][x] > bestValue) {
				bestValue = aliasedMap[y][x];
				bestSpot = { static_cast<int>(y), static_cast<int>(x) };
			}
		}
	}
	return (bestSpot);
}

std::map<std::string, Tile> ADrone::tryWithHim(std::map<std::string, Tile> buddies, std::pair<std::string, Tile> newBuddy) const
{
	buddies.emplace(newBuddy);
	return (buddies);
}

std::map<std::string, Tile> ADrone::addBuddies(std::map<std::string, Tile> buddies, std::map<std::string, std::size_t> &requirements) const
{
	std::map<std::string, std::size_t> mockInventory = {
		{"linemate", 0}, {"deraumere", 0}, {"sibur", 0}, {"mendiane", 0}, {"phiras", 0}, {"thystame", 0}
	};
	std::map<std::string, Tile> incantationPals = buddies;

	for (auto &it : _commonInventory) {
		if (buddies.size() < requirements.find("player")->second && buddies.find(it.first) == buddies.end() &&
		    std::stoi(it.first) > static_cast<int>(_id) && it.second.getNbContent("level") == _level && it.second.getNbContent("state") == 0 && it.second.getNbContent("food") > 7 + requirements.find("player")->second * 5) {
			incantationPals = addBuddies(tryWithHim(buddies, it), requirements);
		}
		if (incantationPals.size() == requirements.find("player")->second) {
			for (auto &bud : incantationPals) {
				for (auto &resource : mockInventory) {
					resource.second += bud.second.getNbContent(resource.first);
				}
			}
			if (mockInventory >= requirements) {
				return (incantationPals);
			}
		}
	}
	return (incantationPals);
}

/**
 * Alors la je sais franchement pas si la méthode de Lucas marchera toujours après mes changements
 * On a besoin de récupérer l'inventaire des coéquipiers pour savoir qui doit drop quoi
 * J'ai trouvé que c'était le meilleur endroit opportun peut être pas le plus judicieux
 * @param requirements
 * @return std::vector<std::pair<std::string ID, Tile Inventaire>>
 */
std::vector<std::pair<std::string, Tile>> ADrone::findIncantationBuddies(std::map<std::string, std::size_t> requirements)
{
	std::map<std::string, std::size_t> mockInventory = {
		{"linemate", 0}, {"deraumere", 0}, {"sibur", 0}, {"mendiane", 0}, {"phiras", 0}, {"thystame", 0}
	};
	std::map<std::string, Tile> buddiesToCompare;
	std::vector<std::pair<std::string, Tile>> ids;


	if (requirements.find("player")->second > _commonInventory.size() + 1)
		return (ids);
	buddiesToCompare.insert({std::to_string(_id), _inventory});
	buddiesToCompare = addBuddies(buddiesToCompare, requirements);
	if (buddiesToCompare.size() == requirements.find("player")->second) {
		for (auto &bud : buddiesToCompare) {
			for (auto &resource : mockInventory) {
				resource.second += bud.second.getNbContent(resource.first);
			}
			ids.insert(ids.end(), bud);
		}
		mockInventory["player"] = ids.size();
		for (const auto &req : requirements) {
			if (mockInventory.at(req.first) < req.second) {
				ids.clear();
				return (ids);
			}
		}
		return (ids);
	}
	ids.clear();
	return (ids);
}

bool ADrone::desiredDirection(int broadcast, std::size_t y, std::size_t x) const
{
	if (broadcast == -1)
		return (true);

	int yDist = getDist(y, getPosition().y, _map.getSize().height);
	int xDist = getDist(x, getPosition().x, _map.getSize().width);

	if (broadcast == 1 && yDist < 0 && abs(xDist) <= abs(yDist) / 3)
		return (true);
	if (broadcast == 2 && abs(xDist) > abs(yDist) / 3 && abs(yDist) > abs(xDist) / 3 &&
		yDist < 0 && xDist < 0)
		return (true);
	if (broadcast == 3 && xDist < 0 && abs(yDist) <= abs(xDist) / 3)
		return (true);
	if (broadcast == 4 && abs(xDist) > abs(yDist) / 3 && abs(yDist) > abs(xDist) / 3 &&
		yDist > 0 && xDist < 0)
		return (true);
	if (broadcast == 5 && yDist > 0 && abs(xDist) <= abs(yDist) / 3)
		return (true);
	if (broadcast == 6 && abs(xDist) > abs(yDist) / 3 && abs(yDist) > abs(xDist) / 3 &&
		yDist > 0 && xDist > 0)
		return (true);
	if (broadcast == 7 && xDist > 0 && abs(yDist) <= abs(xDist) / 3)
		return (true);
	if (broadcast == 8 && abs(xDist) > abs(yDist) / 3 && abs(yDist) > abs(xDist) / 3 &&
		yDist < 0 && xDist > 0)
		return (true);
	if (broadcast == 0 && yDist == 0 && xDist == 0)
		return (true);
	return (false);
}

int ADrone::getDist(std::size_t tilePos, int playerPos, std::size_t axis) const
{
	while (playerPos < 0)
		playerPos += axis;
	while (playerPos > static_cast<int>(axis))
		playerPos -= axis;

	int dist = abs(static_cast<int>(tilePos - playerPos));
	if (dist > static_cast<int>(axis / 2))
		dist = static_cast<int>(axis - dist);
	if ((static_cast<int>(tilePos) < playerPos && playerPos - tilePos < axis / 2) ||
		(static_cast<int>(tilePos) > playerPos && tilePos - playerPos > axis / 2))
		dist *= -1;
	return (dist);
}

double ADrone::distanceRatio(int distance, int maxLoss, int loss) const
{
	double totalLoss = loss * abs(distance);

	if (totalLoss > maxLoss)
		totalLoss = maxLoss;
	totalLoss = 100 - totalLoss;
	return (totalLoss / 100);
}

int ADrone::relativeToAbsoluteReception(int receipt) const
{
	if (receipt <= 0)
		return (receipt);
	receipt -= (_orientation.getIndex() - 1) * 2;
	if (receipt <= 0)
		receipt += 8;
	if (receipt > 8)
		receipt -= 8;
	//std::cout << "sound originates from " << receipt << std::endl;
	return (receipt);
}

std::size_t ADrone::usefulResourcesCount(const Tile &tile, const std::map<std::string, std::size_t> &goal) const
{
	static const std::vector<std::string> resources = {"food", "linemate", "deraumere", "sibur", "mendiane", "phiras", "thystame"};
	std::size_t amount = 0;
	std::size_t sumSearched = 0;

	for (const auto &resource : resources) {
		if (goal.find(resource) == goal.end())
			continue;
		sumSearched += goal.find(resource)->second;
		if (tile.getNbContent(resource) >
			goal.find(resource)->second) {
			amount += goal.find(resource)->second;
		} else {
			amount += tile.getNbContent(resource);
		}
	}
	// get the amount of item on the tile correspondig to the item set as goal
	// multiply it with the reliability of the tile
	if (sumSearched == 0)
		return (0);
	return ((std::size_t)(/*tile.getNbContent("reliability")*/100 * amount / sumSearched));
}

void ADrone::addToInventory(const std::string &item, const Reality real)
{
	if (real == Reality::REAL) {
		//std::cout << "Add to inventory" << std::endl;
		_inventory.addTileContent(item, 1);
	}
	else
		_supposedInventory.addTileContent(item, 1);
}

void ADrone::removeFromInventory(const std::string &item, const Reality real)
{
	if (real == Reality::REAL)
		_inventory.withdrawItem(item);
	else
		_supposedInventory.withdrawItem(item);
}

void ADrone::editInventory(const std::string &item, size_t quantity, const Reality real)
{
	if (real == Reality::REAL)
		_inventory.withdrawItem(item, quantity);
	else
		_supposedInventory.withdrawItem(item, quantity);
}

void ADrone::removeFromTile(const std::string &item, size_t quantity, const Reality real)
{
	if (real == Reality::REAL) {
		getMap().accessTile(getPosition()).withdrawItem(item, quantity);
	} else {
		getMap(Reality::SUPPOSED).accessTile(getPosition(Reality::SUPPOSED)).withdrawItem(item, quantity);
	}
}

void ADrone::removeFromTile(const std::string &item, const Reality real)
{
	if (real == Reality::REAL) {
		getMap().accessTile(getPosition()).withdrawItem(item);
	} else {
		getMap(Reality::SUPPOSED).accessTile(getPosition(Reality::SUPPOSED)).withdrawItem(item);
	}
}

void ADrone::addToTile(const std::string &item, const Reality real)
{
	if (real == Reality::REAL) {
		getMap().accessTile(getPosition()).addTileContent(item, 1);
	} else {
		getMap(Reality::SUPPOSED).accessTile(getPosition(Reality::SUPPOSED)).addTileContent(item, 1);
	}
}

void ADrone::addCommand(std::shared_ptr<ACommand> command)
{
	_list.push(command);
}

void ADrone::move(Reality real)
{
	if (real == Reality::REAL) {
		_position += _orientation;
		_position.scaleToMap(_map);
	} else {
		_supposedPosition += _supposedOrientation;
		_supposedPosition.scaleToMap(_supposedMap);
	}
}

void ADrone::addLevel()
{
	_level++;
}

Orientation &ADrone::getOrientation(Reality real)
{
	if (real == Reality::REAL)
		return (_orientation);
	else
		return (_supposedOrientation);
}

void ADrone::setMapTile(const Position &pos, const Tile &tile, Reality real)
{
	if (real == Reality::REAL) {
		_map.accessTile(pos).setTileContent(tile);
	} else {
		_supposedMap.accessTile(pos).setTileContent(tile);
	}
}

void ADrone::handleServerMessage(const std::string &serverMsg)
{
	bool used = true;
	size_t i = 0;

	if (serverMsg == "dead") {
		_dead = true;
	} else if (serverMsg.size() >= 6 && serverMsg.substr(0, 5) == "eject") {
		//std::cout << "Ejected" << std::endl;
	} else if (serverMsg == "Elevation underway") {
		_actions.push_back(std::make_shared<Cmd::Incantate>(_com, true));
	} else {
		used = false;
	}
	if (!used && !_list.empty()) {
		used = _list.front()->handleServerResponse(serverMsg, *this);
		if (_list.front()->isToDelete())
			_list.pop();
	}
	while (!used && i < _actions.size()) {
		used = _actions[i]->handleServerResponse(serverMsg, *this);
		i++;
	}
	if (!used) {
		if (::Broadcast::Broadcast::isMessage(serverMsg)) {
			used = handleCommonsMessage(serverMsg);
		}
		if (!used)
			defaultMessageHandling(serverMsg);
	}
	for (auto &action : _actions) {
		action->update(*this);
	}
	if (!_list.empty() && _list.front()->isToDelete())
		_list.pop();
}

bool ADrone::handleCommonsMessage(const std::string &servMessage)
{
	Broadcast::Message message(servMessage);
	const auto &params = message.getParams();

	if (message.getFunction() == "NOT_FIRST" && params.size() == 2) {
		std::istringstream iss(params[1]);
		std::size_t id;
		iss >> id;

		if (_globalId < id)
			_globalId = id;
	} else if (message.getFunction() == "INVENTORY" && params.size() > 2) {
		_commonInventory[params[0]] = getInventoryFromParams(
			message.getParamsLine().substr(message.getParamsLine().find('['))
			);
	} else if (message.getFunction() == "NEW" && _id != 0 && !params.empty()) {
		_actions.push_back(std::make_shared<Cmd::Broadcast>(_com, "NOT_FIRST " + params[0] + " " + std::to_string(_globalId + 1)));
		_globalId++;
	} else if (message.getFunction() == "INCANTATE" && params.size() > 3) {
		if (std::to_string(_id) == params[1]) {
			if (_state == State::IDLE) {
				_actions.push_back(std::make_shared<Cmd::JoinPeople>(_com, *this, std::stoul(params[0]), message.getOrientation()));
			} else {
				_actions.push_back(std::make_shared<Cmd::Broadcast>(_com, "INCANT_END " + params[0] + " " + std::to_string(_id)));
			}
		} else {
			_commonInventory[params[1]].setTileContent("state", 1);
		}
	} else {
		return (false);
	}
	return (true);
}

Tile ADrone::getInventoryFromParams(const std::string &obj)
{
	std::string formatted_obj = obj;
	formatted_obj = std::regex_replace(obj, std::regex("\\[|\\]"), "");
	std::vector<std::string> elems;
	boost::split(elems, formatted_obj, boost::is_any_of(" ,"));
	Tile tile;

	for (std::size_t i = 0; i + 1 < elems.size() ; i++) {
		if (elems[i].size() > 3) {
			std::stringstream ss(elems[i + 1]);
			size_t nb = 0;
			ss >> nb;
			tile.addTileContent(elems[i], nb);
			i++;
		}
	}
	return (tile);
}

void ADrone::defaultMessageHandling(const std::string &)
{
}

void ADrone::setRemainingSlots(size_t slots)
{
	_remainingSlots = slots;
}

void ADrone::setSize(size_t height, size_t width)
{
	_map.setSize({height, width});
	_supposedMap.setSize({height, width});
}

void ADrone::setMaxId(std::size_t id)
{
	if (_globalId < id)
		_globalId = id;
}

void ADrone::setId(std::size_t id)
{
	std::cout << "my id is " << id << std::endl;
	_id = id;
	if (id == 1) {
		_sharedPosition = true;
	}
	if (id > _globalId) {
		_globalId = id;
	}
}

void ADrone::setInventory(Tile tile, Reality real)
{
	if (real == Reality::REAL)
		_inventory = tile;
	else if (real == Reality::SUPPOSED)
		_supposedInventory = tile;
}

std::size_t ADrone::getTotalTicks() const
{
	std::size_t ticks = _ticks;

	for (const auto &action : _actions) {
		ticks += action->getTicksPassed();
	}
	return (ticks);
}

std::size_t ADrone::getTotalCommands() const
{
	return (_list.size());
}

void ADrone::initNeed()
{
	_need.clear();
	for (const auto &elem : Level::getNeed()) {
		if (elem.first != "player" && elem.second > _inventory.getNbContent(elem.first) > 0) {
			_need[elem.first] = elem.second - _inventory.getNbContent(elem.first);
		}
	}
	if (_inventory.getNbContent("food") < 25) {
		_need["food"] = 25 - _inventory.getNbContent("food");
		if (_need["food"] > 5)
			_need["food"] = 5;
	} else {
		_need["food"] = 2;
	}
}

void ADrone::setObjectif(int i)
{
	_objectif = i;
}

void ADrone::setState(State state)
{
	_state = state;
}

/* getters */

const std::shared_ptr<Connection> ADrone::getConnection() const
{
	return (_com);
}

const ElementMap &ADrone::getMap(Reality real) const
{
	if (real == Reality::REAL)
		return (_map);
	else
		return (_supposedMap);
}

ElementMap &ADrone::getMap(Reality real)
{
	if (real == Reality::REAL)
		return (_map);
	else
		return (_supposedMap);
}

const std::string &ADrone::getTeamName() const
{
	return (_teamName);
}

std::size_t ADrone::getRemainingSlots() const
{
	return (_remainingSlots);
}

const std::vector<std::shared_ptr<ACommand>> &ADrone::getActions() const
{
	return (_actions);
}

const Orientation &ADrone::getDirection(Reality real) const
{
	if (real == Reality::REAL)
		return (_orientation);
	else
		return (_supposedOrientation);
}

const Position &ADrone::getPosition(Reality real) const
{
	if (real == Reality::REAL)
		return (_position);
	else
		return (_supposedPosition);
}

bool ADrone::getSharedPosition() const
{
	return (_sharedPosition);
}

const Tile &ADrone::getInventory(Reality real) const
{
	if (real == Reality::REAL)
		return (_inventory);
	else
		return (_supposedInventory);
}

const std::unordered_map<std::string, Tile> &ADrone::getCommonInventory() const
{
	return (_commonInventory);
}

std::size_t ADrone::getLevel() const
{
	return (_level);
}

std::size_t ADrone::getId() const
{
	return (_id);
}

std::size_t ADrone::getGlobalId() const
{
	return (_globalId);
}

std::size_t ADrone::getTicks() const
{
	return (_ticks);
}

bool ADrone::isConnected() const
{
	return (_connected);
}

bool ADrone::isDead() const
{
	return (_dead);
}

ADrone::State ADrone::getState() const
{
	return (_state);
}
