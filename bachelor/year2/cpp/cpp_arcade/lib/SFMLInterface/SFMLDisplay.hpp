/*
** EPITECH PROJECT, 2021
** cpp_arcade
** File description:
** Created by angevil,
*/

#ifndef CPP_ARCADE_SFMLDisplay_HPP
# define CPP_ARCADE_SFMLDisplay_HPP

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "IDisplay.hpp"


/**
 * \file
 * The file containing the class ar::SFMLDisplay.
 * It inherit from ar::IDisplay.
 */

namespace ar {
	/**
	 * The display class of the SFML library
	 */
	class SFMLDisplay : public ar::IDisplay {
	public:
		SFMLDisplay();
		~SFMLDisplay() override;
		ar::Event getEvent(int &realKey) override;
		bool canHandleSprites() override;
		void displayGame(const userInterface &UI, Map &map) override;
		void loadResources(const std::map<unsigned char, colorVector> &) override;
		void loadResources(const std::string &filePath, const std::map<unsigned char, spriteCoords> &) override;
		void initMenu(const std::vector<std::string> &menuChoices, const std::string &menuName,
			const std::vector<std::string> &display
		) override;
		int refreshMenu(const ar::Event &key, const std::vector<userInterface> &dataArray) override;
		void refreshUsername(std::string &name, int realKey) override;
		void destroyMenu() override;

		/**
		 * A basic structure used to define and draw a sprite in the SFML window
		 */
		typedef struct Sprite {
			ar::spriteCoords coords; /*!< The information required to load the sprite from the sprite sheet */
			sf::Texture texture; /*!< The texture loaded from the sprite sheet */
			sf::Sprite sprite; /*!< The sprite containing the texture that will be displayed */
		} Sprite;
	private:
		/**
		 * Display the Map with the right Sprite size scaled by the Map size and the window size
		 * @param map Reference to the Map that will be displayed
		 * @param pixelSize Size of a sprite
		 * @param pixelFactor Factor used to calculate the sprite size thanks to the Map size and the window size
		 */
		void displayMap(Map &map, int pixelSize, float pixelFactor);

		/**
		 * Set the scale, the position of the Sprite in the sprite sheet
		 * @param sprite Sprite index
		 * @param pixelFactor Factor used to calculate the sprite size thanks to the Map size and the window size
		 */
		void setSpriteAttr(int sprite, float pixelFactor);

		/**
		 * Change the selected ar::userInterface in the menu
		 * @param key ar::Event that will be process
		 * @param dataArray A vector of ar::userInterface used to delimit the event action
		 */
		void handleMenuInput(ar::Event key, std::vector<ar::userInterface> dataArray);

		/**
		 * Calculate a factor in order to scale the sprite to always fit the windows
		 * @param map Map used to calculate a factor from the default map size
		 * @return The factor calculated
		 */
		float getPixelFactorMap(Map &map);

		/**
		 * Calculate a factor in order to scale the text to always fit the windows
		 * @return The factor calculated
		 */
		float getPixelFactor();

		/*!
		 * This structure contains all the information required in order for a SFML sprite to work
		 */
		sf::RenderWindow _window; /*!< The SFML window used to display */
		sf::Font _font; /*!< The font used in all the text displayed */
		sf::Text _username; /*!< The text containing the user name */
		sf::Text _time;  /*!< The text containing the user game timer of the actual game */
		sf::Text _score;  /*!< The text containing the user score of the actual game */
		int _selected; /*!< The selected ar::userInterface in the menu*/
		int _selectedItem;  /*!< The selected choice in the menu*/
		std::vector<sf::Text> _choices;  /*!< A vector containing all menu choices used*/
		sf::Text _menuName; /*!< The text containing the menu tile */
		std::map<unsigned char, ar::SFMLDisplay::Sprite> _sprites; /*!< A map containing all loaded sprite after the call to loadResources()*/
		std::vector<sf::Text> _graphicalLibraries; /*!< A vector containing all the fileName of the loaded graphical library*/
	};
}

#endif //CPP_ARCADE_SFMLDisplay_HPP
