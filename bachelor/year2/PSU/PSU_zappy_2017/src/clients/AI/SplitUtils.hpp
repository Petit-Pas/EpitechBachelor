/*
** EPITECH PROJECT, 2018
** client
** File description:
** split
*/

#ifndef CLIENT_SPLIT_UTILS_HPP
#define CLIENT_SPLIT_UTILS_HPP

#include <vector>
#include <string>

class SplitUtils {
public:
	static std::vector<std::string> split
		(const std::string &str, char delim);
};

#endif //CLIENT_UTILS_HPP
