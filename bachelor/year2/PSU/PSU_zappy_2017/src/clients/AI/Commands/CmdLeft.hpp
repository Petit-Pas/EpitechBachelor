//
// EPITECH PROJECT, 2018
// Zappy
// File description:
// Simple Left
//

#ifndef CMD_LEFT_HPP_
#define CMD_LEFT_HPP_

#include "SimpleCmd.hpp"

namespace Cmd
{
	class Left : public SimpleCmd
	{
	public:
		Left(const std::shared_ptr<Connection> &, ADrone &, const std::string & = "Left");

		void okCase(ADrone &) override;
	private:
		static const size_t DEFAULT_TIME;
	};
};

#endif /* !CMD_LEFT_HPP_ */
