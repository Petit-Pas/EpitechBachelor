//
// EPITECH PROJECT, 2018
// Zappy
// File description:
// Simple Broadcast
//

#ifndef CMD_BROADCAST_HPP_
#define CMD_BROADCAST_HPP_

#include "SimpleCmd.hpp"

namespace Cmd
{
	class Broadcast : public SimpleCmd
	{
	public:
		Broadcast(const std::shared_ptr<Connection> &, const std::string &, const std::string & = "Broadcast");
	private:
		static const size_t DEFAULT_TIME;
	};
};

#endif /* !CMD_BROADCAST_HPP_ */
