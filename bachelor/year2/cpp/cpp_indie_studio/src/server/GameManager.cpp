/*
** EPITECH PROJECT, 2021
** cpp_inidie_studio
** File description:
** internal functions
*/

#include <iostream>
#include <csignal>
#include <entities/AIFactory.hpp>
#include "MyGlobal.hpp"
#include "PlayerCommunication.hpp"
#include "ServerPackageSender.hpp"
#include "MapGenerator.hpp"
#include "GameManager.hpp"

GameManager::GameManager(std::vector<PlayerCommunication> &playCom, std::vector<IADefinition> & ias)
{
	auto players = std::make_shared<LockedItem<std::vector<std::unique_ptr<Player>>>>();
	auto blocking = std::make_shared<LockedItem<std::vector<std::unique_ptr<AEntity>>>>();
	auto fires = std::make_shared<LockedItem<std::vector<std::unique_ptr<Fire>>>>();
	auto bombs = std::make_shared<LockedItem<std::vector<std::unique_ptr<Bomb>>>>();
	auto bonuses = std::make_shared<LockedItem<std::vector<std::unique_ptr<ABonus>>>>();

	auto playerCommunication = std::make_shared<LockedItem<std::vector<PlayerCommunication>>>(playCom);

	std::vector<std::pair<float, float>> startPos = {{1.5f, 1.5f}, {11.5f, 13.5f}, {1.5f, 13.5f}, {11.5f, 1.5f}};

	for (size_t index = 0; index < playCom.size(); index++) {
		players->getItem().push_back(
			std::make_unique<Player>(startPos.at(index), playCom.at(index).getPlayerId()));
	}

	for (size_t index = 0; index < ias.size(); index++) {
		auto *newAI = AIFactory::getAI(ias[index].getType(), startPos[index + playCom.size()],
			static_cast<int>(10 + index + playCom.size()) , players, blocking, fires, bombs, bonuses, playerCommunication);
		players->getItem().push_back(std::unique_ptr<AI>(newAI));
	}

	MapGenerator mapGenerator;
	if (!mapGenerator.GetNewTemplate()) {
		std::cerr << "Error while opening map/" << std::endl;
		endTheGame(players, playerCommunication);
		return;
	}
	mapGenerator.setEntities(blocking);

	TimerManager timerManager(players, blocking, fires, bombs, bonuses, playerCommunication);
	ServerPackageReceiver serverPackageReceiver(players, blocking, fires, bombs, bonuses, playerCommunication);
	ServerPackageSender serverPackageSender(players, blocking, playerCommunication);

	auto threadTimerManager = Thread<TimerManager>(timerManager);
	auto threadServerReceivePackage = Thread<ServerPackageReceiver>(serverPackageReceiver);
	auto threadServerSendPackage = Thread<ServerPackageSender>(serverPackageSender);

	while (!endG) {
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		if (endOfGame(players)) {
			endG = true;
		}
	}
	threadServerSendPackage.getThread().join();
	threadTimerManager.getThread().join();
	threadServerReceivePackage.getThread().join();
	endTheGame(players, playerCommunication);
}

GameManager::~GameManager()
{
}

void GameManager::endTheGame(const std::shared_ptr<LockedItem<std::vector<std::unique_ptr<Player>>>> &players,
	const std::shared_ptr<LockedItem<std::vector<PlayerCommunication>>> &playerCom
) const
{
	size_t i = 0;

	while (i < players->getItem().size() && players->getItem()[i]->getState() == Element::State::DEAD) {
		i++;
	}
	if (i < players->getItem().size()) {
		packageServerClient package(players->getItem()[i]->entityToPackage(PackageType::GAMEOVER));

		auto vec = playerCom->getItem();
		for (auto &player : vec) {
			player.sendData(package);
		}
	} else {
		packageServerClient package(players->getItem()[0]->entityToPackage(PackageType::GAMEOVER));

		package.uniqueID = 15;
		auto vec = playerCom->getItem();
		for (auto &player : vec) {
			player.sendData(package);
		}
	}
}

bool GameManager::endOfGame(const std::shared_ptr<LockedItem<std::vector<std::unique_ptr<Player>>>> &players)
{
	size_t alive = 0;
	size_t iaAlive = 0;

	for (const auto &player : players->getItem()) {
		if (player->getState() != Element::State::DEAD) {
			alive++;
			if (player->getType() == Element::Type::AI)
				iaAlive++;
		}
	}
	return (alive < 2 || iaAlive == alive);
}
