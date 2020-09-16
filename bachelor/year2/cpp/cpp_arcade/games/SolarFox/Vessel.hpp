//
// EPITECH PROJECT, 2018
// SolarFox Arcade
// File description:
// Vessel
//

#ifndef VESSEL_HPP
# define VESSEL_HPP

# include "Map.hpp"
# include "Arcade.hpp"
# include "TextureSolarFox.hpp"

namespace ar {
	/**
	 * ar::Vessel class for ar::SolarFox game
	 */
	class Vessel {
	public:
		/**
		 * Just a basic struct containing position, direction and old texture
		 */
		typedef struct pos {
			int posX; /*!< the x-coordinate */
			int posY;/*!< the y-coordinate */
			Event dir; /*!< Direction */
			int old; /*!< the old texture map */
		} pos_t;

		/**
		 * Generate a vessel
		 * @param pos Vessel position and direction
		 * @param width Map max witdth
		 * @param height Map max height
		 * @param map Map pointer
		 */
		Vessel(pos_t pos, int width, int height, Map *map);
		~Vessel() = default;

		/**
		 * The function called by ar::SolarFox to shoot a missil
		 */
		void shoot(Event);
		/**
		 * The function called by ar::SolarFox to move the missil
		 */
		void moveMissil();
		/**
		 * The function called by ar::SolarFox to get the enemy position
		 * @return Enemy position
		 */
		pos_t getPos();
		/**
		 * The function called by ar::SolarFox to get the state of game
		 * @return boolean of the vessel life
		 */
		bool isGameOver();
		/**
		 * The function called by ar::SolarFox to move the vessel
		 * @param _dir
		 */
		void move(Event _dir);
		/**
		 * The function called by ar::SolarFox to get the score
		 * @return _score value
		 */
		int getScore();
	private:
		int _posX; /*!< X Position of the vessel */
		int _maxX; /*!< X max position of the vessel */
		int _posY; /*!< Y Position of the vessel */
		int _maxY; /*!< Y max position of the vessel */
		Event _dir; /*!< Enemy direction */
		bool _shoot; /*!< Boolean of the state of shoot */
		int _missilLife; /*!< Life of a missil */
		pos_t _missil; /*!< Position of the missil */
		int _old; /*!< old map case texture */
		bool _gameOver; /*!< boolean of the vessel life */
		Map *_map; /*!< Pointer to the map of the ar::SolarFox */
		int _score; /*!< Score of the game */
	};
};
#endif // VESSEL_HPP
