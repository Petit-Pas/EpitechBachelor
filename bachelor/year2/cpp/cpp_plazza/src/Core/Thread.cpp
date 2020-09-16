/*
** EPITECH PROJECT, 2018
** bsPlazza
** File description:
** Internal functions
*/
#include <cstring>
#include "Thread.hpp"
#include "ThreadData.hpp"
#include "ParserSlave.hpp"

plz::Thread::Thread(std::shared_ptr<LockedItem<ThreadData>> item) : _threadData(item), _messageQueue(13)
{
	_self = std::thread(&Thread::threadLoop, this);
}

void plz::Thread::threadLoop()
{
	while (!isAtEnd()) {
		checkHasWork();
		usleep(100);
	}
}

plz::Thread::~Thread()
{
}

bool plz::Thread::isAtEnd()
{
	bool result;

	_threadData.get()->lockItem();
	result = _threadData.get()->getItem().getEnd();
	_threadData.get()->unlockItem();
	return result;
}

std::thread &plz::Thread::getThread()
{
	return _self;
}

void plz::Thread::setUsed()
{
	_threadData.get()->lockItem();
	_threadData.get()->getItem().setUse(true);
	_threadData.get()->unlockItem();
}

void plz::Thread::setUnused()
{
	_threadData.get()->lockItem();
	_threadData.get()->getItem().setUse(false);
	_threadData.get()->unlockItem();
}

int plz::Thread::getId()
{
	int ret;

	_threadData.get()->lockItem();
	ret = _threadData.get()->getItem().getIndex();
	_threadData.get()->unlockItem();
	return ret;
}

void plz::Thread::checkHasWork()
{
	_threadData.get()->lockItem();
	if (_threadData.get()->getItem().getTask().filename[0] != 0) {
		Task data;
		data = _threadData.get()->getItem().getTask();
		_threadData.get()->unlockItem();
		scrapIt(data);
	}
	_threadData.get()->unlockItem();
}

void plz::Thread::scrapIt(plz::Task &data)
{
	ParserSlave parser(data);

	parser.startJob();
	_messageQueue.send(std::string(data.outFileName));
	_threadData.get()->lockItem();
	_threadData.get()->getItem().getTask().filename[0] = 0;
	_threadData.get()->getItem().getTask().outFileName[0] = 0;
	_threadData.get()->getItem().setUse(false);
	_threadData.get()->unlockItem();
}
