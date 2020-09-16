//
// EPITECH PROJECT, 2018
// Zappy
// File description:
// Inventory command
//

#ifndef ZAPPY_CMDINVENTORY_HPP
#define ZAPPY_CMDINVENTORY_HPP

#include "SimpleCmd.hpp"

namespace Cmd
{
	class Inventory : public SimpleCmd
	{
	public:
		Inventory(const std::shared_ptr<Connection> &, const std::string & = "Inventory");
		bool handleServerResponse(const std::string &, ADrone &) override;
	};
};

#endif //ZAPPY_CMDINVENTORY_HPP
