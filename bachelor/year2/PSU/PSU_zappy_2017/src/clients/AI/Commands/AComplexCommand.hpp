//
// EPITECH PROJECT, 2018
// Zappy
// File description:
// define a command composed of multiple command (ex: find a melanite)
//

#ifndef ACOMPLEX_COMMAND_HPP_
#define ACOMPLEX_COMMAND_HPP_

#include <vector>
#include <memory>
#include "ACommand.hpp"

namespace Cmd
{
	class AComplexCommand : public ACommand
	{
	public:
		AComplexCommand(const std::shared_ptr<Connection> &);

		/**
		 * default isDone calls isDone on each actions in is vector
		 */
		virtual bool isDone() const;

		/**
		 * call update on each sub command, then calls update commands
		 */
		void update(ADrone &);

		/**
		 * default isToDelete check if all actions are deleted and _toDelete is true
		 */
		bool isToDelete() const;

		/**
		 * default handle calls the actions methods, 
		 * if none match then it calls unusedMessage
		 */
		bool handleServerResponse(const std::string &, ADrone &);

		/**
		 * calls the first command that is not done sendCommand
		 */
		bool sendCommand(ADrone &);

		/**
		 * return the sum of ticks passed for action + previous actions
		 */
		size_t getTicksPassed() const;
	private:
		/**
		 * called when a server response has been used
		 */
		virtual void updateCommands(ADrone &) = 0;

		/**
		 * called when a server response doesn't match any action
		 */
		virtual bool unusedMessage(const std::string &, ADrone &) = 0;

		void eraseCmds();

	protected:
		std::vector<std::shared_ptr<ACommand>> _actions;
		bool _done;

	private:
		size_t _ticks;
	};
};

#endif /* !ACOMPLEX_COMMAND_HPP_ */
