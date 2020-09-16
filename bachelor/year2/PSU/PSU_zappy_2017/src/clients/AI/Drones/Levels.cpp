//
// EPITECH PROJECT, 2018
// zappy
// File description:
// Level helper
//

#include "Levels.hpp"

const std::unordered_map<std::string, size_t> Level::getRequirementsForPeoples(size_t nb)
{
	std::unordered_map<std::string, size_t> max;

	if (nb == 0)
		nb = 1;
	for (const auto &req : LEVELS_REQUIREMENT) {
		if (req.second.at("player") == nb) {
			for (const auto &resources : req.second) {
				if (max.find(resources.first) == max.end() ||
				    max[resources.first] < resources.second)
					max[resources.first] = resources.second;
			}
		}
	}
	return (max);
}

std::map<std::string, size_t> Level::getRequirementsForPeoples2(size_t nb)
{
	std::map<std::string, size_t> max;

	if (nb == 0)
		nb = 1;
	for (const auto &req : LEVELS_REQUIREMENT) {
		if (req.second.at("player") == nb) {
			for (const auto &resources : req.second) {
				if (max.find(resources.first) == max.end() ||
					max[resources.first] < resources.second)
					max[resources.first] = resources.second;
			}
		}
	}
	return (max);
}

const std::unordered_map<std::string, size_t> Level::getNeed()
{
	std::unordered_map<std::string, size_t> max;

	for (const auto &req : LEVELS_REQUIREMENT) {
		for (const auto &resources : req.second) {
			if (resources.first != "player" &&
			    (max.find(resources.first) == max.end() || max[resources.first] < resources.second))
				max[resources.first] = resources.second;
		}
	}
	return (max);
}

size_t Level::getNbPeopleNeeded(const size_t nb)
{
	return LEVELS_REQUIREMENT.at(nb).at("player");
}
