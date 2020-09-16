//
// EPITECH PROJECT, 2018
// Zappy
// File description:
// share inventory with group
//

#ifndef CMD_SHARED_INVENTORY_HPP_
#define CMD_SHARED_INVENTORY_HPP_

#include "AComplexCommand.hpp"

namespace Cmd
{
	class SharedInventory : public AComplexCommand
	{
	public:
		SharedInventory(const std::shared_ptr<Connection> &, ADrone &);

		void updateCommands(ADrone &);
		bool unusedMessage(const std::string &, ADrone &);
	};
};

#endif /* !CMD_SHARED_INVENTORY_HPP_ */
