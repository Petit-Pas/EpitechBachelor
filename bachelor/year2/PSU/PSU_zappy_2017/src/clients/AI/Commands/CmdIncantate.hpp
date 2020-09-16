//
// EPITECH PROJECT, 2018
// Zappy
// File description:
// incantate
//

#ifndef CMD_INCANTATE_HPP_
#define CMD_INCANTATE_HPP_

#include "SimpleCmd.hpp"

namespace Cmd
{
	class Incantate : public SimpleCmd
	{
	public:
		Incantate(const std::shared_ptr<Connection> &, const std::string & = "Incantation");
		Incantate(const std::shared_ptr<Connection> &, bool, const std::string & = "Incantation");
		bool handleServerResponse(const std::string &, ADrone &) override;
	private:
		bool _ko;
	};
};

#endif /* !CMD_INCANTATE_HPP_ */
