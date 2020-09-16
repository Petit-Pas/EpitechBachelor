//
// EPITECH PROJECT, 2018
// Zappy
// File description:
// Simple set
//

#ifndef ZAPPY_CMDSET_HPP
#define ZAPPY_CMDSET_HPP

#include <string>
#include "SimpleCmd.hpp"
#include "ADrone.hpp"

namespace Cmd
{
	class Set : public SimpleCmd
	{
	public:
		Set(const std::shared_ptr<Connection> &, const std::string &, ADrone &, const std::string & = "Set");

	private:
		void okCase(ADrone &) override;

		static const size_t DEFAULT_TIME;
		std::string _item;
	};
};

#endif //ZAPPY_CMDSET_HPP
