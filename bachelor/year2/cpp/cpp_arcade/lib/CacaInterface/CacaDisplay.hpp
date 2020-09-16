/*
** EPITECH PROJECT, 2021
** cpp_arcade
** File description:
** Created by angevil,
*/

/**
 * \file
 * The file containing the class ar::CacaDisplay.
 * It inherit from ar::IDisplay.
 */

#ifndef CPP_ARCADE_CacaDISPLAY_HPP
# define CPP_ARCADE_CacaDISPLAY_HPP

#include <memory>
#include "Caca.hpp"
#include "IDisplay.hpp"

namespace ar {
	/**
	 * The display class of the caca library
	 */
	class CacaDisplay : public ar::IDisplay {
	public:
		CacaDisplay();
		~CacaDisplay() override;
		ar::Event getEvent(int &realKey) override;
		bool canHandleSprites() override;
		void displayGame(const userInterface &UI, Map &map) override;
		void loadResources(const std::map<unsigned char, colorVector> &) override;
		void loadResources(const std::string &filePath, const std::map<unsigned char, spriteCoords> &
		) override;
		void initMenu(const std::vector<std::string> &menuChoices, const std::string &menuName,
			const std::vector<std::string> &display
		) override;
		int refreshMenu(const ar::Event &, const std::vector<userInterface> &dataArray) override;
		void refreshUsername(std::string &name, int realKey) override;
		void destroyMenu() override;
	private:
		/**
		 * Display user information int the menu
		 * @param dataArray A vector of ar::userInterface to display the selected ar::userInterface
		 */
		void displayUI(std::vector<ar::userInterface> dataArray);

		/**
		 * Change the selected ar::userInterface in the menu
		 * @param key ar::Event that will be process
		 * @param dataArray A vector of ar::userInterface used to delimit the event action
		 */
		void handleMenuInput(ar::Event key, std::vector<userInterface> dataArray);

		/**
		 * Display the Map with the right Sprite size scaled by the Map size and the window size
		 * @param map Reference to the Map that will be displayed
		 */
		void displayMap(Map &map);
		std::unique_ptr<caca::Caca> _caca; /*!< The display window created by the libcaca*/
		std::unique_ptr<caca::Canvas> _canvas; /*!< The canvas displayed in the window created by the libcaca*/
		std::unique_ptr<caca::Event> _event; /*!< The last event received by the window*/
		int _selected; /*!< The selected ar::userInterface in the menu*/
		int _selectedItem;  /*!< The selected choice in the menu*/
		std::vector<std::string> _choices;  /*!< A vector containing all menu choices used*/
		std::string _menuName; /*!< The text containing the menu tile */
		std::map<unsigned char, int16_t> _colors; /*!< A map containing all loaded colors after the call to loadResources()*/
		std::vector<std::string> _graphicalLibraries; /*!< A vector containing all the fileName of the loaded graphical library*/
	};
}

#endif //CPP_ARCADE_CacaDISPLAY_HPP
