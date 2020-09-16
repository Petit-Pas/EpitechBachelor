//
// EPITECH PROJECT, 2018
// Zappy
// File description:
// handle the incantation master side once everyone is on the same tile
//

#ifndef CMD_MASTER_INCANTATION_HPP_
#define CMD_MASTER_INCANTATION_HPP_

#include "AComplexCommand.hpp"

namespace Cmd
{
	class MasterIncantation : public AComplexCommand
	{
	public:
		MasterIncantation(const std::shared_ptr<Connection> &, ADrone &, const std::vector<std::pair<std::size_t , std::unordered_map<std::string, size_t>>> &);

		void updateCommands(ADrone &) override;
		bool unusedMessage(const std::string &, ADrone &) override;

		void prepareNextIncantation(ADrone &);

	private:
		bool isReadyToIncant(ADrone &drone);

	private:
		std::vector<std::pair<std::size_t , std::unordered_map<std::string, size_t>>> _team;
		std::vector<std::size_t> _teamFinished;

	};
};

#endif /* !CMD_MASTER_INCANTATION_HPP_ */
