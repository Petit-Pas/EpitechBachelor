/*
** EPITECH PROJECT, 2018
** client
** File description:
** split
*/

#include <sstream>
#include "SplitUtils.hpp"

std::vector<std::string> SplitUtils::split(const std::string &str, char delim)
{
	std::vector<std::string> parts;
	std::string part;
	std::istringstream stream(str);
	while (getline(stream, part, delim))
		parts.push_back(part);
	return parts;
}
