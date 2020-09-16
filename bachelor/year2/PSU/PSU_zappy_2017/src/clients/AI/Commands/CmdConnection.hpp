//
// EPITECH PROJECT, 2018
// zappy
// File description:
// Connection command
//

#ifndef CMD_CONNECTION_HPP_
#define CMD_CONNECTION_HPP_

#include "ACommand.hpp"

class CmdConnection : public ACommand
{
public:
	CmdConnection(const std::shared_ptr<Connection> &, const std::string &);

	bool handleServerResponse(const std::string &, ADrone &) override;
	bool sendCommand(ADrone &) override;

	void update(ADrone &) override;

	bool isDone() const override;

	size_t getTicksPassed() const override;
private:
	const std::string _teamName;
	size_t _nbResponse;
};

#endif /* !CMD_CONNECTION_HPP_ */
