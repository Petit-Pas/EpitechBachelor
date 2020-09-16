/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** Internal functions
*/

#ifndef CPP_PLAZZA_PLOTLINES_HPP
# define CPP_PLAZZA_PLOTLINES_HPP

#include <deque>
#include "GUI.hpp"

namespace plz {
	namespace GUI {
		class PlotLine {
		public:
			PlotLine(int _id);
			void addValue(float value);
			void load(const plz::GUI::Vector2Int &_size);
			void setQueue(int queue);
			int getId() const;
		private:
			int _id;
			int _queue;
			std::deque<float> _values;
		};
	}
}

#endif //CPP_PLAZZA_PLOTLINES_HPP
