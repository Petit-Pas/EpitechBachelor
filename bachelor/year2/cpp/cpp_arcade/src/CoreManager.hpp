/*
** EPITECH PROJECT, 2021
** cpp_arcade
** File description:
** Created by angevil,
*/

/**
 * \file
 * Contains the main Class of the arcade project
 */

#ifndef CPP_ARCADE_COREMANAGER_HPP
# define CPP_ARCADE_COREMANAGER_HPP

#include "IGame.hpp"
#include "IDisplay.hpp"
#include <vector>

namespace ar {
	/**
	 * Main class of the arcade project
	 */
	class CoreManager {
	public:
		CoreManager();
		~CoreManager() = default;

		/**
		 * Initializes the menus and contains the main loop of the program.
		 * @return void
		 */
		void menu();

		/**
		 * The loop that load colors / sprites then loop, calling IDisplay::getEvent(),
		 * IGame::manageKey() IGame::refreshTimer() and IGame::refreshScore()
		 * @return ar::GAME_OVER if the game is over, informations for the core otherwise (ar::MENU, ar::NEXT_GAME, etc...)
		 */
		ar::Event game();

		/**
		 * The loop to load all symbols of games.
		 * @param names the names of every .so
		 * @return void
		 */
		void loadAllGames(std::vector<std::string> names);

		/**
		 * The function that loads every symbol of a game.so.
		 * @param it an iterator pointing to the name of the .so to load
		 * @param i counts the amount of games that could be loaded correctly
		 * @return void
		 */
		void dlGames(std::vector<std::string>::iterator &it, int &i);

		/**
		 * Frees resources of every loaded game.so.
		 * @return void
		 */
		void unloadAllGames();

		/**
		 * The loop to load all symbols of graphic interface.
		 * @param names the names of every .so
		 * @return void
		 */
		void loadAllDisplay(std::vector<std::string> names);

		/**
		 * The function that loads every symbol of a graphicalInterface.so.
		 * @param it an iterator pointing to the name of the .so to load
		 * @param i counts the amount of graphical interface that could be loaded correctly
		 * @param names the vector containing the name of the .so to load
		 * @return void
		*/
		void dlDisplay(std::vector<std::string>::iterator &it, int &i, const std::vector<std::string> &names);

		/**
		 * Frees resources of every loaded graphicalInterface.so.
		 * @return void
		 */
		void unloadAllDisplay();

		/**
		 * Unload the current (indexed by _displayID) instance of graphical interface.
		 * @return void
		 */
		void unloadCurrentDisplay();

		/**
		 * Load the current (indexed by _displayID) instance of graphical interface.
		 * @return void
		 */
		void loadCurrentDisplay();

		/**
		 * modifies the "current" graphicalInterface
		 * @param displayID will be set in _displayID
		 * @return void
		 */
		void setDisplayID(int displayID);

		/**
		 * Destroys the instance of the current game (indexed by _gameID) and create a new one
		 * @return void
		 */
		void restartCurrentGame();

		/**
		 * The main loop for the gameOver menu, it is also the function that launches the game by calling IGame::loop()
		 * As both gameover and main menu are used the same way, we need to provide a std::vector<userInterface> to IDisplay::initMenu()
		 * It is here provided with multiple copy of the same interface (corresponding to the current Game)
		 * @param UIs the userInterface to print in the menu
		 * @return AR_EXIT or AR_MENU
		 */
		ar::Event gameOverMenu(std::vector<userInterface> &UIs);

		/**
		 * The loop for the main menu
		 * @param UIs the std::vector<userInterface> needed in IDisplay::refreshMenu()
		 * @param menuChoices the std::vector<std::string> needed in IDisplay::initMenu()
		 * @return AR_EXIT or AR_VALIDATE
		 */
		ar::Event mainMenu(std::vector<userInterface> &UIs, std::vector<std::string> menuChoices);

		/**
		 * Load the graphical interface (indexed by _displayID + 1) then reload the menu
		 * @param choices the std::vector<std::string> needed in IDisplay::initMenu()
		 * @param title the std::string needed in IDisplay::initMenu()
		 * @param UI the std::vector<userInterface> needed in IDisplay::refreshMenu()
		 * @return void
		 */
		void loadNextGraphMenu(const std::vector<std::string> &choices,
			std::string title, const std::vector<userInterface> &UI);

		/**
		 * Load the graphical interface (indexed by _displayID - 1) then reload the menu
		 * @param choices the std::vector<std::string> needed in IDisplay::initMenu()
		 * @param title the std::string needed in IDisplay::initMenu()
		 * @param UI the std::vector<userInterface> needed in IDisplay::refreshMenu()
		 * @return void
		 */
		void loadPrevGraphMenu(const std::vector<std::string> &choices,
			std::string title, const std::vector<userInterface> &UI);

		/**
		 * The loop for the game over menu.
		 * @param GameOverUI the std::vector<userInterface> needed in IDisplay::refreshMenu()
		 * @param gameOverChoices the std::vector<std::string> needed in IDisplay::initMenu()
		 * @param id the id of the choice seleceted in the menu
		 * @return AR_EXIT, AR_MENU or AR_UNKNOWN
		 */
		ar::Event loopMenuGameOver(const std::vector<userInterface> &GameOverUI,
			const std::vector<std::string> &gameOverChoices, int &id);

		/**
		 * refresh every name in the vector of userInterface to have the same eveywhere
		 * @param UIs std::vector<userInterface> needed in IDisplay::refreshMenu()
		 * @return void
		 */
		void refreshNames(std::vector<userInterface> &UIs);

		/**
		 * The loop that calls the function launching game.
		 * The changes of lib and games while playing are managed thanks to this method.
		 * @return AR_EXIT or AR_MENU
		 */
		ar::Event selectGameAndDisplay();

		/**
		 * The structure that contains the handler and functions get by dlopen for the graphical interface.
		 */
		typedef struct displayHdl {
			std::string fileName; /*!< The name of the file sent to dlopen() */
			void *displayHandler; /*!< The handler by dlopen */
			ar::createDisplay *displayConstructor /*!< The constructor by dlsym */;
			ar::destroyDisplay *displayDestructor /*!< The destructor by dlsym */;;
		} displayHdl;

		/**
		 * The structure that contains the handler and functions get by dlopen for the games.
		 */
		typedef struct gameHdl {
			std::string fileName; /*!< The name of the file sent to dlopen() */
			void *gameHandler; /*!< The handler by dlopen() */
			ar::createGame *gameConstructor; /*!< The constructor by dlsym() */;
			ar::destroyGame *gameDestructor; /*!< The destructor by dlsym() */;
			ar::IGame *gameInterface; /*!< The instance of the class */
			ar::userInterface UI; /*!< The userInterface linked to the game */
		} gameHdl;

	private:
		ar::IDisplay *_graphicInterface; /*!< The instance of the current display interface */
		std::map<int, gameHdl *> _games; /*!< The vector containing every loaded game */
		std::map<int, displayHdl *> _displays; /*!< The vector containing the handlers and constructors/destructors of the graphical interfaces loaded */
		int _displayID; /*!< The index of the current graphical Interface */
		int _gameID; /*!< The index of the current game */
	};
};

#endif //CPP_ARCADE_COREMANAGER_HPP
