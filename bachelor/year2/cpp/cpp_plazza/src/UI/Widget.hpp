/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** Internal functions
*/

#ifndef CPP_PLAZZA_WIDGET_HPP
# define CPP_PLAZZA_WIDGET_HPP

#include <string>
#include "GUI.hpp"

namespace plz {
	namespace GUI {
		class Widget {
		public:
			Widget(const std::string &name, int flags);
			void load(const plz::GUI::Vector2Int &size, const plz::GUI::Vector2Int &pos);
			void unload();
		private:
			std::string _name;
			int _flags;
		};
	}
}

#endif //CPP_PLAZZA_WIDGET_HPP
