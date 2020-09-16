//
// EPITECH PROJECT, 2018
// Zappy
// File description:
// Simple Forward
//

#ifndef CMD_FORWARD_HPP_
#define CMD_FORWARD_HPP_

#include "SimpleCmd.hpp"

namespace Cmd
{
	class Forward : public SimpleCmd
	{
	public:
		Forward(const std::shared_ptr<Connection> &, ADrone &, const std::string & = "Forward");

		void okCase(ADrone &) override;
	private:
		static const size_t DEFAULT_TIME;
	};
};

#endif /* !CMD_FORWARD_HPP_ */
