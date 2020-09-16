/*
** EPITECH PROJECT, 2021
** pbrain-gomoku
** File description:
** internal functions
*/

#ifndef PBRAIN_GOMOKU_GOMOKU_HPP
# define PBRAIN_GOMOKU_GOMOKU_HPP

namespace gom {
	enum state {
		YOU_PLAY,
		OTHER_PLAYED,
		END,
		START,
		BOARD,
		INFO,
		ABOUT,
		UNKNOWN
	};

	enum combinations {
		IMPOSSIBLE = 0,
		EMPTY = 1,
		ONE,
		TWO,
		THREE,
		NO_LIMIT_THREE,
		FOUR
	};

	enum specialTurn {
		NO_SPECIAL = 0,
		LOOSE_2_3 = 1,
		WIN_2_3, /* (.X.XX. or .XX.X. different lines) or (.XXX.. or ..XXX. same line)*/
		LOOSE_4,
		WIN_4
	};
}

#endif //PBRAIN_GOMOKU_GOMOKU_HPP
