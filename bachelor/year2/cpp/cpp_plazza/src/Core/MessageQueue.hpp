/*
** EPITECH PROJECT, 2021
** bsPlazza
** File description:
** internal functions
*/

#ifndef BSPLAZZA_MESSAGEQUEUE_HPP
# define BSPLAZZA_MESSAGEQUEUE_HPP

#include "Plazza.hpp"


//TODO: Créer une classe Communication qui utilise MQ

namespace plz {
	class ICommunication {
		virtual void send(int id, MainData &data) = 0;
		virtual bool receive(int id, MainData &data) = 0;
		virtual void send(const std::string &name) = 0;
		virtual bool receive(std::string &name) = 0;
	};
}

namespace plz {
	class MessageQueue : public ICommunication {
		typedef struct MessageMainData {
			long mtype;
			MainData data;
		} MessageMainData;

		typedef struct MessageNameDone {
			long mtype;
			char doneName[128];
		} MessageNameDone;

	public:
		MessageQueue(int token);
		MessageQueue(const MessageQueue &old) = default;
		~MessageQueue() = default;
		int getToken() const;
		int getMessageIndex() const;
		int getSemaphoreIndex() const;
		void send(int id, MainData &data) override;
		bool receive(int id, MainData &toFill) override;
		void send(const std::string &name) override;
		bool receive(std::string &name) override;
		void lock();
		void unlock();
		void destroySemaphore();

	private:
		int _token;
		int _messageIndex;
		int _semaphoreIndex;
	};
}

#endif //BSPLAZZA_MESSAGEQUEUE_HPP
