/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Created by vincent,
*/

#ifndef CPP_INDIE_STUDIO_NODE_HPP
#define CPP_INDIE_STUDIO_NODE_HPP

#include <vector>
#include "Element.hpp"

struct twoFloat {
	float y;
	float x;
};

struct node {
	bool visited;
	bool deadEnd;
	std::vector<node *> near;
	node *parent;
	twoFloat pos;
	Element::Type type;
	short danger;
	unsigned short goal;
	unsigned short id;
	int uniqueID;
};


#endif /* CPP_INDIE_STUDIO_NODE_HPP */
