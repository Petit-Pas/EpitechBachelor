/*
** EPITECH PROJECT, 2021
** cpp_arcade
** File description:
** Created by angevil,
*/

#ifndef CPP_ARCADE_SNAKE_HPP
# define CPP_ARCADE_SNAKE_HPP

#include <vector>
#include <memory>
#include "Map.hpp"
#include "IGame.hpp"
#include "Arcade.hpp"
#include "Bomb.hpp"
#include "Mob.hpp"

namespace ar {
	/**
	 * Main class for the Snake game
	 */
	class Bomberman : public IGame {
	public:

		Bomberman();
		~Bomberman();

		const std::string getGameName() const override;
		const std::map<unsigned char, spriteCoords> &getSprites() const override;
		const std::map<unsigned char, colorVector> &getColors() const override;
		const std::string getSpritesPath() const override;
		void manageKey(const Event &) override;
		int refreshScore() override;
		int refreshTimer() override;
		bool isGameOver() override;
		void loop() override;
		Map &getMap() override;
		void setPause() override;

	private:

		void spawnBonus(int x, int y);
		void refreshExplosions();
		void addExplosion(std::vector<explosionT> explosion);

		void spawnBomb();

		void refreshBombs();

		/**
		* Move the Bomberman depending of the direction
		*/
		void refreshBomberman();

		/**
		 * Initialize the colors vector
		 */
		void initColorsVector();

		/**
		 * Initialize the sprites vector
		 */
		void initSpriteVector();

		/**
		 * Initialize the Bomberman and put it in the map center
		 */
		void initBomberman();

		/**
		 * Fill the Map with the desired Bomberman Map
		 */
		void initMap();

		/**
		 * Handle pause and calculate the time in pause to set the right timer
		 */
		void handlePause();

		/**
		 * Move the Bomberman's head
		 */
		void moveBomberman();

		void removeExplosions();

		void checkDeath();
		void initMobs();
		void refreshMobs();
		void checkWin();
		void updateDirection();

		int _score; /*!< The score of the current game */
		Event _direction; /*!< the actual direction (set by IGame::manageKey()) */
		textureBomberman _player;
		Map _map; /*!< The map of the game */
		clock_t _step; /*!< For timer calculations */
		std::map<unsigned char, ar::spriteCoords> _mapSprites; /*!< The vector of sprites coordinates */
		std::map<unsigned char, colorVector> _mapColors; /*!< The vector of colors */
		int _posX; /*!< The x-coordinates of the player */
		int _posY; /*!< The y-coordinates of the player */
		bool _gameOver; /*!< true if the game is over, false otherwise */
		time_t _start; /*!< Timer of the start of the pause, is modified by pause */
		time_t _end; /*!< Timer of end of game*/
		time_t _pause; /*!< Timer of the start of the pause */
		bool _paused; /*!< true if the game is set to paused */
		int _powerBombs;
		int _spanBombs;
		int _amountBombs;
		std::vector<Bomb> _bombs;
		std::vector<explosionT> _explosedAreas;
		std::vector<Mob> _mobs;

	};
};
#endif //CPP_ARCADE_Bomberman_HPP
