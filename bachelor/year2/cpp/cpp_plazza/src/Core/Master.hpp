/*
** EPITECH PROJECT, 2021
** bsPlazza
** File description:
** internal functions
*/

#ifndef BSPLAZZA_MASTER_HPP
# define BSPLAZZA_MASTER_HPP

#include "LockedItem.hpp"
#include "MessageQueue.hpp"
#include "ThreadPoolManager.hpp"
#include "ParserMaster.hpp"

//TODO: Create a slave class before ThreadPool

namespace plz {
	class Master {
		typedef struct threadPool {
			int id;
			plz::MainData data;
			int pid;
		} threadPool;

	public:
		explicit Master(int nbThreads);
		virtual ~Master();
		int requestReceiver();
		virtual void manageCmdLoop();
		void setOutfileName(Task &task);
		virtual void sendCommandList(std::vector<plz::Task> toSend);
		void sendCommand(plz::Task);
		int getIndexFreeSlave();
		void refreshSlavesData();
		virtual void eraseFromSlaves(int id);
		threadPool getNewSlave();
		void appendToPendingTasks(Task &task);
		bool isPendingEmpty();
		void removeFromPending(const std::string &);
	protected:
		std::shared_ptr<LockedItem<MessageQueue>> _messageQueue;
		std::shared_ptr<LockedItem<MessageQueue>> _messageQueueDone;
		std::vector<threadPool> _slaves;
		std::thread _requestReceiver;
		int _amountThreads;
		ParserMaster _parser;
		std::shared_ptr<plz::LockedItem<std::vector<plz::Task>>> _pendingTasks;
		int _newIdMQ;
	};
}

#endif //BSPLAZZA_MASTER_HPP
