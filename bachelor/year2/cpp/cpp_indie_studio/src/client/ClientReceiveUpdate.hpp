/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Created by vincent,
*/
#ifndef CPP_INDIE_STUDIO_CLIENTRECEIVEUPDATE_HPP
#define CPP_INDIE_STUDIO_CLIENTRECEIVEUPDATE_HPP

#include "Packet.hpp"
#include "LockedItem.hpp"
#include "AEntityClient.hpp"
#include "ClientTCP.hpp"
#include "Client.hpp"
#include "TaskQueue.hpp"
#include "Task.hpp"

extern bool endG;

using entityKey = std::pair<int, Element::Type>;

class ClientReceiveUpdate {
public:
	ClientReceiveUpdate(std::shared_ptr<ClientTCP> playerCom, std::shared_ptr<TaskQueue> &queue
	);
	~ClientReceiveUpdate() = default;

	void run();

private:
	bool receiveServerPackage(packageServerClient &);

	void applyChanges(const packageServerClient &);
	Task packetToTask(const packageServerClient &);

private:
	std::shared_ptr<ClientTCP> _playerCom;
	std::shared_ptr<TaskQueue> _queue;
};

#endif //CPP_INDIE_STUDIO_CLIENTRECEIVEUPDATE_HPP
