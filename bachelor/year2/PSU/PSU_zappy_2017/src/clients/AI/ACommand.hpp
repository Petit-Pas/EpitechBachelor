//
// EPITECH PROJECT, 2018
// zappy
// File description:
// zappy commands Abstract class
//

#ifndef ACOMMAND_HPP_
#define ACOMMAND_HPP_

#include <memory>
#include "ADrone.hpp"

class ADrone;

class ACommand
{
public:
	ACommand(const std::shared_ptr<Connection> &);
	virtual ~ACommand();

	/**
	 * handle the server responses
	 */
	virtual bool handleServerResponse(const std::string &, ADrone &) = 0;

	/**
	 * Called when a response was received by server
	 */
	virtual void update(ADrone &) = 0;

	/**
	 * send the next command to the server
	 */
	virtual bool sendCommand(ADrone &) = 0;

	/**
	 * send command is called if true is returned
	 */
	virtual bool isDone() const;

	/**
	 * The command will be deleted if true is returned
	 */
	virtual bool isToDelete() const;

	/**
	 * Return the number of ticks this command took until now
	 */
	virtual size_t getTicksPassed() const = 0;

protected:
	bool _done;
	bool _toDelete;
	const std::string _command;
	std::shared_ptr<Connection> _com;
};

#endif /* !ACOMMAND_HPP_ */
