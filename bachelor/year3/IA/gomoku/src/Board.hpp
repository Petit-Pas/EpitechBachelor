/*
** EPITECH PROJECT, 2021
** pbrain-gomoku
** File description:
** internal functions
*/

#ifndef PBRAIN_GOMOKU_BOARD_HPP
# define PBRAIN_GOMOKU_BOARD_HPP

#include <vector>
#include <memory>
#include "Cell.hpp"

// A Board contains Cells, each Cell contains a certain amount of

class Board {
public:
	Board(int size);
	~Board() = default;
	void displayBoard();
	void displayRawValues();
	void displayRawValuesSelf();
	void displayRawValuesOpponent();

	void setup(const std::vector<std::string> &turns);
	void computeTurns();

	void setCombinations();
	void setCombinations(int deltaX, int deltaY, int func);
	void setCombinations(int x, int y, int deltaX, int deltaY, int func);

	void setCellId(int x, int y, int value);
	int getSize();
	gom::specialTurn getHighestCombination();
	int getAmountSpecialCombination();
	std::vector<std::shared_ptr<Cell>> getCellsBySpecialTurn(gom::specialTurn turn);
	std::shared_ptr<Cell> getHighestValuedCell();
	std::vector<std::vector<std::shared_ptr<Cell>>> &getCells();

private:
	int _size;
	std::vector<std::vector<std::shared_ptr<Cell>>> _cells;
	std::vector<std::shared_ptr<Combination>> _combinations;
};

#endif //PBRAIN_GOMOKU_BOARD_HPP
