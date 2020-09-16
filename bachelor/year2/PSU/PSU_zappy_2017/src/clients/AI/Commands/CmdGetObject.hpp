//
// EPITECH PROJECT, 2018
// Zappy
// File description:
// get a defined object
//

#ifndef CMD_GET_OBJECT_HPP_
#define CMD_GET_OBJECT_HPP_

#include "AComplexCommand.hpp"

namespace Cmd
{
	class GetObject : public AComplexCommand
	{
	public:
		GetObject(const std::shared_ptr<Connection> &, const std::string &, ADrone &);
	private:
		void updateCommands(ADrone &) override;
		bool unusedMessage(const std::string &, ADrone &) override ;
	private:
		std::string _target;
		std::size_t _nb;
	};
};

#endif /* !CMD_GO_TO_HPP_ */
