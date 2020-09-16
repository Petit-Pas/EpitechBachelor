/*
** EPITECH PROJECT, 2021
** pbrain-gomoku
** File description:
** internal functions
*/

#ifndef PBRAIN_GOMOKU_BRAIN_HPP
# define PBRAIN_GOMOKU_BRAIN_HPP

#include "Board.hpp"
#include "Parser.hpp"

class Brain {
public:
	Brain(Parser &parser);
	~Brain();

	void process();
	void play();
	void otherPlays();
	void setupBoard();

	void chooseBySpecialTurn(gom::specialTurn turn);
	void chooseByValue();
	bool chooseWithPrevision();

	std::vector<std::shared_ptr<Cell>> getNBestCellsSelf(int nb);
	std::vector<std::shared_ptr<Cell>> getNBestCellsOpponent(int nb);
	int simulate(std::shared_ptr<Cell> &cell, int team);

private:
	Board _board;
	Parser _parser;
	std::map<gom::state, void (Brain::*)()> _dico;
};

#endif //PBRAIN_GOMOKU_BRAIN_HPP
