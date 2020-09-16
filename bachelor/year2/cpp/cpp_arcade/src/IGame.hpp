/*
** EPITECH PROJECT, 2021
** cpp_arcade
** File description:
** Created by angevil,
*/

/**
 * \file
 * The file containing the abstract class ar::IGame.
 * Every game should inherit from it and override every pure method.
 */

#ifndef CPP_ARCADE_IGAME_HPP
# define CPP_ARCADE_IGAME_HPP

#include <map>
#include "Arcade.hpp"
#include "Map.hpp"

namespace ar {
	/**
	 * Every game should inherit from it and override every pure method.
	 */
	class IGame {
	public:
		IGame() = default;

		virtual ~IGame() = default;

		/**
		 * Modifies the state of the game by managing the Event sent.
		 * @param key Event received with IDisplay::getEvent().
		 * @return void
		 */
		virtual void manageKey(const Event &key) = 0;

		/**
		 * Is used if IDisplay::canHandleSprites() returned true.
		 * The char is the number stored in the map, the spriteCoords describes the sprite that should be print when finding 'char' in the map.
		 * @return the vector of sprites to send to IDisplay::initSprites().
		 */
		virtual const std::map<unsigned char, spriteCoords> &getSprites() const = 0; //dans games, à l'initialisation

		/**
		 * Is used if IDisplay::canHandleSprites() returned true.
		 * @return the path to the spriteSheet
		 */
		virtual const std::string getSpritesPath() const = 0;

		/**
		 * Is used if IDisplay::canHandleSprites() returned true.
		 * The char is the number stored in the map, the colorVector describes the RGB code that should be print when finding 'char' in the map.
		 * @return the vector of colors to set via initColors in the graphical interface.
		 */
		virtual const std::map<unsigned char, colorVector> &getColors() const = 0; //dans games, à l'initialisation

		/**
		 * Should be called after each call of IGame::manageKey() to refresh the score in the ar::userInterface of the game.
		 * @return the actual score of the game
		 */
		virtual int refreshScore() = 0;

		/**
		 * Should be called after each call of IGame::manageKey() to refresh the timer in the ar::userInterface of the game.
		 * @return the actual timer of the game
		 */
		virtual int refreshTimer() = 0;

		/**
		 * Check the status of the game.
		 * Should be called after each call of IGame::manageKey()
		 * @return true if the game is over, false otherwise
		 */
		virtual bool isGameOver() = 0;

		/**
		 * Should be called after each call of IGame::manageKey() to send it to IDisplay::displayGame()
		 * @return the updated map of the game
		 */
		virtual Map &getMap() = 0;

		/**
		 * This is the main function for every game, it will be called in a loop by the core Manager.
		 * It should include a timer to know wether or not it should update the game
		 * @return void
		 */
		virtual void loop() = 0;

		/**
		 * Used to init the main Menu correctly, as it needs to receive an std::vector<std::string> with the name of every game in IDisplay::initMenu().
		 * @return A string containing the name of the game.
		 */
		virtual const std::string getGameName() const = 0;

		/**
		 * Forces the pause in the game, if it was already in Pause, does nothing.
		 * \warning A game should always be set to pause when created.
		 * @return void
		 */
		virtual void setPause() = 0;
	};

	/**
	 * The typedef for the extern "C" function needed in every Game to create a new instance of it.
	 * @warning This function must be implemented in order to load the library
	 */
	typedef ar::IGame *createGame();

	/**
	 * The typedef for the extern "C" function needed in every Game destroy an instance of it.
	 * @warning This function must be implemented in order to load the library
	 */
	typedef void destroyGame(ar::IGame *);
};

#endif //CPP_ARCADE_IGAME_HPP
