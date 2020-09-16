/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Created by vincent,
*/

#include <thread>
#include <chrono>
#include <irrlicht.h>
#include "ClientReceiveUpdate.hpp"
#include "Client.hpp"

bool endG = false;

ClientReceiveUpdate::ClientReceiveUpdate(std::shared_ptr<ClientTCP> playerCom, std::shared_ptr<TaskQueue> &queue
) : _playerCom(playerCom), _queue(queue)
{
}

void ClientReceiveUpdate::run()
{
	packageServerClient package;

	while (!endG) {
		if (receiveServerPackage(package)) {
			applyChanges(package);
		} else
			std::this_thread::sleep_for(std::chrono::milliseconds(40));
	}
}

bool ClientReceiveUpdate::receiveServerPackage(packageServerClient &package)
{
	bool status = _playerCom->recvData(package);
	return (status);
}

void ClientReceiveUpdate::applyChanges(const packageServerClient &package)
{
	if (PackageType::UNKNOWN == package.magicNumber)
		return;
	auto task = packetToTask(package);
	_queue->addTask(task);
}

Task ClientReceiveUpdate::packetToTask(const packageServerClient &package)
{
	auto kindOfTask = static_cast<TypeTask>(package.magicNumber);

	return {kindOfTask, package.uniqueID, package.direction, irr::core::vector2df(package.posX, package.posY),
		static_cast<Element::Type>(package.type), static_cast<Element::State>(package.status)};
}
