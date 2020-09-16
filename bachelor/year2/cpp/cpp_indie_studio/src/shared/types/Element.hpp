//
// EPITECH PROJECT, 2018
// cpp_arcade
// File description:
// define the types and states of the element
//

#ifndef ELEMENT2_HPP_
#define ELEMENT2_HPP_

namespace Element {
	enum Type {
		EMPTY = 0,
		HARDWALL = 1,
		SOFTWALL,
		PLAYER,
		AI,
		BOMB,
		FIRE,
		BONUS,
		BOMB_UP,
		FIRE_UP,
		SPEED_UP,
		WALK_THROUGH,
		PIERCE_BOMB
	};

	enum State {
		NONE = 0,
		ALIVE = 1,
		BREAKABLE,
		DEAD,
		INVULNERABLE,
		CLOCK,
		EXPLOSION,
		ENDOF_EXPLOSION,
	};
};

#endif /* !ELEMENT2_HPP_ */
