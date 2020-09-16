/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Created by vincent,
*/

#include "Pathfinder.hpp"
#include "AI.hpp"

Pathfinder::Pathfinder() : _startingNode(nullptr), _goalNode(nullptr), _orientations({dir::NONE, dir::NONE, dir::NONE, dir::NONE}), _directions({dir::NONE}), _interestingGoalCell(
	nullptr), _interestingSafeCell(nullptr), _start({0.f, 0.f}), _goal({0.f, 0.f}),  _acceptableDanger(50)
{
}

void Pathfinder::clear(std::vector<std::vector<node>> &nodeMap)
{
	for (auto &nodes : nodeMap) {
		for (auto &node : nodes) {
			if (node.type != Element::HARDWALL) {
				node.deadEnd = false;
				node.visited = false;
				node.parent = nullptr;
			}
		}
	}
	_directions.clear();
	_orientations.clear();
}

void Pathfinder::calcOrientation()
{
	const auto angleDeg = static_cast<int>(atan2f(_goal.y - _start.y, _goal.x - _start.x) * 180.f / M_PI);

	if (angleDeg >= 0 && angleDeg <= 45)
		_orientations = {paths::RIGHT, paths::DOWN, paths::UP, paths::LEFT};
	else if (angleDeg > 45 && angleDeg <= 90)
		_orientations = {paths::DOWN, paths::RIGHT, paths::LEFT, paths::UP};
	else if (angleDeg > 90 && angleDeg <= 135)
		_orientations = {paths::DOWN, paths::LEFT, paths::RIGHT, paths::UP};
	else if (angleDeg > 135 && angleDeg <= 180)
		_orientations = {paths::LEFT, paths::DOWN, paths::UP, paths::RIGHT};
	else if (angleDeg < 0 && angleDeg >= -45)
		_orientations = {paths::RIGHT, paths::UP, paths::DOWN, paths::LEFT};
	else if (angleDeg < -45 && angleDeg >= -90)
		_orientations = {paths::UP, paths::RIGHT, paths::LEFT, paths::DOWN};
	else if (angleDeg < -90 && angleDeg >= -135)
		_orientations = {paths::UP, paths::LEFT, paths::RIGHT, paths::DOWN};
	else
		_orientations = {paths::LEFT, paths::UP, paths::DOWN, paths::RIGHT};
}

dir::directions Pathfinder::findPath(std::vector<std::vector<node>> &nodeMap)
{
	clear(nodeMap);
	_startingNode = &nodeMap[_start.y][_start.x];
	_goalNode = &nodeMap[_goal.y][_goal.x];
	if (_startingNode == _goalNode)
		return dir::directions::NONE;
	_interestingGoalCell = _startingNode;
	_interestingSafeCell = _startingNode;
	calcOrientation();
	loopFind();

	if (_directions.empty())
		return dir::NONE;
	return _directions[0];
}

void Pathfinder::loopFind()
{
	node *tmp = _startingNode;

	size_t i = 0;
	_startingNode->visited = false;
	while (tmp->id != _goalNode->id) {
		tmp = move(tmp);
		if (tmp->id == _startingNode->id && deadEnd(_startingNode)) {
			_directions.clear();
			_directions.push_back(dir::NONE);
			return;
		}
		i++;
	}
}

node *Pathfinder::move(node *node)
{
	for (auto &orientation : _orientations ) {
		if (node->near[orientation] && !node->near[orientation]->visited && !node->near[orientation]->deadEnd && (!node->parent || (node->parent->id != node->near[orientation]->id)) && node->near[orientation]->type != Element::SOFTWALL && node->near[orientation]->danger < _acceptableDanger) {
			node->near[orientation]->parent = node;
			node->visited = true;
			_directions.push_back(static_cast<dir::directions>(orientation + 1));
			compareInterestingGoalCell(node->near[orientation]);
			compareInterestingSafeCell(node->near[orientation]);
			return node->near[orientation];
		}
	}
	node->deadEnd = true;
	return backtracking(node);
}

bool Pathfinder::deadEnd(node *node)
{
	if (node->deadEnd)
		return true;
	for (auto &orientation : _orientations ) {
		if (node->near[orientation] && !node->near[orientation]->visited && (!node->parent || (node->parent->id != node->near[orientation]->id)) && node->near[orientation]->type != Element::SOFTWALL && node->near[orientation]->danger < _acceptableDanger)
			return false;
	}
	return true;
}

node *Pathfinder::backtracking(node *cell)
{
	while (cell && deadEnd(cell)) {
		_directions.pop_back();
		cell->deadEnd = true;
		if (cell->id == _startingNode->id) {
			return cell;
		}
		cell = cell->parent;
		cell->visited = false;
	}
	return cell;
}

twoFloat Pathfinder::interestingGoalCell(Element::Type &type)
{
	type = _interestingGoalCell->type;
	return _interestingGoalCell->pos;
}

twoFloat Pathfinder::interestingSafeCell(Element::Type &type)
{
	type = _interestingSafeCell->type;
	return _interestingSafeCell->pos;
}

void Pathfinder::compareInterestingGoalCell(node *node)
{
	if (_interestingGoalCell->goal <= node->goal) {
		if (_interestingGoalCell->goal < node->goal)
			_interestingGoalCell = node;
		else {
			if (_interestingGoalCell->danger >= node->danger) {
				if (_interestingGoalCell->danger > node->danger)
					_interestingGoalCell = node;
				else {
					const float newDistance = fabsf(_startingNode->pos.x - node->pos.x) + fabsf(_startingNode->pos.y - node->pos.y);
					const float actualDistance = fabsf(_startingNode->pos.x - _interestingGoalCell->pos.x) + fabsf(_startingNode->pos.y - _interestingGoalCell->pos.y);
					if (actualDistance > newDistance)
						_interestingGoalCell = node;
				}
			}
		}
	}
}

void Pathfinder::compareInterestingSafeCell(node *node)
{
	if (_interestingSafeCell->danger < node->danger) {
		_interestingSafeCell = node;
	}
}

void Pathfinder::setAcceptableDanger(unsigned char danger)
{
	_acceptableDanger = danger;
}