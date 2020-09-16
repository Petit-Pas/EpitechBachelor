/*
** EPITECH PROJECT, 2021
** bsPlazza
** File description:
** internal functions
*/

#include <memory>
#include <sys/msg.h>
#include <csignal>
#include <strings.h>
#include <cstring>
#include <sys/sem.h>
#include <sys/shm.h>
#include "Master.hpp"

plz::Master::Master(int nbThreads) : _amountThreads(nbThreads), _parser(), _newIdMQ(10)
{
	MessageQueue messageQueue(12);
	std::shared_ptr<LockedItem<MessageQueue>> tmp(new LockedItem<MessageQueue>(messageQueue));
	_messageQueue = tmp;

	MessageQueue messageQueueDone(13);
	std::shared_ptr<LockedItem<MessageQueue>> tmp2(new LockedItem<MessageQueue>(messageQueueDone));
	_messageQueueDone = tmp2;

	_requestReceiver = std::thread(&Master::requestReceiver, this);
	std::vector<Task> vector = {};
	std::shared_ptr<plz::LockedItem<std::vector<Task>>> ptr(new LockedItem<std::vector<Task>>(vector));
	_pendingTasks = ptr;
}

plz::Master::~Master()
{
	_requestReceiver.join();
	msgctl(_messageQueue.get()->getItem().getMessageIndex(), IPC_RMID, nullptr);
	_messageQueue.get()->getItem().destroySemaphore();

	msgctl(_messageQueueDone.get()->getItem().getMessageIndex(), IPC_RMID, nullptr);
	_messageQueueDone.get()->getItem().destroySemaphore();

	for (auto &it : _slaves) {
		kill(it.pid, SIGINT);
	}
	int tmp = semget(42, 1, SHM_R | SHM_W);
	semctl(tmp, 1, IPC_RMID);
}

int plz::Master::requestReceiver()
{
	std::string toRemove;
	bool ret;

	while (!endG || !isPendingEmpty()) {
		_messageQueueDone.get()->lockItem();
		ret = _messageQueueDone.get()->getItem().receive(toRemove);
		_messageQueueDone.get()->unlockItem();
		if (ret) {
			removeFromPending(toRemove);
			_pendingTasks.get()->lockItem();
			_pendingTasks.get()->unlockItem();
		} else {
			usleep(100);
		}
	}
	return 0;
}

void plz::Master::manageCmdLoop()
{
	while (!endG) {
		std::vector<Task> commands;
		try {
			commands = _parser.parseLine();
		} catch (std::runtime_error &e) {
			break;
		}
		for (auto &it : commands)
			setOutfileName(it);
		sendCommandList(commands);
		usleep(100);
	}
	endG = true;
}

void plz::Master::setOutfileName(plz::Task &task)
{
	bzero(task.outFileName, 512);
	strcpy(task.outFileName, task.filename);
	switch (task.information) {
	case plz::EMAIL_ADDRESS:
		strcat(task.outFileName, "-email-");
		break;
	case plz::IP_ADDRESS:
		strcat(task.outFileName, "-ip-");
		break;
	case plz::PHONE_NUMBER:
		strcat(task.outFileName, "-phone-");
		break;
	}
	strcat(task.outFileName, std::to_string(rand()).c_str());
	strcat(task.outFileName, ".log");
}

void plz::Master::sendCommandList(std::vector<plz::Task> toSend)
{
	refreshSlavesData();
	for (auto &it : toSend) {
		sendCommand(it);
	}
}

void plz::Master::sendCommand(plz::Task task)
{
	auto index = static_cast<unsigned long>(getIndexFreeSlave());
	MainData data;

	memset(&data, 0, sizeof(MainData));
	if (static_cast<int>(index) == -1) {
		index = _slaves.size();
		_slaves.push_back(getNewSlave());
	}
	data.asked = task;
	appendToPendingTasks(task);
	_messageQueue.get()->lockItem();
	_messageQueue.get()->getItem().send(_slaves.at(index).id, data);
	_messageQueue.get()->unlockItem();
	_messageQueue.get()->lockItem();
	while (!_messageQueue.get()->getItem().receive(_slaves.at(index).id + SHIFT_IN_OUT_MQ, data)) {
		_messageQueue.get()->unlockItem();
		usleep(100);
		_messageQueue.get()->lockItem();
	}
	_messageQueue.get()->unlockItem();
	_slaves.at(index).data = data;
}

int plz::Master::getIndexFreeSlave()
{
	int min = 101;
	int indexMin = -1;

	for (int i = 0; i != static_cast<int>(_slaves.size()); i++) {
		if (_slaves.at(i).data.usePercentage != 100) {
			if (min > _slaves.at(i).data.usePercentage) {
				min = _slaves.at(i).data.usePercentage;
				indexMin = i;
			}
		}
	}
	if (indexMin != -1)
		return indexMin;
	min = _amountThreads;
	for (int i = 0; i != static_cast<int>(_slaves.size()); i++) {
		if (_slaves.at(i).data.waitingListState < min) {
			min = _slaves.at(i).data.waitingListState;
			indexMin = i;
		}
	}
	return indexMin;
}

void plz::Master::refreshSlavesData()
{
	MainData data;

	bzero(&data, sizeof(MainData));
	auto it = _slaves.begin();
	while (it != _slaves.end()) {
		_messageQueue.get()->lockItem();
		_messageQueue.get()->getItem().send((*it).id, data);
		_messageQueue.get()->unlockItem();

		_messageQueue.get()->lockItem();
		while (!_messageQueue.get()->getItem().receive((*it).id + SHIFT_IN_OUT_MQ, (*it).data)) {
			_messageQueue.get()->unlockItem();
			_messageQueue.get()->lockItem();
		}
		_messageQueue.get()->unlockItem();
		if ((*it).data.timeout) {
			eraseFromSlaves((*it).id);
			_slaves.erase(it);
		} else
			it++;
	}
}

plz::Master::threadPool plz::Master::getNewSlave()
{
	threadPool newOne = {_newIdMQ, {}, 0};

	bzero(&newOne.data, sizeof(MainData));
	int pid = fork();
	if (pid == 0) {
		ThreadPoolManager newSlave(_amountThreads, _newIdMQ);
		newSlave.loop();
		exit(0);
	}
	newOne.pid = pid;
	_newIdMQ += 1;
	return newOne;
}

void plz::Master::appendToPendingTasks(plz::Task &task)
{
	_pendingTasks.get()->lockItem();
	_pendingTasks.get()->getItem().push_back(task);
	_pendingTasks.get()->unlockItem();
}

bool plz::Master::isPendingEmpty()
{
	bool ret;

	_pendingTasks.get()->lockItem();
	ret = _pendingTasks.get()->getItem().empty();
	_pendingTasks.get()->unlockItem();
	return ret;
}

void plz::Master::removeFromPending(const std::string &toRemove)
{
	_pendingTasks.get()->lockItem();
	auto list = _pendingTasks.get()->getItem();
	auto it = list.begin();
	while (it != list.end()) {
		if (std::string((*it).outFileName) == toRemove) {
			it = list.erase(it);
			_pendingTasks.get()->getItem() = list;
			_pendingTasks.get()->unlockItem();
			return;
		}
		it++;
	}
	_pendingTasks.get()->unlockItem();
}

void plz::Master::eraseFromSlaves(__attribute__((unused)) int id)
{
}
