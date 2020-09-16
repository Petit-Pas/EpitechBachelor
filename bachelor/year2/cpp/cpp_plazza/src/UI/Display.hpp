/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** Internal functions
*/

#ifndef CPP_PLAZZA_DISPLAY_HPP
# define CPP_PLAZZA_DISPLAY_HPP

#include <vector>
#include "PlotLine.hpp"
#include "Window.hpp"
#include "Widget.hpp"

namespace plz {
	namespace GUI {
		class Display {
		public:
			Display(unsigned int width, unsigned int height, unsigned int framerate, std::string name);
			std::string loop();
			bool isOpen();
			void updateSlave(int id, float value, int queue);
			void setDeadSlave(int id);
		private:
			void displaySlaves();
			void displayButtons();
			void handleInputs();
			Win _window;
			Widget _taskManager;
			Widget _commandManager;
			std::string _textString;
			std::vector<PlotLine> _slaves;
			std::string _textValidate;
		};
	}
}

#endif //CPP_PLAZZA_DISPLAY_HPP
