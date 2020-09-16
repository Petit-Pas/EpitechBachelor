/*
** EPITECH PROJECT, 2018
** client
** File description:
** Created by martin.van-elslande@epitech.eu,
*/

#include "Utils.hpp"

#include <sstream>
#include "Utils.hpp"

std::vector<std::string> Utils::split(const std::string &str, char delim)
{
	std::vector<std::string> parts;
	std::string part;
	std::istringstream stream(str);
	while (getline(stream, part, delim))
		if (!part.empty())
			parts.push_back(part);
	return parts;
}