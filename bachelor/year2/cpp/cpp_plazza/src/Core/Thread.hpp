/*
** EPITECH PROJECT, 2018
** bsPlazza
** File description:
** Internal functions
*/

#ifndef BSPLAZZA_THREAD_HPP
#define BSPLAZZA_THREAD_HPP

#include <unistd.h>
#include <thread>
#include <iostream>
#include "LockedItem.hpp"
#include "ThreadData.hpp"

namespace plz {
	class Thread {
	public:
		Thread(std::shared_ptr<LockedItem<ThreadData>> _threadData);
		~Thread();

		bool isAtEnd();
		void threadLoop();
		std::thread &getThread();
		void setUsed();
		void setUnused();
		int getId();
		void checkHasWork();
		void scrapIt(Task &data);
	private:
		std::shared_ptr<LockedItem<ThreadData>> _threadData;
		std::thread _self;
		MessageQueue _messageQueue;

	};
}

#endif //BSPLAZZA_THREAD_HPP
