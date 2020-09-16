/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Created by vincent,
*/

#include <iostream>
#include "TaskQueue.hpp"

TaskQueue::TaskQueue() : _valid(true)
{
}

TaskQueue::~TaskQueue()
{
	closeQueue();
}

void TaskQueue::clear()
{
	std::lock_guard<std::mutex> lock(_mutex);
	while (!_queue.empty()) {
		_queue.pop();
	}
}

void TaskQueue::closeQueue()
{
	std::lock_guard<std::mutex> lock(_mutex);
	_valid = false;
}

void TaskQueue::addTask(Task &task)
{
	std::lock_guard<std::mutex> lock(_mutex);

	_queue.push(task);
}

bool TaskQueue::getTask(Task &task)
{
	if (!_valid || _queue.empty())
		return false;
	std::lock_guard<std::mutex> lock(_mutex);
	auto &newTask = _queue.front();
	task.task = newTask.task;
	task.type = newTask.type;
	task.state = newTask.state;
	task.pos.X = newTask.pos.X;
	task.pos.Y = newTask.pos.Y;
	task.uniqueId = newTask.uniqueId;
	task.direction = newTask.direction;
	_queue.pop();
	return true;
}

size_t TaskQueue::getSize() const
{
	return _queue.size();
}

bool TaskQueue::isEmpty() const
{
	std::lock_guard<std::mutex> lock(_mutex);
	return _queue.empty();
}

bool TaskQueue::isValid() const
{
	std::lock_guard<std::mutex> lock(_mutex);
	return _valid;
}

