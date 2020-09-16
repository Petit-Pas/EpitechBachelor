//
// EPITECH PROJECT, 2018
// Zappy
// File description:
// do as the master say
//

#ifndef CMD_OBEY_INCANTATOR_HPP_
#define CMD_OBEY_INCANTATOR_HPP_

#include "AComplexCommand.hpp"
#include "Broadcast.hpp"

namespace Cmd
{
	class ObeyIncantator : public AComplexCommand
	{
	public:
		ObeyIncantator(const std::shared_ptr<Connection> &, ADrone &);

		void updateCommands(ADrone &) override;
		bool unusedMessage(const std::string &, ADrone &) override;

	private:
	};
};

#endif /* !CMD_OBEY_INCANTATOR_HPP_ */
