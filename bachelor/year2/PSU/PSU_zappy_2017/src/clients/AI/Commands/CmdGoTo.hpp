//
// EPITECH PROJECT, 2018
// Zappy
// File description:
// go to a defined tile
//

#ifndef CMD_GO_TO_HPP_
#define CMD_GO_TO_HPP_

#include "AComplexCommand.hpp"

namespace Cmd
{
	class GoTo : public AComplexCommand
	{
	public:
		GoTo(const std::shared_ptr<Connection> &, const Position &, ADrone &);
	private:
		void updateCommands(ADrone &) override ;
		bool unusedMessage(const std::string &, ADrone &) override ;

		void setNextAction(ADrone &);
	private:
		Position _target;
	};
};

#endif /* !CMD_GO_TO_HPP_ */
