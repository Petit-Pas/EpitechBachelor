/*
** EPITECH PROJECT, 2021
** cpp_arcade
** File description:
** internal functions
*/

/**
 * \file
 * contains the ar::Flame class for the ar::Qix game
 */

#ifndef CPP_ARCADE_FLAME_HPP
# define CPP_ARCADE_FLAME_HPP

#include "Map.hpp"
#include "TextureQix.hpp"

namespace ar {
	/**
	 * ar::Flame class for ar::Qix game
	 */
	class Flame {
	public:
		/**
		 * Generate a flame at the start of the player trail
		 * @param map The reference of the actual map
		 * @param x The player x-coordinates
		 * @param y The player y-coordinates
		 */
		Flame(Map &map, int x, int y);
		~Flame();

		/**
		 * the function called by ar::Qix to make the flame go forward
		 * @return true if the player is hit, false otherwise
		 */
		bool live();
	private:
		/**
		 * pathfind to the border, as it spawns on the player
		 */
		void goBack();

		/**
		 * check if a cell is well inside the map
		 * @param x the x-coordinates of the cell to check
		 * @param y the y-coordinates of the cell to check
		 * @return true if it is, false otherwise
		 */
		bool checkIfCellIsInside(int x, int y);
		Map &_map; /*!< a reference to the map of the ar::Qix */
		int _x; /*!< the x-coordinate of the ar::Flame */
		int _y; /*!< the y-coordinate of the ar::Flame */
		int _prevX; /*!< the previous x-coordinate of the ar::Flame */
		int _prevY; /*!< the previous y-coordinate of the ar::Flame */
		TextureQix _texture; /*!< a stock of the texture, as it switches between 2 different */
	};
}

#endif //CPP_ARCADE_FLAME_HPP
