/*
** EPITECH PROJECT, 2018
** bsPlazza
** File description:
** Internal functions
*/

#include <csignal>
#include "ThreadPoolManager.hpp"

static void sigHandler(__attribute__((unused)) int signum)
{
	plz::endG = true;
}

plz::ThreadPoolManager::ThreadPoolManager(int amount, int id) : _id(id), _messageQueue(12), _inactive(true),
	_timeInactive(0), _end(false)
{
	for (int i = 0; i != amount; i++) {
		ThreadData newData(i);
		std::shared_ptr<LockedItem<ThreadData>> p(new LockedItem<ThreadData>(newData));
		_datas.emplace_back(p);
	}
	for (int i = 0; i != amount; i++) {
		std::unique_ptr<Thread> newThread(new Thread(_datas.at(i)));
		_threadPool.push_back(std::move(newThread));
	}
}

plz::ThreadPoolManager::~ThreadPoolManager()
{
	for (auto &it : _datas) {
		it.get()->lockItem();
		it.get()->getItem().setEnd();
		it.get()->unlockItem();
	}
	for (auto &it : _threadPool) {
		it.get()->getThread().join();
	}
}

int plz::ThreadPoolManager::getUsagePercentage()
{
	int used = 0;
	for (auto &it : _datas) {
		it.get()->lockItem();
		if (it.get()->getItem().getUse())
			used += 100;
		it.get()->unlockItem();
	}
	return static_cast<int>(used / _datas.size());
}

int plz::ThreadPoolManager::getIndexUnoccupied()
{
	int i = 0;

	for (auto &it : _datas) {
		it.get()->lockItem();
		if (!it.get()->getItem().getUse()) {
			it.get()->unlockItem();
			return i;
		}
		it.get()->unlockItem();
		i += 1;
	}
	return -1;
}

void plz::ThreadPoolManager::loop()
{
	MainData received;

	signal(SIGINT, sigHandler);
	while (!endG && !_end) {
		usleep(100);
		if (_messageQueue.receive(_id, received))
			manageRequest(received);
		pushFromWaitingList();
	}
}

void plz::ThreadPoolManager::manageRequest(MainData &data)
{
	if (data.asked.filename[0] != '\0')
		addCommand(data);
	pushFromWaitingList();
	sendData(data);
}

void plz::ThreadPoolManager::addCommand(plz::MainData &data)
{
	_inactive = false;
	_waitingList.push_back(data.asked);
}

void plz::ThreadPoolManager::sendData(plz::MainData &data)
{
	data.timeout = false;
	data.usePercentage = getUsagePercentage();
	data.waitingListState = getWaitingListState();
	if (data.usePercentage == 0 && data.waitingListState == 0 && _inactive == false) {
		_inactive = true;
		_timeInactive = static_cast<int>(time(nullptr));
	}
	if (time(nullptr) - _timeInactive > 5 && _inactive) {
		data.timeout = true;
		_end = true;
	}
	_messageQueue.send(_id + SHIFT_IN_OUT_MQ, data);
}

int plz::ThreadPoolManager::getWaitingListState()
{
	return static_cast<int>(_waitingList.size());
}

void plz::ThreadPoolManager::pushFromWaitingList()
{
	if (!_waitingList.empty()) {
		int index = getIndexUnoccupied();
		if (index != -1) {
			_datas.at(index).get()->lockItem();
			_datas.at(index).get()->getItem().setToDo(_waitingList.at(0));
			_datas.at(index).get()->getItem().setUse(true);
			_datas.at(index).get()->unlockItem();
			_waitingList.erase(_waitingList.begin());
		}
	}
}
