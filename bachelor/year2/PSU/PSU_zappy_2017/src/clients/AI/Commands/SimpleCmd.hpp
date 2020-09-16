//
// EPITECH PROJECT, 2018
// Zappy
// File description:
// Simple Command
//

#ifndef SIMPLE_CMD_HPP_
#define SIMPLE_CMD_HPP_

#include "ACommand.hpp"

namespace Cmd
{
	class SimpleCmd : public ACommand
	{
	public:
		SimpleCmd(const std::shared_ptr<Connection> &, const std::string &, size_t ticks = 0,const std::string & = "");
		virtual bool handleServerResponse(const std::string &, ADrone &);
		bool sendCommand(ADrone &);

		void update(ADrone &);

		size_t getTicksPassed() const;
	private:
		virtual void koCase(ADrone &);
		virtual void okCase(ADrone &);
	private:
		std::string _msg;
		std::size_t _ticks;
	};
};

#endif /* !SIMPLE_CMD_HPP_ */
