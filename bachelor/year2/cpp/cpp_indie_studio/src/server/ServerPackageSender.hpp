/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Created by vincent,
*/

#ifndef CPP_INDIE_STUDIO_SRVENTITYPCKGMANAGER_HPP
#define CPP_INDIE_STUDIO_SRVENTITYPCKGMANAGER_HPP

#include <map>
#include <vector>
#include <irrlicht.h>
#include "Direction.hpp"
#include "TimedObject.hpp"
#include "AMovable.hpp"
#include "LockedItem.hpp"
#include "AEntity.hpp"
#include "ABonus.hpp"
#include "Packet.hpp"
#include "PlayerCommunication.hpp"

struct PlayerInfo {
	irr::core::vector2df pos;
	dir::directions directions;
};

class ServerPackageSender {
public:
	ServerPackageSender(std::shared_ptr<LockedItem<std::vector<std::unique_ptr<Player>>>> players,
		std::shared_ptr<LockedItem<std::vector<std::unique_ptr<AEntity>>>> blocking,
		std::shared_ptr<LockedItem<std::vector<PlayerCommunication>>> playerCom
	);

	~ServerPackageSender() = default;
	void run();

private:
	void sendPlayers(const PackageType &);
	void sendBlocking();
	bool checkUpdate(const PackageType &type, const packageServerClient &package);
	std::shared_ptr<LockedItem<std::vector<std::unique_ptr<Player>>>> _players; /*!< contains the players */
	std::shared_ptr<LockedItem<std::vector<std::unique_ptr<AEntity>>>> _blocking; /*!< contains walls and breakables */
	std::shared_ptr<LockedItem<std::vector<PlayerCommunication>>> _playerCom;
	std::map<int, PlayerInfo> _cmpPlayers;
};

#endif //CPP_INDIE_STUDIO_SRVENTITYPCKGMANAGER_HPP
