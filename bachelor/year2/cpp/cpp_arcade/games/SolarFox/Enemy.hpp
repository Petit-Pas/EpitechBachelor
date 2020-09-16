/*
** EPITECH PROJECT, 2018
** SolarFox Arcade
** File description:
** Enemy
*/

/**
 * \file
 * contains the ar::Enemy class for the ar::SolarFox game
 */

#ifndef ENEMY_HPP
# define ENEMY_HPP

# include "Map.hpp"
# include "Arcade.hpp"
# include "TextureSolarFox.hpp"

namespace ar {
	/**
	 * ar::Enemy class for ar::SolarFox game
	 */
	class Enemy {
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
		 * Generate an enemy
		 * @param pos Enemy position and direction
		 * @param max Maximal position of the enemy
		 * @param map Map pointer
		 * @param text Enemy texture
		 */
		Enemy(pos_t pos, int max, Map *map, int text);
		~Enemy() = default;

		/**
		 * The function called by ar::SolarFox to move the Enemy
		 */
		void move();
		/**
		 * The function called by ar::SolarFox to get the enemy position
		 * @return Enemy position
		 */
		pos_t getPos();
		/**
		 * The function called by ar::SolarFox to move the Enemy shoot
		 */
		void moveShoot();
	private:
		/**
		 * The function called by ar::Enemy to shoot a missil
		 */
		void shoot();
		int _posX; /*!< X Position of the enemy */
		int _posY; /*!< Y Position of the enemy */
		int _max; /*!< Enemy position maximal */
		Event _dir; /*!< Enemy direction */
		Map *_map; /*!< Pointer to the map of the ar::SolarFox */
		int _old; /*!< old map case texture */
		int _texture; /*!< Texture of the enemy */
		bool _shoot; /*!< Boolean of the state of shoot */
		pos_t _missil; /*!< Position of the missil */
	};
};
#endif // ENEMY_HPP
