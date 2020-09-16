/*
** EPITECH PROJECT, 2021
** pbrain-gomoku
** File description:
** internal functions
*/

#include <iostream>
#include <map>
#include <algorithm>
#include <regex>
#include "Board.hpp"
#include "gomoku.hpp"
#include "Combination.hpp"

Board::Board(int size) : _size(size)
{
	for (int y = 0; y != _size; y++) {
		std::vector<std::shared_ptr<Cell>> temp;
		for (int x = 0; x != _size; x++) {
			Cell tempCell(x, y, 0);
			temp.push_back(std::make_shared<Cell>(tempCell));
		}
		_cells.push_back(temp);
	}
	setCombinations();
	computeTurns();
}

void Board::setCombinations()
{
	setCombinations(1, 0, 1);
	setCombinations(0, 1, 0);
	setCombinations(1, 1, 2);
	setCombinations(1, -1, 3);
}

void Board::setCombinations(int deltaX, int deltaY, int func)
{
	for (int y = 0; y != _size; y++) {
		for (int x = 0; x != _size; x++) {
			setCombinations(x, y, deltaX, deltaY, func);
		}
	}
}

void Board::setCombinations(int x, int y, int deltaX, int deltaY, int func)
{
	std::vector<std::shared_ptr<Cell>> cells;
	static std::map<int, void (Cell::*)(std::shared_ptr<Combination> &)> dico = {
		{0, &Cell::addCombinationVertical},
		{1, &Cell::addCombinationHorizontal},
		{2, &Cell::addCombinationTLBR},
		{3, &Cell::addCombinationBLTR}};

	if (x + 4 * deltaX >= _size || x + 4 * deltaX < 0 ||
		y + 4 * deltaY >= _size || y + 4 * deltaY < 0)
		return;
	for (int i = 0; i != 5; i += 1) {
		cells.push_back(_cells[y + i * deltaY][x + i * deltaX]);
	}
	Combination combination(cells);
	auto ptr = std::make_shared<Combination>(combination);
	_combinations.push_back(ptr);
	for (auto &cell : ptr->getCells()) {
		for (auto &command : dico) {
			if (command.first == func) {
				((*cell).*(command.second))(ptr);
				break;
			}
		}
	}
}

void Board::displayBoard()
{
	for (auto &line : _cells) {
		for (auto &cell : line) {
			std::cout << cell->getId() << " ";
		}
		std::cout << std::endl;
	}
}

void Board::displayRawValues()
{
	for (auto &line : _cells) {
		for (auto &cell : line) {
			std::cout << cell->getRawValue() << "\t";
		}
		std::cout << std::endl;
	}
}

void Board::setCellId(int x, int y, int value)
{
	_cells[y][x]->setId(value);
}

int Board::getSize()
{
	return _size;
}

gom::specialTurn Board::getHighestCombination()
{
	std::vector<gom::specialTurn> turns;

	for (auto &line : _cells) {
		for (auto &cell : line) {
			if (cell->getId() != 0)
				continue;
			turns.push_back(cell->getSpecialTurn());
		}
	}
	return *std::max_element(turns.begin(), turns.end());
}

std::vector<std::shared_ptr<Cell>> Board::getCellsBySpecialTurn(
	gom::specialTurn turn
)
{
	std::vector<std::shared_ptr<Cell>> cells;

	for (auto &line : _cells) {
		for (auto &cell : line) {
			if (cell->getId() != 0)
				continue;
			if (cell->getSpecialTurn() == turn)
				cells.push_back(cell);
		}
	}
	return cells;
}

std::shared_ptr<Cell> Board::getHighestValuedCell()
{
	int value = _cells[0][0]->getRawValue();
	std::vector<std::shared_ptr<Cell>> valuedCells;

	valuedCells.push_back(_cells[0][0]);
	if (valuedCells[0]->getRawValue() != 0)
		value = -1;

	for (auto &line : _cells) {
		for (auto &cell : line) {
			if (cell->getId() != 0)
				continue;
			else if (cell->getRawValue() > value) {
				valuedCells = {};
				valuedCells.push_back(cell);
				value = cell->getRawValue();
			}
			else if (cell->getRawValue() == value) {
				valuedCells.push_back(cell);
			}
		}
	}
	return valuedCells[rand() % valuedCells.size()];
}

void Board::setup(const std::vector<std::string> &turns)
{
	for (auto &line : _cells) {
		for (auto &cell : line) {
			cell->setId(0);
		}
	}
	std::smatch matches;
	static std::regex regex("([0-9]+),([0-9]+),([0-9]+)");

	for (auto &line : turns) {
		std::regex_search(line, matches, regex);
		if (matches.size() != 4)
			continue;
		_cells[std::stoi(matches[2])][std::stoi(matches[1])]->setId(std::stoi(matches[3]));
	}
}

void Board::computeTurns()
{
	for (auto &line : _cells) {
		for (auto &cell : line) {
			cell->computeCombinationsValues();
			cell->calculateSpecialTurn();
		}
	}
}

std::vector<std::vector<std::shared_ptr<Cell>>> &Board::getCells()
{
	return _cells;
}

void Board::displayRawValuesSelf()
{
	for (auto &line : _cells) {
		for (auto &cell : line) {
			std::cout << cell->getRawValueSelf() << "\t";
		}
		std::cout << std::endl;
	}
}

void Board::displayRawValuesOpponent()
{
	for (auto &line : _cells) {
		for (auto &cell : line) {
			std::cout << cell->getRawValueOpponent() << "\t";
		}
		std::cout << std::endl;
	}
}

int Board::getAmountSpecialCombination()
{
	int count = 0;

	for (auto &line : _cells) {
		for (auto &cell : line) {
			if (cell->getSpecialTurn() != gom::specialTurn::NO_SPECIAL)
				count += 1;
		}
	}
	return count;
}
