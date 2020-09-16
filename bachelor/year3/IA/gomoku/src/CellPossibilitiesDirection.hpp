/*
** EPITECH PROJECT, 2021
** pbrain-gomoku
** File description:
** internal functions
*/

#ifndef PBRAIN_GOMOKU_CELLPOSSIBILITIES_HPP
# define PBRAIN_GOMOKU_CELLPOSSIBILITIES_HPP

#include <vector>
#include "gomoku.hpp"
#include "Combination.hpp"

class CellPossibilitiesDirection {
public:
	CellPossibilitiesDirection();

	void addCombination(std::shared_ptr<Combination> &combination);
	void computeCombinations();
	void calculateSpecialTurn();
	void calculateRawValue();
	void calculateThrees();

	gom::specialTurn getSpecialTurn();
	bool getThreeSelf();
	bool getThreeOpponent();
	int getRawValue();
	int getRawValueSelf();
	int getRawValueOpponent();

private:
	gom::specialTurn _turn;
	int _rawSelf;
	int _rawOpponent;
	bool _threeSelf;
	bool _threeOpponent;
	std::vector<std::shared_ptr<Combination>> _combinations;
	std::vector<gom::combinations> _value;
	std::vector<gom::combinations> _valueOpponent;
};

#endif //PBRAIN_GOMOKU_CELLPOSSIBILITIES_HPP
