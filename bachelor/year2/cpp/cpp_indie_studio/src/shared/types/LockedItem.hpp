/*
** EPITECH PROJECT, 2018
** indie_studio
** File description:
** Internal functions
*/
#ifndef INDIE_LOCKEDITEM_HPP
#define INDIE_LOCKEDITEM_HPP

#include <memory>
#include <mutex>
#include <iostream>

template<typename T>
class LockedItem {
public:
	LockedItem(T &input);
	LockedItem() = default;

	//LockedItem();

	//LockedItem(LockedItem &toCopy) = delete;

	//~LockedItem() = default;

	void lockItem();

	void unlockItem();

	int trylockItem();

	T &getItem();

private:
	std::mutex _mutex;
	T _myContained;
};

template<typename T>
LockedItem<T>::LockedItem(T &input)
	: _mutex(), _myContained(input)
{
}

template<typename T>
void LockedItem<T>::lockItem()
{
	_mutex.lock();
}

template<typename T>
void LockedItem<T>::unlockItem()
{
	_mutex.unlock();
}

template<typename T>
int LockedItem<T>::trylockItem()
{
	return _mutex.try_lock();
}

template<typename T>
T &LockedItem<T>::getItem()
{
	return _myContained;
}

/*template<typename T>
LockedItem<T>::LockedItem() : _mutex(), _myContained(T())
{
}*/

#endif //INDIE_LOCKEDITEM_HPP
