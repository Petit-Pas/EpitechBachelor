/*
** EPITECH PROJECT, 2018
** bsPlazza
** File description:
** Internal functions
*/
#include <iostream>
#include <cstring>
#include "ThreadData.hpp"

plz::ThreadData::ThreadData(int index) : _used(false), _index(index), _end(false)
{
}

plz::ThreadData::~ThreadData()
{
}

int plz::ThreadData::getIndex() const
{
	return _index;
}

void plz::ThreadData::setIndex(int input)
{
	_index = input;
}

plz::ThreadData::ThreadData(const ThreadData &old)
{
	_index = old.getIndex();
	_used = false;
	_end = false;
	memset(&_toDo, 0, sizeof(Task));
}

void plz::ThreadData::setEnd()
{
	_end = true;
}

bool plz::ThreadData::getEnd()
{
	return _end;
}

void plz::ThreadData::setUse(bool status)
{
	_used = status;
}

bool plz::ThreadData::getUse()
{
	return _used;
}

void plz::ThreadData::setToDo(plz::Task &task)
{
	memcpy(&_toDo, &task, sizeof(Task));
}

plz::Task &plz::ThreadData::getTask()
{
	return _toDo;
}
