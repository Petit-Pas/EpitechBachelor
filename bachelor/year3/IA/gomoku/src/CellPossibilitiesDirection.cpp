/*
** EPITECH PROJECT, 2021
** pbrain-gomoku
** File description:
** internal functions
*/

#include <algorithm>
#include <iostream>
#include "CellPossibilitiesDirection.hpp"

CellPossibilitiesDirection::CellPossibilitiesDirection() : _turn(gom::specialTurn::NO_SPECIAL), _rawSelf(0), _rawOpponent(0), _threeSelf(false), _threeOpponent(false)
{
}

void CellPossibilitiesDirection::addCombination(
	std::shared_ptr<Combination> &combination
)
{
	_combinations.push_back(combination);
}

void CellPossibilitiesDirection::computeCombinations()
{
	_value = {};
	_valueOpponent = {};
	for (auto &combination : _combinations) {
		_value.push_back(combination->getValueSelf());
		_valueOpponent.push_back(combination->getValueOpponent());
	}
	calculateSpecialTurn();
	calculateThrees();
	calculateRawValue();
}

void CellPossibilitiesDirection::calculateSpecialTurn()
{
	if (std::find(_value.begin(), _value.end(), gom::combinations::FOUR) != _value.end()) {
		_turn = gom::specialTurn::WIN_4;
	}
	else if (std::find(_valueOpponent.begin(), _valueOpponent.end(), gom::combinations::FOUR) != _valueOpponent.end())
		_turn = gom::specialTurn::LOOSE_4;
	else if (std::count(_value.begin(), _value.end(), gom::combinations::NO_LIMIT_THREE) > 1)
		_turn = gom::specialTurn::WIN_2_3;
	else if (std::count(_valueOpponent.begin(), _valueOpponent.end(), gom::combinations::NO_LIMIT_THREE) > 1)
		_turn = gom::specialTurn::LOOSE_2_3;
	else
		_turn = gom::specialTurn::NO_SPECIAL;
}

void CellPossibilitiesDirection::calculateRawValue()
{
	_rawSelf = 0;
	_rawOpponent = 0;

	_rawSelf += 2 * std::count(_value.begin(), _value.end(), gom::combinations::ONE);
	_rawSelf += 3 * std::count(_value.begin(), _value.end(), gom::combinations::TWO);
	_rawSelf += 4 * std::count(_value.begin(), _value.end(), gom::combinations::THREE);
	_rawSelf += 4 * std::count(_value.begin(), _value.end(), gom::combinations::NO_LIMIT_THREE);

	int amount = 0;
	for (auto &comb : _combinations) {
		if (comb->getValueSelf() != gom::combinations::IMPOSSIBLE)
			amount += 1;
	}
	_rawSelf += amount;

	_rawOpponent += 2 * std::count(_valueOpponent.begin(), _valueOpponent.end(), gom::combinations::ONE);
	_rawOpponent += 3 * std::count(_valueOpponent.begin(), _valueOpponent.end(), gom::combinations::TWO);
	_rawOpponent += 4 * std::count(_valueOpponent.begin(), _valueOpponent.end(), gom::combinations::THREE);
	_rawOpponent += 4 * std::count(_valueOpponent.begin(), _valueOpponent.end(), gom::combinations::NO_LIMIT_THREE);

	amount = 0;
	for (auto &comb : _combinations) {
		if (comb->getValueOpponent() != gom::combinations::IMPOSSIBLE)
			amount += 1;
	}
	_rawOpponent += amount;
}

void CellPossibilitiesDirection::calculateThrees()
{
	_threeSelf = false;
	_threeOpponent = false;
	if (std::find(_value.begin(), _value.end(), gom::combinations::THREE) != _value.end()
		|| std::find(_value.begin(), _value.end(), gom::combinations::NO_LIMIT_THREE) != _value.end())
		_threeSelf = true;
	if (std::find(_valueOpponent.begin(), _valueOpponent.end(), gom::combinations::THREE) != _valueOpponent.end()
		|| std::find(_valueOpponent.begin(), _valueOpponent.end(), gom::combinations::NO_LIMIT_THREE) != _valueOpponent.end())
		_threeOpponent = true;
}

gom::specialTurn CellPossibilitiesDirection::getSpecialTurn()
{
	return _turn;
}

bool CellPossibilitiesDirection::getThreeSelf()
{
	return _threeSelf;
}

bool CellPossibilitiesDirection::getThreeOpponent()
{
	return _threeOpponent;
}

int CellPossibilitiesDirection::getRawValue()
{
	return static_cast<int>(_rawSelf + _rawOpponent * 0.5);
}

int CellPossibilitiesDirection::getRawValueSelf()
{
	return _rawSelf;
}

int CellPossibilitiesDirection::getRawValueOpponent()
{
	return _rawOpponent;
}
