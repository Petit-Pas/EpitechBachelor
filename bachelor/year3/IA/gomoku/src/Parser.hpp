/*
** EPITECH PROJECT, 2021
** 302separation
** File description:
** internal functions
*/

#ifndef INC_302SEPARATION_PARSER_HPP
# define INC_302SEPARATION_PARSER_HPP

#include <string>
#include <fstream>
#include <regex>
#include <map>
#include "gomoku.hpp"

class Parser {
public:
	Parser();
	Parser(const Parser &toCopy);

	gom::state parse();
	gom::state handleBegin(const std::string &input);
	gom::state handleStart(const std::string &input);
	gom::state handleTurn(const std::string &input);
	gom::state handleBoard(const std::string &input);
	gom::state handleEnd(const std::string &input);
	gom::state handleInfo(const std::string &input);
	gom::state handleAbout(const std::string &input);

	std::pair<int, int> &getTurn();
	int getBoardSize() const;
	std::vector<std::string> &getTurns();

private:
	std::regex _regexStart;
	std::regex _regexTurn;
	std::regex _regexInfo;
	std::pair<int, int> _turnPlayed;
	std::map<std::string, gom::state (Parser::*)(const std::string &)> _dico;
	int _boardSize;
	std::vector<std::string> _turnsToPlay;
};

#endif //INC_302SEPARATION_PARSER_HPP
