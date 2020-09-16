/*
** EPITECH PROJECT, 2021
** pbrain-gomoku
** File description:
** internal functions
*/

#ifndef PBRAIN_GOMOKU_CELL_HPP
# define PBRAIN_GOMOKU_CELL_HPP

#include <memory>
#include <vector>
#include "gomoku.hpp"
#include "CellPossibilitiesDirection.hpp"

class Combination;

class Cell {
public:
	Cell(int x, int y, int value);

	int getId() const;
	void setId(int value);
	int getX();
	int getY();
	int getRawValue();
	int getRawValueSelf();
	int getRawValueOpponent();

	void addCombinationVertical(std::shared_ptr<Combination> &combination);
	void addCombinationHorizontal(std::shared_ptr<Combination> &combination);
	void addCombinationTLBR(std::shared_ptr<Combination> &combination);
	void addCombinationBLTR(std::shared_ptr<Combination> &combination);

	void refreshCombinationsValues();
	void computeCombinationsValues();
	void displayCombinations() const;

	void calculateSpecialTurn();
	void calculateRawValues();
	gom::specialTurn checkDoubleThreeTurn(gom::specialTurn turn);

	gom::specialTurn getSpecialTurn();

private:
	int _x;
	int _y;
	int _id;
	int _rawValue;
	int _rawValueSelf;
	int _rawValueOpponent;
	gom::specialTurn _turn;
	CellPossibilitiesDirection _vertical;
	CellPossibilitiesDirection _horizontal;
	CellPossibilitiesDirection _TLBR;
	CellPossibilitiesDirection _BLTR;
	std::vector<std::shared_ptr<Combination>> _allCombinations;
};

#endif //PBRAIN_GOMOKU_CELL_HPP
