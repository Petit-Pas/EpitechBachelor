/*
** EPITECH PROJECT, 2021
** Arcade
** File description:
** SolarFox
*/

#ifndef SOLARFOX_HPP
# define SOLARFOX_HPP

# include <vector>
# include <memory>
# include <Map.hpp>
# include "IGame.hpp"
# include "Arcade.hpp"
# include "Vessel.hpp"
# include "Enemy.hpp"
# include "TextureSolarFox.hpp"

namespace ar {
	/**
	 * main class for the SolarFox game
	 */
	class SolarFox : public IGame {
	public:
		/**
		 * Just a basic struct containing shoots information
		 */
		struct shoots {
			int x; /*!< the x-coordinate */
			int y; /*!< the y-coordinate */
			int to_die; /*!< the n move before die */
			int dir; /*!< shoots direction */
			spriteCoords save; /*!< information of case before move shoots */
		};
		SolarFox();
		~SolarFox() override;

		const std::string getGameName() const override;
		const std::map<unsigned char, spriteCoords> &getSprites() const override;
		const std::map<unsigned char, colorVector> &getColors() const override;
		const std::string getSpritesPath() const override;

		void manageKey(const Event &) override;
		int refreshScore() override;
		int refreshTimer() override;
		bool isGameOver() override;
		void loop() override;

		void setPause() override;
		Map &getMap() override;

	private:
		/**
		 * Create the color Vector that can be asked by the CoreManager if IDisplay::canHandleSprites()  returns false
		 */
		void initColorsVector();
		/**
		 * Create the sprite Vector that can be asked by the CoreManager if IDisplay::canHandleSprites() returns true
 		 */
		void initSpriteVector();
		/**
		 * Fill the map with initial needed values
		 */
		void initMap();
		/**
		 * Fill the map with initial coin
		 */
		void coinMap();
		/**
		 * modify the status of the game paused <--> unpaused
		 * handles the timer too
		 */
		void handlePause();
		int _score; /*!< the score of the current game */
		int _width; /*!< Map width */
		int _height; /*!< Map height */
		Event _direction; /*!< direction Event */
		Map _map; /*!< the map of the game */
		clock_t _step; /*!< the map of the game */
		std::map<unsigned char, ar::spriteCoords> _mapSprites; /*!< the vector of sprites coordinates */
		std::map<unsigned char, colorVector> _mapColors; /*!< the vector of colors */
		std::vector<ar::spriteCoords> _coins; /*!< the vector of coins */
		std::vector<shoots> _shoots; /*!< The vector of shoots */
		bool _gameOver; /*!< true if the game is over, false otherwise */
		bool _isDirectionValidated; /*!< used to avoid multiple directional inputs between 2 frames */
		time_t _start; /*!< timer of the start of the pause, is modified by pause */
		time_t _end; /*!< timer of end of game*/
		time_t _pause; /*!< timer of the start of the pause */
		bool _paused; /*!< true if the game is set to paused */
		Enemy *_enemy[4]; /*!< Array of enemy */
		Vessel *_vessel; /*!< Pointer of the player vessel */
	};
};
#endif //CPP_ARCADE_SOLARFOX_HPP
