/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** Internal functions
*/

#ifndef CPP_PLAZZA_WINDOW_HPP
# define CPP_PLAZZA_WINDOW_HPP

#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "GUI.hpp"

namespace plz {
	namespace GUI {
		class Win {
		public:
			Win(unsigned int width, unsigned int height, unsigned int framerate, std::string name);
			Win(const sf::RenderWindow &_window);
			virtual ~Win();
			bool isOpen();
			void handleClose();
			plz::GUI::Vector2Int getSize();
			void render();
			void update();
		private:
			sf::RenderWindow _window;
		};
	}
}

#endif //CPP_PLAZZA_WINDOW_HPP
