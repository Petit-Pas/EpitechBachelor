/*
** EPITECH PROJECT, 2021
** cpp_arcade
** File description:
** internal functions
*/

/**
 * \file
 * contains the ar::Spark class for the ar::Qix game
 */

#ifndef CPP_ARCADE_SPARK_HPP
# define CPP_ARCADE_SPARK_HPP

#include <vector>
#include <Map.hpp>
#include "TextureQix.hpp"

namespace ar {
	/**
	 * the ar::Spark class for the ar::Qix game
	 */
	class Spark {
	public:
		/**
		 * constructor of the spark
		 * @param map map of the game
		 * @param posX the x-coordinate of the flame
		 * @param posY the y-coordinate of the flame
		 * @param oldX the x-coordinate of the theorical previous position
		 * @param oldY the y-coordinate of the theorical previous position
		 */
		Spark(Map &map, int posX, int posY, int oldX, int oldY);
		~Spark();

		/**
		 * call this to make the ar::Spark move
		 */
		void live();

	private:
		/**
		 * just a basic struct for coordinates
		 */
		typedef struct coordSpark {
			int x; /*!< x-coordinate */
			int y; /*!< y-coordinate */
		} coordSpark;

		/**
		 * fill an array of ar::TextureQix with the surrounding values
		 * @param around the array to fill
		 */
		void getSurroundingContent(ar::TextureQix *around);

		/**
		 * checks if the ar::Spark can go anywhere on BORDER or PLAYER
		 * @param around the surrounding content
		 * @return true if it could, false otherwise
		 */
		bool checkHighPriorityMove(ar::TextureQix *around);

		/**
		 * Do the first possible move.
		 * @param around The surrounding content.
		 */
		void doLowPriorityMove(ar::TextureQix *around);

		/**
		 * count the amount of possibilities around
		 * @param around The surrounding content.
		 * @return this amount
		 */
		int countPossibleWays(ar::TextureQix *around);

		/**
		 * moves the Spark and update the pos
		 * @param addonX to add to _x
		 * @param addonY to add to _y
		 */
		void validateNewPos(int addonX, int addonY);

		/**
		 * validate the first possible move
		 * @param around The surrounding content.
		 */
		void validateFirstWay(ar::TextureQix *around);

		/**
		 * do a pathfinding to find the nearest border
		 * @param around The surrounding content.
		 */
		void pathfindToBorder(ar::TextureQix *around);

		/**
		 * recursively find the nearest border
		 * @param oldSet a vector containing only the starting coordinates (for loop purpose)
		 * @return the coordinates of the nearest border
		 */
		coordSpark findClosestBorder(std::vector<coordSpark> &oldSet);

		/**
		 * check if a cell is well inside the map
		 * @param x the x-coordinates of the cell to check
 		 * @param y the y-coordinates of the cell to check
 		 * @return true if it is, false otherwise
 		 */
		bool checkIfCellIsInside(int x, int y);

		/**
		 * add a coordSpark in a vector
		 * @param x x-coordinate of the cell to add
		 * @param y y-coordinate of the cell to add
		 * @param depth depth of the cell (as the search in depth first)
		 * @param toFill the vector to fill
		 */
		void pushCell(int x, int y, int depth, std::vector<coordSpark> &toFill);

		/**
		 * as the pathfind modifies the map, this function is needed to clean it afterwards
		 */
		void erasePathfind();

		/**
		 * dumps the map, for debugging purpose
		 */
		void dump();

		/**
		 * use the pathfind to find which way to go
		 * @param closest the closest border from the pos of the ar::Spark
		 */
		void goBack(coordSpark closest);
		int _x; /*!< the x-coordinate of the ar::Spark */
		int _y; /*!< the y-coordinate of the ar::Spark */
		int _prevY; /*!< the previous x-coordinate of the ar::Spark */
		int _prevX; /*!< the previous y-coordinate of the ar::Spark */
		Map &_map; /*!< the reference to the ar::Map of the ar::Qix game */
	};
}
#endif //CPP_ARCADE_SPARK_HPP
