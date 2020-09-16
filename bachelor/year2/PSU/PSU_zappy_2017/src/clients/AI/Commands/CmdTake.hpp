//
// EPITECH PROJECT, 2018
// Zappy
// File description:
// Simple Take
//

#ifndef CMD_TAKE_HPP_
#define CMD_TAKE_HPP_

#include <string>
#include "SimpleCmd.hpp"
#include "ADrone.hpp"

namespace Cmd
{
	class Take : public SimpleCmd
	{
	public:
		Take(const std::shared_ptr<Connection> &, const std::string &, ADrone &, const std::string & = "Take");

	private:
		void okCase(ADrone &) override;
		void koCase(ADrone &) override;

		static const size_t DEFAULT_TIME;
		std::string _item;
	};
};

#endif /* !CMD_TAKE_HPP_ */
