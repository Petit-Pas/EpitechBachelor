/*
** EPITECH PROJECT, 2018
** bsPlazza
** File description:
** Internal functions
*/
#ifndef BSPLAZZA_THREADDATA_HPP
#define BSPLAZZA_THREADDATA_HPP

#include "Plazza.hpp"
#include "MessageQueue.hpp"
#include "LockedItem.hpp"

namespace plz {
	class ThreadData {
	public:
		ThreadData(int index);

		ThreadData(const ThreadData &);

		~ThreadData();

		int getIndex() const;

		void setIndex(int input);

		bool getEnd();

		void setEnd();

		void setUse(bool status);

		bool getUse();

		void setToDo(plz::Task &task);

		plz::Task &getTask();

	private:
		bool _used;
		int _index;
		bool _end;
		plz::Task _toDo;
	};
}

#endif //BSPLAZZA_THREADDATA_HPP
