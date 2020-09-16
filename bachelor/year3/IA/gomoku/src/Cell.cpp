/*²²
** EPITECH PROJECT, 2021
** pbrain-gomoku
** File description:
** internal functions
*/

#include <iostream>
#include <algorithm>
#include "Cell.hpp"
#include "gomoku.hpp"
#include "Combination.hpp"

Cell::Cell(int x, int y, int value) : _x(x), _y(y), _id(value), _rawValue(0), _rawValueSelf(0), _rawValueOpponent(0), _turn(gom::specialTurn::NO_SPECIAL)
{
}

int Cell::getId() const
{
	return _id;
}

void Cell::setId(int value)
{
	_id = value;
	for (auto &combination : _allCombinations) {
		combination->refreshContent();
	}
	refreshCombinationsValues();
}

void Cell::displayCombinations() const
{
}

void Cell::addCombinationVertical(std::shared_ptr<Combination> &combination)
{
	_vertical.addCombination(combination);
	_allCombinations.push_back(combination);
}

void Cell::addCombinationHorizontal(std::shared_ptr<Combination> &combination)
{
	_horizontal.addCombination(combination);
	_allCombinations.push_back(combination);
}

void Cell::addCombinationTLBR(std::shared_ptr<Combination> &combination)
{
	_TLBR.addCombination(combination);
	_allCombinations.push_back(combination);
}

void Cell::addCombinationBLTR(std::shared_ptr<Combination> &combination)
{
	_BLTR.addCombination(combination);
	_allCombinations.push_back(combination);
}

void Cell::refreshCombinationsValues()
{
	for (auto &combination : _allCombinations) {
		combination->evaluateValues();
	}
	computeCombinationsValues();
}

void Cell::computeCombinationsValues()
{
	if (_id != 0)
		return;
	_horizontal.computeCombinations();
	_vertical.computeCombinations();
	_TLBR.computeCombinations();
	_BLTR.computeCombinations();
}

void Cell::calculateSpecialTurn()
{
	if (_id != 0)
		return;
	std::vector<gom::specialTurn> turns;

	turns.push_back(_horizontal.getSpecialTurn());
	turns.push_back(_vertical.getSpecialTurn());
	turns.push_back(_TLBR.getSpecialTurn());
	turns.push_back(_BLTR.getSpecialTurn());
	gom::specialTurn turn = *std::max_element(turns.begin(), turns.end());
	if (turn == gom::NO_SPECIAL || turn == gom::LOOSE_2_3)
		_turn = checkDoubleThreeTurn(turn);
	else
		_turn = turn;
	calculateRawValues();
}

gom::specialTurn Cell::checkDoubleThreeTurn(gom::specialTurn turn)
{
	int countSelf = 0;
	int countOpponent = 0;

	countSelf += _vertical.getThreeSelf();
	countOpponent += _vertical.getThreeOpponent();
	countSelf += _horizontal.getThreeSelf();
	countOpponent += _horizontal.getThreeOpponent();
	countSelf += _TLBR.getThreeSelf();
	countOpponent += _TLBR.getThreeOpponent();
	countSelf += _BLTR.getThreeSelf();
	countOpponent += _BLTR.getThreeOpponent();

	if (countSelf > 1)
		return gom::WIN_2_3;
	if (countOpponent > 1)
		return gom::LOOSE_2_3;
	return turn;
}

gom::specialTurn Cell::getSpecialTurn()
{
	return _turn;
}

int Cell::getX()
{
	return _x;
}

int Cell::getY()
{
	return _y;
}

int Cell::getRawValue()
{
	return _rawValue;
}

void Cell::calculateRawValues()
{
	_rawValue = 0;
	_rawValue += _horizontal.getRawValue();
	_rawValue += _vertical.getRawValue();
	_rawValue += _TLBR.getRawValue();
	_rawValue += _BLTR.getRawValue();

	_rawValueSelf = 0;
	_rawValueSelf += _horizontal.getRawValue();
	_rawValueSelf += _vertical.getRawValue();
	_rawValueSelf += _TLBR.getRawValue();
	_rawValueSelf += _BLTR.getRawValue();

	_rawValueOpponent = 0;
	_rawValueOpponent += _horizontal.getRawValue();
	_rawValueOpponent += _vertical.getRawValue();
	_rawValueOpponent += _TLBR.getRawValue();
	_rawValueOpponent += _BLTR.getRawValue();

}

int Cell::getRawValueSelf()
{
	return _rawValueSelf;
}

int Cell::getRawValueOpponent()
{
	return _rawValueOpponent;
}
