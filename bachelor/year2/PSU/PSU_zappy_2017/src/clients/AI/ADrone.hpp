//
// EPITECH PROJECT, 2018
// zappy
// File description:
// zappy IA definition of methods
//

#ifndef ADRONE_HPP_
#define ADRONE_HPP_

#include <map>
#include "ElementMap.hpp"
#include "Movement.hpp"
#include "Connection.hpp"
#include "ACommand.hpp"

class ACommand;

class ADrone
{
public:
	ADrone(const std::string &, int, const std::string &);
	ADrone(const std::shared_ptr<ADrone> &drone);
	virtual ~ADrone() = default;

	enum class Reality
	{
		REAL,
		SUPPOSED
	};

	enum class State
	{
		IDLE = 0,
		JOIN
	};

	/**
	 * simulate is the main loop of any ia, 
	 * it calls the handleMessage if one was receive, 
	 * execute the next command to be executed (in list of actions)
	 * then calls the findNextAction if there is space in the command list
	 */
	void simulate();

	virtual void findNextAction() = 0;

	void connect();
	void setRemainingSlots(size_t);

	/**
	 * set size of map
	 */
	void setSize(size_t, size_t);

	void setMapTile(const Position &, const Tile &, Reality = Reality::REAL);

	void setId(std::size_t);
	void setMaxId(std::size_t);
	void setInventory(Tile, Reality = Reality::REAL);

	std::size_t getTotalTicks() const;
	std::size_t getTotalCommands() const;
	Position findBestSpot(const std::map<std::string, std::size_t> &, int) const;
	std::map<std::string, Tile> tryWithHim(std::map<std::string, Tile>, std::pair<std::string, Tile> ) const;
	std::map<std::string, Tile> addBuddies(std::map<std::string, Tile> , std::map<std::string, std::size_t> &) const;
	std::vector<std::pair<std::string, Tile>> findIncantationBuddies(std::map<std::string, std::size_t> );
	std::size_t usefulResourcesCount(const Tile &, const std::map<std::string, std::size_t> &) const;

	Orientation &getOrientation(Reality = Reality::REAL);
	int relativeToAbsoluteReception(int) const;

	void addToInventory(const std::string &item, Reality reality = Reality::REAL);
	void removeFromInventory(const std::string &item, Reality reality = Reality::REAL);
	void editInventory(const std::string &item, size_t quantity, Reality reality = Reality::REAL);
	void removeFromTile(const std::string &item, size_t quantity, Reality reality = Reality::REAL);
	void removeFromTile(const std::string &item, Reality reality = Reality::REAL);
	void addToTile(const std::string &item, Reality reality = Reality::REAL);

	void addCommand(std::shared_ptr<ACommand>);

	void move(Reality = Reality::REAL);

	void addLevel();

	void setObjectif(int);

	void setState(State);

	static Tile getInventoryFromParams(const std::string &);

	/**
	 * getters
	 */
	const std::shared_ptr<Connection> getConnection() const;
	const ElementMap &getMap(Reality = Reality::REAL) const;
	ElementMap &getMap(Reality = Reality::REAL);
	const std::string &getTeamName() const;
	std::size_t getRemainingSlots() const;
	const std::vector<std::shared_ptr<ACommand>> &getActions() const;
	const Position &getPosition(Reality = Reality::REAL) const;
	const Orientation &getDirection(Reality = Reality::REAL) const;
	bool getSharedPosition() const;
	const Tile &getInventory(Reality = Reality::REAL) const;
	const std::unordered_map<std::string, Tile> &getCommonInventory() const;
	std::size_t getLevel() const;
	std::size_t getId() const;
	std::size_t getGlobalId() const;
	std::size_t getTicks() const;
	State getState() const;
	bool isConnected() const;
	bool isDead() const;
private:

	/**
	 * calls the handle server message on the list of actions until one return true
	 * if none return true, then the defaultMessage handling is called
	 */
	void handleServerMessage(const std::string &);

	/**
	 * messages treated by the drones (common protocols)
	 */
	bool handleCommonsMessage(const std::string &);

	/**
	 * called when a message is not attributed to any of the previous actions
	 */
	virtual void defaultMessageHandling(const std::string &);

	/**
	 * call the execution of the next command
	 */
	virtual void executeCommand();

	bool desiredDirection(int, std::size_t, std::size_t) const;
	int getDist(std::size_t, int, std::size_t) const;
	double distanceRatio(int, int, int) const;

	static const int TILE_DEFAULT_VALUE = 30;
	static const int MAX_DISTANCE_PRECISION_LOSS = 40;
	static const int TILE_DISTANCE_PRECISION_LOSS = 5;

protected:
	/**
	 * init the map of needed elements
	 */
	void initNeed();

protected:
	std::shared_ptr<Connection> _com;
	ElementMap _map;
	ElementMap _supposedMap;
	std::string _teamName;
	std::size_t _remainingSlots;
	Position _position;
	Position _supposedPosition;
	std::vector<std::shared_ptr<ACommand>> _actions;
	std::queue<std::shared_ptr<ACommand>> _list;
	Orientation _orientation;
	Orientation _supposedOrientation;
	int _objectif;
	bool _sharedPosition;
	Tile _inventory;
	Tile _supposedInventory;
	std::unordered_map<std::string, Tile> _commonInventory;
	std::size_t _level;
	std::size_t _id;
	std::size_t _globalId;
	std::size_t _ticks;
	bool _connected;
	bool _dead;
	State _state;

	std::map<std::string, size_t> _need;
};

#endif /* !ADRONE_HPP_ */
