/*
** EPITECH PROJECT, 2021
** bsPlazza
** File description:
** internal functions
*/

#include <sys/msg.h>
#include <sys/shm.h>
#include <system_error>
#include <sys/sem.h>
#include <iostream>
#include <strings.h>
#include <cstring>
#include <unistd.h>
#include "MessageQueue.hpp"

plz::MessageQueue::MessageQueue(int token) : _token(token)
{
	_messageIndex = msgget(_token, SHM_R | SHM_W);
	if (_messageIndex == -1) {
		_messageIndex = msgget(_token, IPC_CREAT | SHM_R | SHM_W);
		_semaphoreIndex = semget(_token, 1, IPC_CREAT | SHM_R | SHM_W);
		semctl(_semaphoreIndex, 0, SETVAL, 1);
	} else {
		_semaphoreIndex = semget(_token, 1, SHM_R | SHM_W);
	}
}

int plz::MessageQueue::getToken() const
{
	return _token;
}

int plz::MessageQueue::getMessageIndex() const
{
	return _messageIndex;
}

void plz::MessageQueue::send(int id, MainData &data)
{
	MessageMainData toSend;

	bzero(&toSend, sizeof(MessageMainData));
	toSend.mtype = id;
	memcpy(&toSend.data, (void *)&data, sizeof(MainData));
	lock();
	while (msgsnd(_messageIndex, &toSend, sizeof(MessageMainData), static_cast<int>(toSend.mtype | IPC_NOWAIT)) ==
		-1) {
		unlock();
		usleep(100);
		lock();
	}
	unlock();
}

bool plz::MessageQueue::receive(int id, MainData &data)
{
	ssize_t ret;
	MessageMainData toRecv;

	bzero(&toRecv, sizeof(MessageMainData));
	toRecv.mtype = id;
	lock();
	ret = msgrcv(_messageIndex, &toRecv, sizeof(MessageMainData), id, IPC_NOWAIT);
	unlock();
	data = toRecv.data;
	if (ret > 0) {
		return true;
	}
	return false;
}

void plz::MessageQueue::lock()
{
	struct sembuf occup{};

	bzero(&occup, sizeof(struct sembuf));
	occup.sem_num = 0;
	occup.sem_flg = 0;
	occup.sem_op = -1;
	semop(_semaphoreIndex, &occup, 1);
}

void plz::MessageQueue::unlock()
{
	struct sembuf occup{};

	bzero(&occup, sizeof(struct sembuf));
	occup.sem_num = 0;
	occup.sem_flg = 0;
	occup.sem_op = 1;
	semop(_semaphoreIndex, &occup, 1);
}

int plz::MessageQueue::getSemaphoreIndex() const
{
	return _semaphoreIndex;
}

void plz::MessageQueue::destroySemaphore()
{
	semctl(_semaphoreIndex, 1, IPC_RMID);
}

void plz::MessageQueue::send(const std::string &name)
{
	MessageNameDone toSend;

	bzero(&toSend, sizeof(MessageNameDone));
	toSend.mtype = ID_DONE_FILE_MQ;
	memcpy(&toSend.doneName, name.c_str(), name.length());
	lock();
	while (msgsnd(_messageIndex, &toSend, sizeof(MessageNameDone), static_cast<int>(toSend.mtype | IPC_NOWAIT)) ==
		-1) {
		unlock();
		usleep(100);
		lock();
	}
	unlock();
}

bool plz::MessageQueue::receive(std::string &fileName)
{
	ssize_t ret;
	MessageNameDone toRecv;

	bzero(&toRecv, sizeof(MessageNameDone));
	toRecv.mtype = ID_DONE_FILE_MQ;
	lock();
	ret = msgrcv(_messageIndex, &toRecv, sizeof(MessageMainData), ID_DONE_FILE_MQ, IPC_NOWAIT);
	unlock();
	fileName = toRecv.doneName;
	if (ret > 0)
		return true;
	return false;
}
