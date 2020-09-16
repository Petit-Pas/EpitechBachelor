/*
** EPITECH PROJECT, 2021
** cpp_inidie_studio
** File description:
** internal functions
*/

#ifndef CPP_INIDIE_STUDIO_PACKET_HPP
# define CPP_INIDIE_STUDIO_PACKET_HPP

#include "MagicNumbers.hpp"

struct packageClientServer {
	magicClientServer magicNumber;
	int playerID;
	int action;
};

struct packageServerClient {
	int magicNumber;
	int playerID;
	int uniqueID;
	float posX;
	float posY;
	int direction;
	int type;
	int status;
};

#endif //CPP_INIDIE_STUDIO_PACKET_HPP
