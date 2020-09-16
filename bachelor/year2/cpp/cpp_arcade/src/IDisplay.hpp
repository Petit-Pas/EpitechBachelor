/*
** EPITECH PROJECT, 2021
** cpp_arcade
** File description:
** Created by angevil,
*/

/**
 * \file
 * The file containing the abstract class ar::IDisplay.
 * Every display should inherit from it and override every pure method.
 */

#ifndef CPP_ARCADE_IDISPLAY_HPP
# define CPP_ARCADE_IDISPLAY_HPP

#include <map>
#include <vector>
#include "Arcade.hpp"
#include "Map.hpp"

namespace ar {
	/**
	 * Every display should inherit from it and override every pure method.
	 */
	class IDisplay {
	public:
		virtual ~IDisplay() = default;

		/**
		 * Get event happening in the display
		 * @param realEvent Is set to the code of the event from the actual graphical library. \n
		 *	Used in IDisplay::refreshUsername() to refresh the username in the main menu
		 * @return The key from the enum ar::Event found \n
		 * 	Sent to IGame::manageKey() in order to handle the keys event. \n
		 * 	If IGame::manageKey() doesn't recognize the key the CoreManager handles it.
		 */
		virtual ar::Event getEvent(int &realEvent) = 0;

		/**
		 * To check if the graphic library handles sprites
		 * @return true If this Graphic interface handles Sprites, false otherwise
		 */
		virtual bool canHandleSprites() = 0;

		/**
		 * Main function to display the game
		 * @param UI The ar::userInterface matching with the game, contains informations to be displayed such as score and timer
		 * @param map The Map used as a double array representing the map to be displayed,\n
		 * should be filled with recognizable characters (set in IDisplay::loadResources or IDisplay::loadResources)
		 */
		virtual void displayGame(const userInterface &UI, Map &map) = 0;

		/**
		 * Used when the library can't handle sprites at initialization (always before displayGame())
		 * @param colors Should contain 1 colorVector for each possible unsigned char in the game map \n example:
		 * 	- 2 -> 255,0,0
		 * 	- 3 -> 0,255,0  etc..
		 * 	\warning  0 and 1 are reserved for black and white, they should be set by default in the graphic libraries DO NOT USE.
		 */
		virtual void loadResources(const std::map<unsigned char, colorVector> &colors) = 0;

		/**
		 * Used when the library can handle sprites at initialization (always before IDisplay::displayGame())
		 * @param filePath The path to your spritesSheet
		 * @param sprites Should contain an ar::spriteCoords for each possible unsigned char in the game map \n
		 * 	    \warning 0 AND 1 are reserved for black and white, they should be set by default in the graphic libraries DO NOT USE \n
		 * 	    		2 is the default texture, the one what will be print on every cell BEFORE printing the real sprite
		 */
		virtual void loadResources(const std::string &filePath,
			const std::map<unsigned char, spriteCoords> &sprites
		) = 0;

		/**
		 * Initialize a menu in the interface
		 * @param menuChoices Every choice on your menu including an exit choice
		 * @param menuName The menu title
		 * @param display A vector containing all the fileName of the loaded graphical library
		*/
		virtual void initMenu(const std::vector<std::string> &menuChoices, const std::string &menuName,
			const std::vector<std::string> &display
		) = 0;

		/**
		 * Refreshes the display of the menu
		 * @param key The last key pressed (should handle only Event::AR_UP, Event::AR_DOWN and AR_VALIDATE from ar::Event)
		 * @param dataArray All interface to be displayed, dataArray.at(0) should be displayed when the menu is on the first row, etc
	 	 * \warning The size of dataArray must be the size of the menuChoices (set in IDisplay::initMenu()) minus 1
		 * @return The cell on which the menu points after the input
		 */
		virtual int refreshMenu(const ar::Event &key, const std::vector<userInterface> &dataArray) = 0;

		/**
		 * Should update a string with the left realKey
		 * @param name The string in which you store the username
		 * @param realKey Set by IDisplay::getEvent()
		 */
		virtual void refreshUsername(std::string &name, int realKey) = 0;

		/**
		 * Destroy Menu ressources, should be called between 2 IDisplay::initMenu()
		 */
		virtual void destroyMenu() = 0;
	};

	/**
	 * The typedef for the extern "C" function needed in every Display to create a new instance of it.
	 * @warning This function must be implemented in order to load the library
	 */
	typedef ar::IDisplay *createDisplay();

	/**
	 * The typedef for the extern "C" function needed in every DIsplay destroy an instance of it.
	 * @warning This function must be implemented in order to load the library
	 */
	typedef void destroyDisplay(ar::IDisplay *);
};

#endif //CPP_ARCADE_IDISPLAY_HPP
