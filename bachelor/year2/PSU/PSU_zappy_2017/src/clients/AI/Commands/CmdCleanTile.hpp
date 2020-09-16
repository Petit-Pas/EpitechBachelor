//
// EPITECH PROJECT, 2018
// Zappy
// File description:
// clean a tile
//

#ifndef CMD_CLEAN_TILE_HPP_
#define CMD_CLEAN_TILE_HPP_

#include "AComplexCommand.hpp"

namespace Cmd
{
	class CleanTile : public AComplexCommand
	{
	public:
		CleanTile(const std::shared_ptr<Connection> &, ADrone &, const std::unordered_map<std::string, size_t> &);
		~CleanTile();
	private:
		void updateCommands(ADrone &) override;
		bool unusedMessage(const std::string &, ADrone &) override;
	private:
		std::unordered_map<std::string, size_t> _target;
	};
};

#endif /* !CMD_CLEAN_TILE_HPP_ */
