//
// EPITECH PROJECT, 2018
// indie studio
// File description:
// structures for lobby
//

#ifndef MENU_STRUCT_HPP_
#define MENU_STRUCT_HPP_

#include "IASetting.hpp"

struct lobby {
	char name[32];
	int nb_persons;
	int max_persons;
	size_t id;
};

struct fullLobby {
	char name[32];
	int nb_persons;
	int max_persons;
	size_t playId;
	/* list of players */
};

struct playerSerial {
	size_t id;
	int human;
	int skinId;
	int ready;
	ind::ia::Types type;
};

struct iaInfo {
	size_t id;
	ind::ia::Types type;
};

#endif /* !MENU_STRUCT_HPP_ */
