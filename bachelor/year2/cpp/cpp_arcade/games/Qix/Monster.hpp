/*
** EPITECH PROJECT, 2021
** cpp_arcade
** File description:
** internal functions
*/

/**
 * \file
 * contains the class of the Monster for the ar::Qix game
 */

#ifndef CPP_ARCADE_MONSTER_HPP
# define CPP_ARCADE_MONSTER_HPP

#include <vector>
#include "Map.hpp"
#include "TextureQix.hpp"

namespace ar {
	/**
	 * the class of the Monster for the ar::Qix game
	 */
	class Monster {
	public:
		/**
		 * Spawn a Qix Monster at the center of the Map
		 * @param map A reference to the actual map used
		 */
		explicit Monster(Map &map);
		~Monster() = default;

		/**
		 * Prints the ar::Monster in the ar::Map of the ar::Qix
		 */
		void putMonster();

		/**
		 * called by the ar::Qix in loop to make the Monster move
		 * @return false if the player (or his trail) is hit, true otherwise
		 */
		bool live();

	private:
		/**
		 * contains 1 part of the body of the ar::Monster
		 */
		typedef struct QixBody {
			int x; /*!< x-coordinate of the cell */
			int y; /*!< y-coordinate of the cell */
			TextureQix texture; /*!< texture of this precise part of the Monster */
		} QixBody;

		/**
		 * check if a cell is well inside the map
		 * @param x the x-coordinates of the cell to check
		 * @param y the y-coordinates of the cell to check
		 * @return true if it is, false otherwise
		 */
		bool checkIfCellIsInside(int x, int y);

		/**
		 * moves the whole ar::Monster of (x;y)
		 * @param x the x to appply on each part of the ar::Monster
		 * @param y the y to appply on each part of the ar::Monster
		 */
		void validateMove(int x, int y);

		/**
		 * checks if this cell is the player or his trail
		 * @param x x-coordinate to check
		 * @param y y-coordinate to check
		 * @return true if it is, false otherwise
		 */
		bool hitsPlayer(int x, int y);

		/**
		 * simulate a move to see if it is possible
		 * @param x the x to appply on each part of the ar::Monster
		 * @param y the y to appply on each part of the ar::Monster
		 * @return true if it is, false otherwise
		 */
		bool checkMove(int x, int y);

		/**
		 * return true if the player indicated by pos is on the border or not
		 * @param y y-coordinate of the player
		 * @param x x-coordinate of the player
		 * @return true if it, false if it is not
		 */
		bool checkPlayerOnBorder(int y, int x);
		std::vector<QixBody> _body; /*!< the vector containing every part of the ar::Monster */
		Map &_map; /*!< the reference of the ar::Map of the ar::Qix game */
	};
}
#endif //CPP_ARCADE_MONSTER_HPP
