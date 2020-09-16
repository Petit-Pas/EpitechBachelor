/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Created by vincent,
*/

#ifndef CPP_INDIE_STUDIO_TASK_HPP
#define CPP_INDIE_STUDIO_TASK_HPP

#include <cstdint>
#include <irrlicht.h>
#include "Element.hpp"

enum class TypeTask : uint8_t {
	UNKNOWN = 0,
	CREATE = 1,
	UPDATE = 2,
	DEL = 3,
	IDLE = 4,
	GAMEOVER = 5
};

struct Task {
	TypeTask task;
	int uniqueId;
	int direction;
	irr::core::vector2df pos;
	Element::Type type;
	Element::State state;
};

#endif /* CPP_INDIE_STUDIO_TASK_HPP */
