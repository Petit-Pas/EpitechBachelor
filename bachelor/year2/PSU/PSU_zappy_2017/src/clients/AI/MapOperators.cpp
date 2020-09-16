//
// EPITECH PROJECT, 2018
// Zappy
// File description:
// Operators overload
//

#include <iostream>
#include "MapOperators.hpp"

std::unordered_map<std::string, std::size_t> operator+(std::unordered_map<std::string, std::size_t> &currentInventory, std::unordered_map<std::string, std::size_t> addedInventory)
{
	std::unordered_map<std::string, std::size_t> newInventory = addedInventory;

	for (auto &it : currentInventory) {
		if (newInventory.find(it.first) == newInventory.end())
			newInventory.insert({it.first, 0});
	}
	for (auto &it : newInventory) {
		if (it.first != "player" && currentInventory.find(it.first) != currentInventory.end())
			it.second += currentInventory.find(it.first)->second;
	}
	return (newInventory);
}

bool operator>=(std::unordered_map<std::string, std::size_t> &currentInventory, std::map<std::string, std::size_t> &comparedInventory)
{
	for (const auto &it : comparedInventory) {
		if (it.first != "player" && it.first != "reliability" &&
			((currentInventory.find(it.first) == currentInventory.end() && it.second != 0) ||
			(currentInventory.find(it.first) != currentInventory.end() && it.second > currentInventory.find(it.first)->second))) {
			return (false);
		}
	}
	return (true);
}