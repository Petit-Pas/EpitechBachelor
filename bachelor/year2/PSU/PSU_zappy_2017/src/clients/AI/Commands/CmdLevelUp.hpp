//
// EPITECH PROJECT, 2018
// Zappy
// File description:
// Leveling
//

#ifndef CMD_LEVEL_UP_HPP_
#define CMD_LEVEL_UP_HPP_

#include "AComplexCommand.hpp"

namespace Cmd
{
	class LevelUp : public AComplexCommand
	{
	public:
		LevelUp(const std::shared_ptr<Connection> &con, ADrone &, const std::vector<std::pair<std::string, Tile>> &);
//		bool isDone() const override;

	private:
		void updateCommands(ADrone &) override;
		bool unusedMessage(const std::string &, ADrone &) override;
	private:
		std::vector<std::pair<std::string, Tile>> _incantTeam;
	};
}

#endif /* !CMD_LEVEL_UP_HPP_ */
