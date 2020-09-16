//
// EPITECH PROJECT, 2018
// indie studio
// File description:
// types
//

#ifndef TYPE_HPP_
#define TYPE_HPP_

enum class TypesMenu {
	/* client actions */
	QUIT,
	JOIN_LOBBY,

	/* server actions */
	LIST_LOBBY,
	CONFIRM
};

enum class TypesLobby {
	/* client actions */
	QUIT,
	CHANGE_SKIN,
	SKIN_DOWN,
	SKIN_UP,
	READY,

	/* master actions */
	KICK_PLAYER,
	LAUNCH_GAME,
	RENAME,
	CHANGE_IA,

	/* lobby actions */
	LIST_LOBBY_PARAMS,
	KICKED
};

#endif /* !TYPE_HPP_ */
