//
// EPITECH PROJECT, 2018
// Zappy
// File description:
// Simple Right
//

#ifndef CMD_RIGHT_HPP_
#define CMD_RIGHT_HPP_

#include "SimpleCmd.hpp"

namespace Cmd
{
	class Right : public SimpleCmd
	{
	public:
		Right(const std::shared_ptr<Connection> &, ADrone &, const std::string & = "Right");

		void okCase(ADrone &) override;
	private:
		static const size_t DEFAULT_TIME;
	};
};

#endif /* !CMD_RIGHT_HPP_ */
