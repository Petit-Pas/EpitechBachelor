/*
** EPITECH PROJECT, 2021
** cpp_inidie_studio
** File description:
** internal functions
*/

#ifndef CPP_INIDIE_STUDIO_SERVER_HPP
# define CPP_INIDIE_STUDIO_SERVER_HPP

#include "AMovable.hpp"
#include "AEntity.hpp"
#include "LockedItem.hpp"
#include "TimedObject.hpp"
#include "Thread.hpp"
#include "ABonus.hpp"
#include "TimerManager.hpp"
#include "ServerPackageReceiver.hpp"
#include "IADefinition.hpp"
#include "AI.hpp"

class GameManager {
public:
	GameManager(std::vector<PlayerCommunication> &playCom, std::vector<IADefinition> &ias);
	~GameManager();
private:
	bool endOfGame(const std::shared_ptr<LockedItem<std::vector<std::unique_ptr<Player>>>> &);
	void endTheGame(
	const std::shared_ptr<LockedItem<std::vector<std::unique_ptr<Player>>>> &,
	const std::shared_ptr<LockedItem<std::vector<PlayerCommunication>>> &) const;
};

#endif //CPP_INIDIE_STUDIO_SERVER_HPP
