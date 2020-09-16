//
// EPITECH PROJECT, 2018
// zappy
// File description:
// This drone goal is to gather the most food he can
//

#ifndef DRONE_FARMER_HPP_
#define DRONE_FARMER_HPP_

#include "ADrone.hpp"

namespace Drone
{
	class Farmer : public ADrone
	{
	public:
		Farmer(const std::string &, int, const std::string &);
		Farmer(const std::shared_ptr<ADrone> drone);
		using ADrone::getTotalCommands;
		using ADrone::removeFromTile;
		using ADrone::initNeed;
		void findNextAction();
	};
}

#endif /* !DRONE_FARMER_HPP_ */
