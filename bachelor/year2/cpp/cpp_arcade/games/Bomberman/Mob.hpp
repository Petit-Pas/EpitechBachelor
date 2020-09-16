/*
** EPITECH PROJECT, 2021
** cpp_arcade
** File description:
** internal functions
*/

#ifndef CPP_ARCADE_MOB_HPP
# define CPP_ARCADE_MOB_HPP

#include "Map.hpp"

namespace ar {
	class Mob {
	public:
		Mob(int posX, int posY);
		~Mob() = default;

		bool live(Map &map);


	private:
		void findPossibleWays(int *possibleWays, Map &map);

		int amountOfHighPriority(int *possibleWays);
		void chooseHighPriority(int *possibleWays);
		bool isLowPriority(int *possibleWays);
		void goLowerPriority(int *possibleWays);

		int _posX;
		int _posY;
		int _oldX;
		int _oldY;
	};
};

#endif //CPP_ARCADE_MOB_HPP
