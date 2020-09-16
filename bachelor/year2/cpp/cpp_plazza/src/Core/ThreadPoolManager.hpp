/*
** EPITECH PROJECT, 2018
** bsPlazza
** File description:
** Internal functions
*/
#ifndef BSPLAZZA_THREADPOOLMANAGER_HPP
#define BSPLAZZA_THREADPOOLMANAGER_HPP

#include <vector>
#include "Plazza.hpp"
#include "Thread.hpp"
#include "MessageQueue.hpp"

namespace plz {
	class ThreadPoolManager {
	public:
		ThreadPoolManager(int amount, int id);
		~ThreadPoolManager();

		int getUsagePercentage();
		int getIndexUnoccupied();
		void loop();
		void manageRequest(MainData &data);
		void addCommand(MainData &data);
		void sendData(MainData &data);
		int getWaitingListState();
		void pushFromWaitingList();

	private:
		int _id;
		std::vector<std::unique_ptr<Thread>> _threadPool;
		std::vector<std::shared_ptr<LockedItem<ThreadData>>> _datas;
		std::vector<Task> _waitingList;
		MessageQueue _messageQueue;
		bool _inactive;
		int _timeInactive;
		bool _end;
	};
}

#endif //BSPLAZZA_THREADPOOLMANAGER_HPP
