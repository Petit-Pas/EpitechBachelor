/*
** EPITECH PROJECT, 2021
** cpp_arcade
** File description:
** Created by angevil,
*/

/**
 * \file
 * The file containing the class ar::NCurseDisplay.
 * It inherit from ar::IDisplay.
 */

#ifndef CPP_ARCADE_NCURSEDISPLAY_HPP
# define CPP_ARCADE_NCURSEDISPLAY_HPP

#include <curses.h>
#include <ncurses.h>
#include <menu.h>
#include "IDisplay.hpp"

namespace ar {
	/**
	 * The display class of the ncurses library
	 */
	class NCurseDisplay : public ar::IDisplay {
	public:
		NCurseDisplay();

		~NCurseDisplay() override;
		ar::Event getEvent(int &realKey) override;
		bool canHandleSprites() override;
		void displayGame(const userInterface &UI, Map &map) override;
		void loadResources(const std::map<unsigned char, colorVector> &) override;
		void loadResources(const std::string &filePath, const std::map<unsigned char, spriteCoords> &) override;
		void initMenu(const std::vector<std::string> &menuChoices, const std::string &menuName,
			const std::vector<std::string> &display
		) override;
		int refreshMenu(const ar::Event &, const std::vector<userInterface> &dataArray) override;
		void refreshUsername(std::string &name, int realKey) override;
		void destroyMenu() override;
	private:
		/**
		 * Initialize all the attributes required to display the menu
		 * @param n_choices size of the menuChoices
	 	 * @param menuChoices A double array of char containing all menu choices used
	 	 */
		void initMenuAttr(size_t n_choices, std::vector<std::string> menuChoices);

		/**
		 * Redisplay the menu after a resize ar::Event is catched
		 * @param dataArray A vector of ar::userInterface to display the selected ar::userInterface
		 */
		void resizeMenu(std::vector<userInterface> dataArray);

		/**
		 * Display user information int the menu
		 * @param dataArray A vector of ar::userInterface to display the selected ar::userInterface
		 */
		void displayUI(std::vector<ar::userInterface> dataArray);

		/**
		 * Display the Map with the right Sprite size scaled by the Map size and the window size
		 * @param map Reference to the Map that will be displayed
		 */
		void displayMap(Map &map);

		int _selectedItem; /*!< The selected ar::userInterface in the menu*/
		ITEM **_items; /*!< A vector containing all menu choices used*/
		MENU *_menu;  /*!< A menu created by the libncurses */
		WINDOW *_menuWin; /*!< A subwindow used by the menu created by the libncurses */
		size_t  _nbChoices; /*!< The size of the double array _choices*/
		char **_choices; /*!< A double array containing all menu choices used*/
		std::string _menuName;  /*!< The text containing the menu tile */
		std::vector<std::string> _graphicalLibraries; /*!< A vector containing all the fileName of the loaded graphical library*/
	};
}

#endif //CPP_ARCADE_NCURSEDISPLAY_HPP
