/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Created by vincent,
*/

#ifndef CPP_INDIE_STUDIO_STACK_HPP
#define CPP_INDIE_STUDIO_STACK_HPP

#include <atomic>
#include <condition_variable>
#include <mutex>
#include <utility>
#include <queue>
#include "Task.hpp"

class TaskQueue {

public:
	TaskQueue();
	~TaskQueue();

	void clear();
	void closeQueue();

	void addTask(Task &);
	bool getTask(Task &);

	size_t getSize() const;
	bool isEmpty() const;
	bool isValid() const;

private:
	std::atomic_bool _valid;
	mutable std::mutex _mutex;
	std::queue<Task> _queue;
	std::condition_variable _condition;
};

#endif //CPP_INDIE_STUDIO_STACK_HPP