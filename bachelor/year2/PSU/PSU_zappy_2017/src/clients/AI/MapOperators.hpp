//
// EPITECH PROJECT, 2018
// Zappy
// File description:
// operators overload
//

#ifndef ZAPPY_MAP_OPERATORS_HPP
#define ZAPPY_MAP_OPERATORS_HPP

#include <unordered_map>
#include <map>
#include <string>

std::unordered_map<std::string, std::size_t> operator+(std::unordered_map<std::string, std::size_t> &, std::unordered_map<std::string, std::size_t>);
bool operator>=(std::unordered_map<std::string, std::size_t> &, std::map<std::string, std::size_t> &);

#endif //ZAPPY_MAP_OPERATORS_HPP
