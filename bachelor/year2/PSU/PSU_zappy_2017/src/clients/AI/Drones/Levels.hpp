//
// EPITECH PROJECT, 2018
// zappy
// File description:
// levels requirements
//

#ifndef LEVELS_HPP_
#define LEVELS_HPP_

#include <string>
#include <unordered_map>
#include <map>

const std::unordered_map<int, std::unordered_map<std::string, size_t>> LEVELS_REQUIREMENT = {

	/* LEVEL 2 */
	{2,
	 {
		 {"player", 1},
		 {"linemate", 1}
	 }
	},

	/* LEVEL 3 */
	{3,
	 {
		 {"player", 2},
		 {"linemate", 1},
		 {"deraumere", 1},
		 {"sibur", 1}
	 }
	},

	/* LEVEL 4 */
	{4,
	 {
		 {"player", 2},
		 {"linemate", 2},
		 {"sibur", 1},
		 {"phiras", 2}
	 }
	},

	/* LEVEL 5 */
	{5,
	 {
		 {"player", 4},
		 {"linemate", 1},
		 {"deraumere", 1},
		 {"sibur", 2},
		 {"phiras", 1}
	 }
	},

	/* LEVEL 6 */
	{6,
	 {
		 {"player", 4},
		 {"linemate", 1},
		 {"deraumere", 2},
		 {"sibur", 1},
		 {"mendiane", 3}
	 }
	},

	/* LEVEL 7 */
	{7,
	 {
		 {"player", 6},
		 {"linemate", 1},
		 {"deraumere", 2},
		 {"sibur", 3},
		 {"phiras", 1}
	 }
	},

	/* LEVEL 8 */
	{8,
	 {
		 {"player", 6},
		 {"linemate", 2},
		 {"deraumere", 2},
		 {"sibur", 2},
		 {"mendiane", 2},
		 {"phiras", 2},
		 {"thystame", 1}
	 }
	},
	{9,
	 {
		 {"player", 80},
	 }
	}
};

class Level
{
public:
	static const std::unordered_map<std::string, size_t> getRequirementsForPeoples(size_t);
	static std::map<std::string, size_t> getRequirementsForPeoples2(size_t);
	static const std::unordered_map<std::string, size_t> getNeed();
	static size_t getNbPeopleNeeded(size_t);
private:
	Level();
};

#endif /* !LEVELS_HPP_ */
