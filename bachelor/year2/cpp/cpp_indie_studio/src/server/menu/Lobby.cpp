//
// EPITECH PROJECT, 2018
// indie studio
// File description:
// lobby
//

#include <cstring>
#include <iostream>

#include "Lobby.hpp"
#include "Type.hpp"
#include "GameManager.hpp"

size_t Lobby::_lastIdLobby = 0;

Lobby::Lobby(PlayerCommunication &player) : _master(player), _maxPlayers(STD_PLAYERS), _valid(true), _update(false),
	_waitStart(false), _idLobby(_lastIdLobby), _updateParams(true)
{
	_players.push_back(player);
	_lastIdLobby++;
	_name = std::to_string(_idLobby);
}

Lobby::~Lobby()
{
}

bool Lobby::addPlayer(PlayerCommunication &player)
{
	if (_players.size() + _ias.size() >= _maxPlayers || _valid == false)
		return (false);
	_players.push_back(player);
	player.sendData<>(TypesMenu::CONFIRM);
	player.sendData<int>(true);
	player.sendData<int>(false);
	_updateParams = true;
	return (true);
}

void Lobby::update()
{
	for (auto &player : _players) {
		update(player);
	}
}

void Lobby::update(PlayerCommunication &player)
{
	TypesLobby type;

	if (player.recvData<>(type) || !player.isOpen()) {
		if (!player.isOpen())
			type = TypesLobby::QUIT;
		switch (type) {
		case TypesLobby::CHANGE_SKIN :
			changeSkin(player);
			break;
		case TypesLobby::SKIN_UP :
			changeSkin(player, 1);
			break;
		case TypesLobby::SKIN_DOWN :
			changeSkin(player, -1);
			break;
		case TypesLobby::READY :
			player.ready();
			break;
		case TypesLobby::KICK_PLAYER :
			if (isMaster(player)) {
				kickPlayer();
			}
			break;
		case TypesLobby::LAUNCH_GAME :
			if (isMaster(player)) {
				_waitStart = true;
			}
			break;
		case TypesLobby::RENAME :
			if (isMaster(player)) {
				rename();
			}
			break;
		case TypesLobby::CHANGE_IA :
			if (isMaster(player)) {
				changeIa();
			}
			break;
		default:
			if (isMaster(player)) {
				masterQuit();
			} else {
				quit(player);
			}
			break;
		}
	}
}

void Lobby::changeIa()
{
	iaInfo ia;

	if (_master.recvData<iaInfo>(ia, true)) {
		if (ia.id >= _players.size() + _ias.size()) {
			if (ia.type != ind::ia::PLAYER) {
				_ias.push_back(ia.type);
			}
		} else if (ia.id < _players.size()) {
			if (ia.type != ind::ia::PLAYER && ia.id != 0) {
				kickPlayer(ia.id);
				_ias.push_back(ia.type);
			}
		} else {
			if (ia.type == ind::ia::PLAYER) {
				_ias.erase(_ias.begin() + ia.id - _players.size());
			} else {	
				_ias[ia.id - _players.size()].setType(ia.type);
			}
		}
	}
	_updateParams = true;
	_update = true;
}

void Lobby::changeSkin(PlayerCommunication &player)
{
	size_t skinId;

	if (player.recvData<size_t>(skinId, true))
		player.setSkin(skinId);
	_updateParams = true;
}

void Lobby::changeSkin(PlayerCommunication &player, int nb)
{
	size_t skinId = player.getSkinId();

	player.setSkin(skinId + nb);
	_updateParams = true;
}

void Lobby::kickPlayer()
{
	size_t playerId;

	if (_master.recvData<size_t>(playerId, true))
		kickPlayer(playerId);
}

void Lobby::rename()
{
	char name[32];

	if (_master.recvData<>(name, true)) {
		_name = std::string(name);
		_update = true;
	}
	_updateParams = true;
}

