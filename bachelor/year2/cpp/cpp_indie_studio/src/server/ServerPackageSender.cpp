/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Created by vincent,
*/

#include <thread>
#include <chrono>
#include <irrlicht.h>
#include "Player.hpp"
#include "ServerPackageSender.hpp"
#include "Packet.hpp"
#include "MyGlobal.hpp"

ServerPackageSender::ServerPackageSender(std::shared_ptr<LockedItem<std::vector<std::unique_ptr<Player>>>> players,
	std::shared_ptr<LockedItem<std::vector<std::unique_ptr<AEntity>>>> blocking,
	std::shared_ptr<LockedItem<std::vector<PlayerCommunication>>> playerCom
) : _players(players), _blocking(blocking), _playerCom(playerCom)
{
}

void ServerPackageSender::run()
{
	sendPlayers(PackageType::CREATE);
	sendBlocking();
	while (!endG) {
		sendPlayers(PackageType::UPDATE);
		std::this_thread::sleep_for(std::chrono::milliseconds(40));
	}
}

void ServerPackageSender::sendPlayers(const PackageType &type)
{
	_players->lockItem();
	if (!_players->getItem().empty()) {
		for (auto &player : _players->getItem()) {
			packageServerClient package(player->entityToPackage(type));
			if (checkUpdate(type, package)) {
				_playerCom.get()->lockItem();
				auto vec = _playerCom.get()->getItem();
				for (auto &player : vec) {
					player.sendData(package);
				}
				_playerCom.get()->unlockItem();
				player->unsetIdle();
			} else {
				if (!player->isIdleSend()) {
					player->setIdleSend();
					packageServerClient package(player->entityToPackage(PackageType::IDLE));
					_playerCom.get()->lockItem();
					auto vec = _playerCom.get()->getItem();
					for (auto &player : vec) {
						player.sendData(package);
					}
				}
				_playerCom.get()->unlockItem();
			}
		}
	}
	_players->unlockItem();
}

void ServerPackageSender::sendBlocking()
{
	_blocking->lockItem();
	if (!_blocking->getItem().empty()) {
		_playerCom.get()->lockItem();
		auto vec = _playerCom.get()->getItem();
		for (auto &block : _blocking->getItem()) {
			packageServerClient package(block->entityToPackage(PackageType::CREATE));
			for (auto &player : vec) {
				player.sendData(package);
			}
		}
		_playerCom.get()->unlockItem();
	}
	_blocking->unlockItem();
}

bool ServerPackageSender::checkUpdate(const PackageType &type, const packageServerClient &package)
{
	auto cmpPlayer = _cmpPlayers.find(package.uniqueID);
	if (type == PackageType::CREATE && cmpPlayer == _cmpPlayers.end()) {
		_cmpPlayers[package.uniqueID].pos.X = package.posX;
		_cmpPlayers[package.uniqueID].pos.Y = package.posY;
		return true;
	} else if (type == PackageType::UPDATE && cmpPlayer != _cmpPlayers.end()) {
		if (fabsf(cmpPlayer->second.pos.X - package.posX) > 0.01f ||
			fabsf(cmpPlayer->second.pos.Y - package.posY) > 0.01f ||
			static_cast<dir::directions>(package.direction) != cmpPlayer->second.directions) {
			_cmpPlayers[package.uniqueID].pos.X = package.posX;
			_cmpPlayers[package.uniqueID].pos.Y = package.posY;
			_cmpPlayers[package.uniqueID].directions = static_cast<dir::directions>(package.direction);
			return true;
		}
		return false;
	} else if (type == PackageType::DEL && cmpPlayer != _cmpPlayers.end() &&
		package.status == Element::State::DEAD) {
		_cmpPlayers.erase(package.uniqueID);
	}
	return false;
}
