/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Internal functions
*/

#ifndef CPP_ARCADE_MAP_HPP
# define CPP_ARCADE_MAP_HPP

/**
 * \file
 * The file containing the class ar::Map.
 * It is used in every Display and Game Interface
 */

namespace ar {
	/**
	 * The Map class
	 * Containing a double array of int
	 */
	class Map {
	public:
		~Map();
		/**
		 * Initialize a map of size _height*_width and fill it with zeros
		 * @param _height The height of the map
		 * @param _width The width of the map
		 */
		Map(int _height, int _width);

		/**
		 * @return The height of the map
		 */
		int getHeight() const;

		/**
		 * @return The width of the map
		 */
		int getWidth() const;

		/**
		 * @return the x-coordinate of the player
		 */
		int getPlayerX() const;

		/**
		 * @return the y-coordinate of the player
		 */
		int getPlayerY() const;

		/**
		 * @param x _playerPosX will be set to x
		 */
		void setPlayerX(int x);

		/**
		 * @param y _playerPosY will be set to y
		 */
		void setPlayerY(int y);

		/**
		 * An overload of the [] operator to use the map as an array
		 * @param x The index of the returned line
		 * @return The line at index x
		 */
		int *&operator[](int x);
	private:
		int **_map; /*!< The double array of int used in the Map */
		int _height; /*!< The height of the map */
		int _width; /*!< The width of the map */
		int _playerPosX; /*!< the x-coordinate of the player, set in the Games and may be used in Display Interface */
		int _playerPosY; /*!< the y-coordinate of the player, set in the Games and may be used in Display Interface */
	};
}

#endif //CPP_ARCADE_MAP_HPP
