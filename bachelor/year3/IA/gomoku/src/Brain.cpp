/*
** EPITECH PROJECT, 2021
** pbrain-gomoku
** File description:
** internal functions
*/

#include <iostream>
#include "Brain.hpp"
#include "gomoku.hpp"

Brain::Brain(Parser &parser) : _board(parser.getBoardSize()), _parser(parser),
	_dico({{gom::OTHER_PLAYED, &Brain::otherPlays},
		{gom::BOARD, &Brain::setupBoard},
		{gom::YOU_PLAY, &Brain::play}})
{
}

Brain::~Brain()
{
}

void Brain::process()
{
	gom::state status = gom::UNKNOWN;
	std::cout << "OK" << std::endl;

	while (status != gom::END) {
		status = _parser.parse();
		for (auto &command : _dico) {
			if (command.first == status) {
				(this->*(command.second))();
				break;
			}
		}
	}
}

void Brain::setupBoard()
{
	_board.setup(_parser.getTurns());
	_board.computeTurns();
	//_board.displayBoard();
	play();
}

void Brain::otherPlays()
{
	auto turn = _parser.getTurn();
	if (turn.first >= 0 && turn.first < _board.getSize() && turn.second >= 0 && turn.second < _board.getSize())
		_board.setCellId(turn.first, turn.second, 2);
	else
		std::cout << "ERROR" << std::endl;
	play();
}

void Brain::play()
{
	gom::specialTurn turn = _board.getHighestCombination();

	if (turn != gom::specialTurn::NO_SPECIAL)
		chooseBySpecialTurn(turn);
	else if (!chooseWithPrevision())
		chooseByValue();
	//_board.displayBoard();
}

void Brain::chooseBySpecialTurn(gom::specialTurn turn)
{
	auto cells = _board.getCellsBySpecialTurn(turn);
	std::shared_ptr<Cell> found = cells[0];
	int value = cells[0]->getRawValue();

	for (auto &cell : cells) {
		if (cell->getRawValue() > value) {
			found = cell;
			value = cell->getRawValue();
		}
		if (cell->getRawValue() == value && rand() % 2 == 0) {
			found = cell;
		}
	}
	found->setId(1);
	std::cout << found->getX() << "," << found->getY() << std::endl;
}

void Brain::chooseByValue()
{
	auto cell = _board.getHighestValuedCell();
	cell->setId(1);
	std::cout << cell->getX() << "," << cell->getY() << std::endl;
}

bool mySort(int a, int b)
{
	return a > b;
}

bool Brain::chooseWithPrevision()
{
	auto bestSelf = getNBestCellsSelf(50);
	auto bestOpponent = getNBestCellsOpponent(50);
	int maxFound = 0;
	std::vector<std::shared_ptr<Cell>> cellsMax;
	int res = 0;

	for (auto &cell : bestSelf) {
		res = simulate(cell, 1);
		if (res > maxFound) {
			cellsMax = {};
			maxFound = res;
		}
		if (res == maxFound) {
			cellsMax.push_back(cell);
		}
	}
	for (auto &cell : bestOpponent) {
		res = simulate(cell, 2);
		if (res > maxFound) {
			cellsMax = {};
			maxFound = res;
		}
		if (res == maxFound) {
			cellsMax.push_back(cell);
		}
	}
	if (maxFound == 0)
		return false;
	auto cell = cellsMax[rand() % cellsMax.size()];
	std::cout << cell->getX() << "," << cell->getY() << std::endl;
	cell->setId(1);
	return true;
}

std::vector<std::shared_ptr<Cell>> Brain::getNBestCellsSelf(int nb)
{
	std::vector<std::shared_ptr<Cell>> bestSelf;
	std::vector<int> selfValues;

	for (auto &line : _board.getCells()) {
		for (auto &cell : line) {
			if (cell->getId() == 0)
				selfValues.push_back(cell->getRawValueSelf());
		}
	}

	std::sort(selfValues.begin(), selfValues.end(), mySort);
	std::vector<int>::const_iterator first = selfValues.begin();
	if (nb > static_cast<int>(selfValues.size()))
		nb = static_cast<int>(selfValues.size());
	std::vector<int>::const_iterator last = selfValues.begin() + nb;
	std::vector<int> bestSelfValues(first, last);

	for (auto &line : _board.getCells()) {
		for (auto &cell : line) {
			int count = 0;
			for (auto &selfValue : bestSelfValues) {
				if (selfValue == cell->getRawValueSelf() && cell->getId() == 0) {
					bestSelf.push_back(cell);
					auto it = bestSelfValues.begin();
					std::advance(it, count);
					bestSelfValues.erase(it);
					break;
				}
				count++;
			}
		}
	}
	return bestSelf;
}

std::vector<std::shared_ptr<Cell>> Brain::getNBestCellsOpponent(int nb)
{
	std::vector<std::shared_ptr<Cell>> bestOpponent;
	std::vector<int> opponentValues;

	for (auto &line : _board.getCells()) {
		for (auto &cell : line) {
			if (cell->getId() == 0)
				opponentValues.push_back(cell->getRawValueOpponent());
		}
	}

	std::sort(opponentValues.begin(), opponentValues.end(), mySort);
	std::vector<int>::const_iterator first = opponentValues.begin();
	if (nb > static_cast<int>(opponentValues.size()))
		nb = static_cast<int>(opponentValues.size());
	std::vector<int>::const_iterator last = opponentValues.begin() + nb;
	std::vector<int> bestOpponentValues(first, last);

	for (auto &line : _board.getCells()) {
		for (auto &cell : line) {
			int count = 0;
			for (auto &opponentValue : bestOpponentValues) {
				if (opponentValue == cell->getRawValueOpponent() && cell->getId() == 0) {
					bestOpponent.push_back(cell);
					auto it = bestOpponentValues.begin();
					std::advance(it, count);
					bestOpponentValues.erase(it);
					break;
				}
				count++;
			}
		}
	}
	return bestOpponent;
}

int Brain::simulate(std::shared_ptr<Cell> &cell, int team)
{
	cell->setId(team);
	int st = _board.getAmountSpecialCombination();
	cell->setId(0);
	return st;
}