void Lobby::kickPlayer(size_t nb)
{
	if (nb < _players.size()) {
		_players[nb].sendData<>(TypesLobby::KICKED);
		_quitting.push_back(_players[nb]);
		_players.erase(_players.begin() + nb);
		_updateParams = true;
	}
}

void Lobby::masterQuit()
{
	size_t max = _players.size();

	while (max > 0) {
		max--;
		kickPlayer(max);
	}
	_valid = false;
}

void Lobby::quit(PlayerCommunication &player)
{
	size_t nb = 0;

	while (nb < _players.size() && player.getSocket() != _players[nb].getSocket())
		nb++;
	if (nb < _players.size()) {
		kickPlayer(nb);
		_updateParams = true;
	}
}

bool Lobby::playerQuit() const
{
	return (!_quitting.empty());
}

PlayerCommunication Lobby::extractPlayer()
{
	auto player = _quitting.front();
	_quitting.erase(_quitting.begin());

	return (player);
}

bool Lobby::isMaster(const PlayerCommunication &player) const
{
	return (player.getSocket() == _master.getSocket());
}

bool Lobby::valid() const
{
	return (_valid);
}

bool Lobby::isUpToDate()
{
	if (_updateParams) {
		_updateParams = false;
		dumpToClients();
	}
	if (_update == true) {
		_update = false;
		return (false);
	}
	return (true);
}

bool Lobby::gameLaunch() const
{
	return (_waitStart);
}

void Lobby::launchGame()
{
	for (size_t i = 0; i < _players.size(); i++) {
		_players[i].setPlayerId(10 + i);
		_players[i].sendData<>(TypesLobby::LAUNCH_GAME);
	}
	auto pid = fork();

	if (pid == 0) {
		srand(time(nullptr));
		GameManager game(_players, _ias);
		exit(0);
	} else if (pid == -1) {
		return;
	} else {
		_pid = pid;
		_waitStart = false;
	}
}

bool Lobby::isRunning()
{
	return (waitpid(_pid, NULL, WNOHANG) <= 0);
}

const std::vector<PlayerCommunication> &Lobby::getAllPlayers()
{
	_players.insert(_players.end(), _quitting.begin(), _quitting.end());
	_quitting.clear();
	return (_players);
}

lobby Lobby::serialize() const
{
	lobby lob;

	std::memset(&lob, 0, sizeof(lob));
	snprintf(lob.name, sizeof(lob.name) - 1, "%s", _name.c_str());
	lob.nb_persons = _players.size() + _ias.size();
	lob.max_persons = _maxPlayers;
	lob.id = _idLobby;
	return (lob);
}

void Lobby::dumpToClient(size_t i, fullLobby &lob, const std::vector<playerSerial> &players)
{
	lob.playId = i + 10;
	_players[i].sendData<>(TypesLobby::LIST_LOBBY_PARAMS);
	_players[i].sendData<>(lob);
	for (const auto &play : players) {
		_players[i].sendData<>(play);
	}
}

void Lobby::dumpToClients()
{
	fullLobby lob;
	std::vector<playerSerial> players;

	std::memset(&lob, 0, sizeof(lob));
	snprintf(lob.name, sizeof(lob.name) - 1, "%s", _name.c_str());
	lob.nb_persons = _players.size() + _ias.size();
	lob.max_persons = _maxPlayers;
	for (size_t i = 0; i < _players.size(); i++) {
		playerSerial play;

		std::memset(&play, 0, sizeof(play));
		play.id = i + 10;
		play.human = true;
		play.skinId = _players[i].getSkinId();
		play.ready = _players[i].getReady();
		play.type = ind::ia::Types::PLAYER;
		players.emplace_back(play);
	}
	for (size_t i = 0; i < _ias.size(); i++) {
			playerSerial play;
			play.id = i + _players.size() + 10;
			play.human = false;
			play.type = _ias[i].getType();
			play.skinId = i;
			play.ready = true;
			players.emplace_back(play);
	}
	for (size_t i = 0; i < _players.size(); i++) {
		dumpToClient(i, lob, players);
	}
}
