/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Created by vincent,
*/

#ifndef CPP_INDIE_STUDIO_PATHFINDER_HPP
#define CPP_INDIE_STUDIO_PATHFINDER_HPP

#include <vector>
#include "Direction.hpp"
#include "Node.hpp"

class Pathfinder {
	public:
	Pathfinder();
	~Pathfinder() = default;

	void setStart(const std::pair<float, float> &pos)
	{
		_start.y = pos.first;
		_start.x = pos.second;
	}

	void setGoal(const twoFloat &pos)
	{
		_goal.y = pos.y;
		_goal.x = pos.x;
	}

	dir::directions findPath(std::vector<std::vector<node>> &);

	twoFloat interestingGoalCell(Element::Type &);
	twoFloat interestingSafeCell(Element::Type &);

	void clear(std::vector<std::vector<node>> &nodeMap);

	void setAcceptableDanger(unsigned char);

private:
	void calcOrientation();
	void loopFind();
	node *move(node *);
	node *backtracking(node *);
	bool deadEnd(node *);
	void compareInterestingGoalCell(node *);
	void compareInterestingSafeCell(node *);

private:
	node *_startingNode;
	node *_goalNode;

	std::vector<unsigned char> _orientations;
	std::vector<dir::directions> _directions;
	node *_interestingGoalCell;
	node *_interestingSafeCell;

	twoFloat _start;
	twoFloat _goal;
	unsigned char _acceptableDanger;
};

#endif //CPP_INDIE_STUDIO_PATHFINDER_HPP
