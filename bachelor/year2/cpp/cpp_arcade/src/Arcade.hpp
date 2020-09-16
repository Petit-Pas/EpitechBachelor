/*
** EPITECH PROJECT, 2021
** cpp_arcade
** File description:
** Created by angevil,
*/

/**
 * \file
 * contains the namespace 'ar' used everywhere
 */

#ifndef CPP_ARCADE_ARCADE_HPP
# define CPP_ARCADE_ARCADE_HPP

#include <string>

/*! \mainpage Arcade Documentation
 *
 * \section intro_sec Introduction
 *
 * Arcade is a gaming platform: a program that lets the user choose a game to play and keeps a register of player scores.\n
 * To be able to deal with the elements of your gaming plateform at run-time, your graphic libraries and your games must be implemented as dynamic libraries, loaded at runtime.\n
 * Each GUI available for the program must be used as a shared library that will be loaded and used dynamically by the main program.\n
 * See the subject at : http://shintaro.ovh/arcade_sujet.pdf
 *
 * \section install_sec Installation
 *
 * \subsection tools_subsec Tools required
 * - Clang (see at : https://clang.llvm.org/)
 * - Library SFML (see at : https://www.sfml-dev.org/documentation/2.4.2/)
 * - Library Caca (see at : http://caca.zoy.org/wiki/libcaca)
 * - Library Ncurses (see at : https://invisible-island.net/ncurses/)
 *
 * \subsection running Running the program
 * In a command window, at the root of the repository type : "make", in order to compile the arcade executable \n
 * Then in order to launch the program, just type "./arcade" and as argument give it an dynamic library compatible \n
 * Example :
 * 	- ./arcade ./lib/lib_arcade_caca.so
 * 	- ./arcade ./lib/lib_arcade_sfml.so
 * 	- ./arcade ./lib/lib_arcade_ncurses.so
 * 	- ./arcade ./lib/lib_arcade_unity.so
 */

/**
 * the namespace used for every asset of the project, contains Abstract classes, classes inherited from those, minor classes for games and enumeration of event
 */
namespace ar {
	/*! This enum references all the possible events returned by IDisplay::getEvent(). \n
	 * Can be split into 2 categories:
	 * 	- Those that are managed by the Core (Switch libs, games and so on...)
	 * 	- Those that are managed by IGame::manageKey()*/
	enum Event {
		AR_UP, /*!< Up key is pressed */
		AR_DOWN, /*!< Down key is pressed */
		AR_LEFT, /*!< Left key is pressed */
		AR_RIGHT, /*!< Right key is pressed */
		AR_PREV_GRAPH_LIB, /*!< Next Graphical library key is pressed */
		AR_NEXT_GRAPH_LIB, /*!< Previous Graphical library key is pressed */
		AR_PREV_GAME, /*!< Previous Game key is pressed */
		AR_NEXT_GAME, /*!< Next Game key is pressed */
		AR_RESTART, /*!< Restart key is pressed */
		AR_MENU, /*!< Menu key is pressed */
		AR_EXIT, /*!< Exit key is pressed */
		AR_ACTION, /*!< Action key is pressed */
		AR_PAUSE, /*!< Pause key is pressed */
		AR_VALIDATE, /*!< Validate key is pressed */
		AR_RESIZE, /*!< Window has been resized */
		AR_GAME_OVER, /*!< The game is over*/
		AR_UNKNOWN /*!< No recognize event */
	};

	/*! This structure stocks all users informations for every games
	 * Sent to IDisplay::displayGame() to display it while the game is running
	 * Sent to IDisplay::refreshMenu() to display it in the menu*/
	typedef struct userInterface {
		int score; /*!< User score on the actual game, updated with IGame::refreshScore() */
		std::string username; /*!< Username, updated with IDisplay::refreshUsername() */
		int time; /*!< Timer on the actual game, updated with IGame::refreshTimer() */
	} userInterface;


	/*! This structure stocks RGB color codes.
	 * Get it from IGame::getColors()
	 * Send it to IDisplay::setColors()*/
	typedef struct colorVector {
		unsigned char red; /*!< Red color code between 0 and 255 */
		unsigned char green; /*!< Green color code 0 and 255 */
		unsigned char blue; /*!< Blue color code 0 and 255 */
	} colorVector;

	/*! This structure stocks position and size of a sprite
	 * Used to get sprites in IGame::getSprites
	 * Used to load sprites in IDisplay::setSprites*/
	typedef struct spriteCoords {
		int x; /*!< x of the top left corner position */
		int y; /*!< y of the top left corner position */
		int width; /*!< width of the sprite*/
		int height; /*!< height of the sprite*/
	} spriteCoords;
};

#endif //CPP_ARCADE_ARCADE_HPP
