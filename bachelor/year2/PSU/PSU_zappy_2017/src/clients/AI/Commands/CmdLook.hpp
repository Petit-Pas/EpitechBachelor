//
// EPITECH PROJECT, 2018
// Zappy
// File description:
// look the tiles
//

#ifndef CMD_LOOK_HPP_
#define CMD_LOOK_HPP_

#include "ACommand.hpp"

namespace Cmd
{
	class Look : public ACommand
	{
	public:
		Look(const std::shared_ptr<Connection> &);

		bool handleServerResponse(const std::string &, ADrone &) override;
		bool sendCommand(ADrone &) override;

		void update(ADrone &) override;

		size_t getTicksPassed() const override;
	private:
		bool epurMsg(std::string &) const;
	private:
		static const size_t DEFAULT_TICKS;
	};
};

#endif /* !CMD_LOOK_HPP_ */
