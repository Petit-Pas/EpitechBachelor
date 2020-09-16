/*
** EPITECH PROJECT, 2021
** cpp_indie_studio
** File description:
** internal functions
*/

#ifndef CPP_INDIE_STUDIO_DIRECTION_HPP
# define CPP_INDIE_STUDIO_DIRECTION_HPP

#include <vector>
#include <utility>

namespace dir {
	enum directions {
		NONE = 0,
		UP = 1,
		DOWN = 2,
		LEFT = 3,
		RIGHT = 4
	};

	const std::vector<std::pair<float, float>> directionPos = {std::pair<float, float>(0, 0),
		std::pair<float, float>(-1, 0), std::pair<float, float>(1, 0), std::pair<float, float>(0, -1),
		std::pair<float, float>(0, 1)};
}
#endif //CPP_INDIE_STUDIO_DIRECTION_HPP
