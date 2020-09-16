/*
** EPITECH PROJECT, 2021
** pbrain-gomoku
** File description:
** internal functions
*/

#include <iostream>
#include "Combination.hpp"
#include "gomoku.hpp"
#include "Cell.hpp"

Combination::Combination(std::vector<std::shared_ptr<Cell>> &cells) : _cells(cells), _valueSelf(gom::EMPTY), _valueOpponent(gom::EMPTY)
{
	for (int i = 0; i != 5; i++) {
		_content.push_back(0);
	}
}

std::vector<std::shared_ptr<Cell>> &Combination::getCells()
{
	return _cells;
}

void Combination::refreshContent()
{
	for (int i = 0; i != 5; i++) {
		_content[i] = _cells[i]->getId();
	}
}

gom::combinations Combination::getValueSelf() const
{
	return _valueSelf;
}

gom::combinations Combination::getValueOpponent() const
{
	return _valueOpponent;
}

void Combination::evaluateValues()
{
	_valueSelf = evaluateValue(1, 2);
	_valueOpponent = evaluateValue(2, 1);
	for (auto &cell : _cells) {
		cell->computeCombinationsValues();
		cell->calculateSpecialTurn();
	}
}

gom::combinations Combination::evaluateValue(int ally, int opponent)
{
	int amountAlly = 0;
	int amountOpponent = 0;

	for (auto &cell : _cells) {
		if (cell->getId() == ally)
			amountAlly += 1;
		else if (cell->getId() == opponent)
			amountOpponent += 1;
	}
	if (amountOpponent != 0)
		return gom::combinations::IMPOSSIBLE;
	else if (amountAlly == 1)
		return gom::combinations::ONE;
	else if (amountAlly == 2)
		return gom::combinations::TWO;
	else if (amountAlly == 3) {
		if ((_cells[0]->getId() == 0 || _cells[0]->getId() != 0) || (_cells[0]->getId() != 0 || _cells[0]->getId() == 0))
			return gom::combinations::NO_LIMIT_THREE;
		return gom::combinations::THREE;
	}
	else if (amountAlly == 4)
		return gom::combinations::FOUR;
	return gom::combinations::EMPTY;
}
