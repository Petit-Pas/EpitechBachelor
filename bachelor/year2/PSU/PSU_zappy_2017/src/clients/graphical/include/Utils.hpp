/*
** EPITECH PROJECT, 2018
** client
** File description:
** Created by martin.van-elslande@epitech.eu,
*/

#ifndef CLIENT_UTILS_HPP
#define CLIENT_UTILS_HPP

#include <vector>
#include <string>

class Utils {
public:
	static std::vector<std::string> split(const std::string &str,
		char delim
	);
};

#endif //CLIENT_UTILS_HPP
