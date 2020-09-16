//
// EPITECH PROJECT, 2018
// indie studio
// File description:
// lobby
//

#ifndef LOBBY_HPP_
#define LOBBY_HPP_

#if defined(WIN32)
#else
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#endif

#include <vector>
#include <string>

#include "PlayerCommunication.hpp"
#include "IADefinition.hpp"
#include "MenuStruct.hpp"

class Lobby {
public:
	Lobby(PlayerCommunication &);
	~Lobby();

	/* menu dependant */
	bool addPlayer(PlayerCommunication &);
	void update();
	void update(PlayerCommunication &);
	void changeSkin(PlayerCommunication &);
	void changeSkin(PlayerCommunication &, int);
	void kickPlayer();
	void kickPlayer(size_t);
	void masterQuit();
	void quit(PlayerCommunication &);

	bool isMaster(const PlayerCommunication &) const;
	bool valid() const;
	bool isUpToDate();

	bool playerQuit() const;
	PlayerCommunication extractPlayer();
	bool gameLaunch() const;

	void rename();
	void launchGame();

	/* forked process */
	bool isRunning();
	const std::vector<PlayerCommunication> &getAllPlayers();

	lobby serialize() const;

private:
	void dumpToClients();
	void dumpToClient(size_t, fullLobby &, const std::vector<playerSerial> &);

	void changeIa();
private:
	PlayerCommunication _master;
	std::vector<PlayerCommunication> _players;
	std::vector<IADefinition> _ias;
	size_t _maxPlayers;

	bool _valid;
	bool _update;
	bool _waitStart;

	static size_t _lastIdLobby;
	size_t _idLobby;

	std::vector<PlayerCommunication> _quitting;

	std::string _name;
	bool _updateParams;

	pid_t _pid;

	static const size_t MAX_PLAYERS = 8;
	static const size_t STD_PLAYERS = 4;
	static const size_t MIN_PLAYERS = 1;
};

#endif /* !LOBBY_HPP_ */
