/*
** EPITECH PROJECT, 2021
** 302separation
** File description:
** internal functions
*/

#include <string>
#include "Parser.hpp"

#include <sstream>
#include <string>
#include <regex>
#include <fstream>
#include <iostream>

//implement RESTART ?
Parser::Parser() : _regexStart("START ([0-9]+)"),
	_regexTurn("TURN ([0-9]+),([0-9]+)"), _regexInfo("INFO .+"),
	_turnPlayed(-1, -1),
	_dico({{"START", &Parser::handleStart}, {"BEGIN", &Parser::handleBegin},
		{"TURN", &Parser::handleTurn}, {"BOARD", &Parser::handleBoard},
		{"END", &Parser::handleEnd}, {"INFO", &Parser::handleInfo},
		{"ABOUT", &Parser::handleAbout}}), _boardSize(0)
{
}

gom::state Parser::parse()
{
	std::string input;

	std::getline(std::cin, input);
	if (!std::cin)
		return gom::END;
	for (auto &command : _dico) {
		if (input.find(command.first) == 0) {
			gom::state state = (this->*(command.second))(input);
			if (state == gom::UNKNOWN) {
				std::cout << "ERROR" << std::endl;
			}
			return state;
		}
	}
	std::cout << "ERROR" << std::endl;
	return gom::UNKNOWN;
}

gom::state Parser::handleBegin(const std::string &input)
{
	if (input == "BEGIN")
		return gom::YOU_PLAY;
	return gom::UNKNOWN;
}

gom::state Parser::handleStart(const std::string &input)
{
	std::smatch matches;

	std::regex_search(input, matches, _regexStart);
	if (matches.size() != 2)
		return gom::UNKNOWN;
	_boardSize = std::stoi(matches[1]);
	return gom::START;
}

gom::state Parser::handleTurn(const std::string &input)
{
	std::smatch matches;

	std::regex_search(input, matches, _regexTurn);
	if (matches.size() != 3)
		return gom::UNKNOWN;
	_turnPlayed = {std::stoi(matches[1]), std::stoi(matches[2])};
	return gom::OTHER_PLAYED;
}

gom::state Parser::handleBoard(const std::string &inputRcv)
{
	std::string input;

	_turnsToPlay = {};
	if (inputRcv != "BOARD")
		return gom::UNKNOWN;
	while (input != "DONE") {
		std::getline(std::cin, input);
		_turnsToPlay.push_back(input);
	}
	return gom::BOARD;
}

gom::state Parser::handleEnd(const std::string &input)
{
	if (input == "END")
		return gom::END;
	return gom::UNKNOWN;
}

gom::state Parser::handleInfo(const std::string &input)
{
	std::smatch matches;

	std::regex_search(input, matches, _regexInfo);
	if (matches.size() != 1)
		return gom::UNKNOWN;
	return gom::INFO;
}

gom::state Parser::handleAbout(const std::string &input)
{
	if (input != "ABOUT")
		return gom::UNKNOWN;
	std::cout
		<< R"(name="JambonBeurre", version="-1.0", author="Benoit H. & Thomas G. & Hugo C.", country="EPI")"
		<< std::endl;
	return gom::ABOUT;
}

std::pair<int, int> &Parser::getTurn()
{
	return _turnPlayed;
}

int Parser::getBoardSize() const
{
	return _boardSize;
}

std::vector<std::string> &Parser::getTurns()
{
	return _turnsToPlay;
}

Parser::Parser(const Parser &toCopy) : _regexStart(toCopy._regexStart),
	_regexTurn(toCopy._regexTurn), _regexInfo(toCopy._regexInfo),
	_turnPlayed(toCopy._turnPlayed), _dico(toCopy._dico),
	_boardSize(toCopy._boardSize), _turnsToPlay(toCopy._turnsToPlay)
{
}
