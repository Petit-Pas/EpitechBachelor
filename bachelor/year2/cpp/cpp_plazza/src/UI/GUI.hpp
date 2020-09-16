/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** Internal functions
*/

#ifndef CPP_PLAZZA_GUI_HPP
# define CPP_PLAZZA_GUI_HPP

namespace plz {
	namespace GUI {
		typedef struct Vector2Int {
			Vector2Int(int x, int y) : x(x), y(y) {};
			int x;
			int y;
		} Vector2Int;
	}
}

#endif //CPP_PLAZZA_GUI_HPP
