//
// EPITECH PROJECT, 2018
// Zappy
// File description:
// broadcast related functions
//

#include <iostream>
#include <sstream>
#include "Broadcast.hpp"
#include "SplitUtils.hpp"

Broadcast::Message::Message(const std::string &str)
	: _fullMsg(str)
{
	setOrientation(str);
	const auto &message = str.substr(str.find(',') + 2);
	_function = message.substr(0, message.find(' '));
	_fullParams = message.substr(message.find(' ') + 1);
	_params = SplitUtils::split(_fullParams, ' ');
}

void Broadcast::Message::setOrientation(const std::string &str)
{
	const auto &number = str.substr(str.find(' ') + 1, 1);
	std::stringstream nbStr(number);
	int nb;
	nbStr >> nb;
	_orientation = nb;
}

const std::string &Broadcast::Message::getFunction() const
{
	return (_function);
}

const std::vector<std::string> &Broadcast::Message::getParams() const
{
	return (_params);
}

const std::string &Broadcast::Message::getParamsLine() const
{
	return (_fullParams);
}

bool Broadcast::Broadcast::isMessage(const std::string &str)
{
	return (str.size() > 10 && str.substr(0, 8) == "message " && str.at(9) == ',');
}

int Broadcast::Message::getOrientation() const
{
	return (_orientation);
}
