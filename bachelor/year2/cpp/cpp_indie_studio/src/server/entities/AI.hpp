/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Created by vincent,
*/

#ifndef CPP_INDIE_STUDIO_AI_HPP
#define CPP_INDIE_STUDIO_AI_HPP

#include "Player.hpp"
#include "ABonus.hpp"
#include "LockedItem.hpp"
#include "GameManager.hpp"
#include "Pathfinder.hpp"

namespace paths {
	const unsigned char UP = 0;
	const unsigned char DOWN = 1;
	const unsigned char LEFT = 2;
	const unsigned char RIGHT = 3;
	const unsigned char SPOT = 4;
	const std::vector<unsigned char> crossDirections = {UP, DOWN, LEFT, RIGHT};

	const std::vector<twoFloat> target = {{-1, 0}, {1, 0}, {0, -1},
		{0, 1},	{0,0}};
};

class AI : public Player {
	public:
	AI(const std::pair<float, float> &pos, int id, std::shared_ptr<LockedItem<std::vector<std::unique_ptr<Player>>>> players,
		std::shared_ptr<LockedItem<std::vector<std::unique_ptr<AEntity>>>> blocking,
		std::shared_ptr<LockedItem<std::vector<std::unique_ptr<Fire>>>> fire,
		std::shared_ptr<LockedItem<std::vector<std::unique_ptr<Bomb>>>> bomb,
		std::shared_ptr<LockedItem<std::vector<std::unique_ptr<ABonus>>>> bonuses,
		std::shared_ptr<LockedItem<std::vector<PlayerCommunication>>> communication);
	~AI() = default;

	void configureMap();
	void update();
	void incrementSpeed() override;

	protected:

	void evaluateDanger(node &, const Bomb &bomb);
	virtual void evaluateGoal(node &);
	virtual void evaluateCellEscapes(node *node);

	virtual void compareGoalCells(node *);
	void setSafePosition();

	void setPath();

	void actDefensively();
	void actOffensively();

	short isSaferCell(node *, short minDanger, unsigned short interest);

	unsigned short interestingGoal(const node *nodeInformation);

	bool isTransitoryEntity(const Element::Type &type) const;


	void reset();
	virtual void updatePlayersOnMap();
	void updateBlocksOnMap();
	void updateFireOnMap();
	void updateBombsOnMap();
	virtual void updateBonusesOnMap();
	void revalueMap();
	void elaborateStrategy();
	float calculateDistanceBetween2f(const twoFloat &nb1, const twoFloat &nb2) const;
	static bool compareDistance(const std::pair<float, twoFloat> &, const std::pair<float, twoFloat> &);

	bool canSpreadFire(unsigned char fireAdvance, int firePower, const node *neighbour, char &breakSoftCapability);
	void spreadFireInLine(int firePower, int percentage, node *neighbour,
		unsigned char direction);

	bool isBodyBlocking(const Element::Type &);

	virtual bool isGoodTimeToDropBomb();

	void recenterMyPosition();
	void recenterMyXPosition();
	void recenterMyYPosition();

	unsigned short deadEnd(const node *node);

	bool hasWayOut(twoFloat, twoFloat, unsigned char);

protected:
	std::shared_ptr<LockedItem<std::vector<std::unique_ptr<Player>>>> _players; /*!< contains the players */
	std::shared_ptr<LockedItem<std::vector<std::unique_ptr<AEntity>>>> _blocking; /*!< contains walls and breakables */
	std::shared_ptr<LockedItem<std::vector<std::unique_ptr<Fire>>>> _fires; /*!< contains explosions(aka Fire) */
	std::shared_ptr<LockedItem<std::vector<std::unique_ptr<Bomb>>>> _bombs; /*!< contains Bombs */
	std::shared_ptr<LockedItem<std::vector<std::unique_ptr<ABonus>>>> _bonuses; /*!< contains every kind of bonus */
	std::shared_ptr<LockedItem<std::vector<PlayerCommunication>>> _communication;
	int _uniqueID;
	bool _goalAchieve;
	twoFloat _goalPos;
	twoFloat _safePos;
	dir::directions _nextDir;
	Pathfinder _findPath;
	std::vector<std::vector<node>> _nodeMap;
	twoFloat _lastPos;
	unsigned char _limitCalcul;
	Element::Type _goalType;
	unsigned char _lapsT;
	unsigned char _limitCalc;
	bool _firstUpdate;
	unsigned char _blocked;
};

#endif //CPP_INDIE_STUDIO_AI_HPP
