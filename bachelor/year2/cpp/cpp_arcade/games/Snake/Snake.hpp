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

namespace ar {
	/**
	 * Main class for the Snake game
	 */
	class Snake : public IGame {
	public:
		/*! This enum references all the possible texture*/
		enum texture {
			EMPTY = 2, /*!< The texture representing a empty area */
			WALL = 3, /*!< The texture representing a wall area */
			FOOD = 4, /*!< The texture representing a food */
			BONUS = 5, /*!< The texture representing a bonus */
			UP_HEAD = 6, /*!< The texture representing an head oriented to the top*/
			RIGHT_HEAD = 7, /*!< The texture representing an head oriented to the right*/
			DOWN_HEAD = 8, /*!< The texture representing an head oriented to the bottom*/
			LEFT_HEAD = 9, /*!< The texture representing an head oriented to the left*/
			BODY_HORIZ = 10, /*!< The texture representing a body oriented horizontally*/
			BODY_VERT = 11, /*!< The texture representing a body oriented vertically*/
			DOWN_TAIL = 12, /*!< The texture representing a tail oriented to the bottom*/
			UP_TAIL = 13,/*!< The texture representing a tail oriented to the top*/
			LEFT_TAIL = 14, /*!< The texture representing a tail oriented to the left*/
			RIGHT_TAIL = 15, /*!< The texture representing a tail oriented to the right*/
			DOWN_RIGHT = 16, /*!< The texture representing a corner*/
			DOWN_LEFT = 17, /*!< The texture representing a corner*/
			UP_RIGHT = 18, /*!< The texture representing a corner*/
			UP_LEFT = 19 /*!< The texture representing a corner*/
		};

		/**
		 * A Simple structure that contains the information about a body cell in the Map
		 */
		typedef struct Body {
			int posX; /*!< The x-coordinates of the body piece */
			int posY; /*!< The y-coordinates of the body piece */
			int span; /*!< How many ticks this body will remain*/
			ar::Event direction; /*!< The body orientation */
		} Body;

		Snake();
		~Snake();
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
		/**
		 * Spawn a bonus randomly in the Map
		 */
		void manageBonus();

		/**
		* Move the snake depending of the direction
		*/
		void refreshSnake();

		/**
		 * Get the right direction with the first set of keys
		 * @param event Asked direction
		 */
		void askedDirection(Event event);

		/**
		 * Initialize the colors vector
		 */
		void initColorsVector();

		/**
		 * Initialize the sprites vector
		 */
		void initSpriteVector();

		/**
		 * Initialize the snake and put it in the map center
		 */
		void initSnake();

		/**
		 * Fill the Map with the desired Snake Map
		 */
		void initMap();

		/**
		 * Handle pause and calculate the time in pause to set the right timer
		 */
		void handlePause();

		/**
		 * Move the snake's head
		 */
		void moveSnake();

		/**
		 * Check if their is something to eat where the snake is headed
		 */
		void checkEat();

		/**
		 * Spawn a food randomly on the map
		 */
		void spawnFood();

		/**
		 * Spawn a bonus randomly on the map
		 */
		void spawnBonus();

		/**
		 * Set the corner to the right orientation
		 */
		void putCorner();

		/**
		 * Check which corner should be put
		 * @param it The iterator in the snake Body
		 * @param a The possible direction of the iterator -1
		 * @param b The possible direction of the iterator
		 * @param c The possible direction of the iterator + 1
		 * @return true if the directions match the snake, false otherwise
		 */
		bool checkCorner(std::vector<struct Body>::iterator &it, ar::Event a, ar::Event b, ar::Event c);

		/**
		 * Do all checks by calling checkCorner().
		 * @param it The iterator in the snake Body
		 */
		void checkCorners(std::vector<struct Body>::iterator it);

		int _score; /*!< The score of the current game */
		Event _direction; /*!< the actual direction (set by IGame::manageKey()) */
		Map _map; /*!< The map of the game */
		clock_t _step; /*!< For timer calculations */
		std::map<unsigned char, ar::spriteCoords> _mapSprites; /*!< The vector of sprites coordinates */
		std::map<unsigned char, colorVector> _mapColors; /*!< The vector of colors */
		int _posX; /*!< The x-coordinates of the player */
		int _posY; /*!< The y-coordinates of the player */
		bool _gameOver; /*!< true if the game is over, false otherwise */
		int _length; /*!< The length of the snake*/
		std::vector<Body> _body; /*!< The snake Body*/
		bool _isDirectionValidated; /*!< Used to avoid multiple directional inputs between 2 frames */
		Body _bonus; /*!< The bonus that spawn randomly*/
		bool _askedRules; /*!< If true the direction are drunk (default: true) \n Undrunk it by pressing Space \n (Thanks Epitech)*/
		time_t _start; /*!< Timer of the start of the pause, is modified by pause */
		time_t _end; /*!< Timer of end of game*/
		time_t _pause; /*!< Timer of the start of the pause */
		bool _paused; /*!< true if the game is set to paused */
	};
};
#endif //CPP_ARCADE_SNAKE_HPP
