/*
** EPITECH PROJECT, 2021
** pbrain-gomoku
** File description:
** internal functions
*/

#ifndef PBRAIN_GOMOKU_COMBINATION_HPP
# define PBRAIN_GOMOKU_COMBINATION_HPP

#include <vector>
#include <memory>
#include "gomoku.hpp"

class Cell;

class Combination {
public:
	explicit Combination(std::vector<std::shared_ptr<Cell>> &cells);

	std::vector<std::shared_ptr<Cell>> &getCells();
	void refreshContent();

	void evaluateValues();
	gom::combinations evaluateValue(int ally, int ennemy);

	gom::combinations getValueSelf() const;
	gom::combinations getValueOpponent() const;

private:
	std::vector<std::shared_ptr<Cell>> _cells;
	std::vector<int> _content;
	gom::combinations _valueSelf;
	gom::combinations _valueOpponent;
};

#endif //PBRAIN_GOMOKU_COMBINATION_HPP
