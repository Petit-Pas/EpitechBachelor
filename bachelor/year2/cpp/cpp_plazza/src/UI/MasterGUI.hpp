/*
** EPITECH PROJECT, 2021
** cpp_plazza
** File description:
** internal functions
*/

#ifndef CPP_PLAZZA_MASTERGUI_HPP
# define CPP_PLAZZA_MASTERGUI_HPP

#include "Master.hpp"
#include "Display.hpp"

namespace plz {
	namespace GUI {
		class MasterGUI : public plz::Master {
		public:
			MasterGUI(int amountThreads, unsigned int width, unsigned int height, unsigned int framerate,
				const std::string &name
			);
			~MasterGUI() = default;
			void manageCmdLoop() override;
			void updateDisplay();
			void eraseFromSlaves(int id) override;
			void sendCommandList(std::vector<plz::Task> toSend) override;

		private:
			std::shared_ptr<Display> _display;
		};
	};
};
#endif //CPP_PLAZZA_MASTERGUI_HPP
