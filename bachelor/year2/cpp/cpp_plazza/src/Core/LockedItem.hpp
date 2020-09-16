/*
** EPITECH PROJECT, 2018
** bsPlazza
** File description:
** Internal functions
*/
#ifndef BSPLAZZA_LOCKEDITEM_HPP
#define BSPLAZZA_LOCKEDITEM_HPP

#include <memory>
#include <mutex>

namespace plz {
	template<typename T>
	class LockedItem {
	public:
		LockedItem(T &input);

		LockedItem();

		~LockedItem() = default;

		void lockItem();

		void unlockItem();

		int trylockItem();

		T &getItem();

	private:
		std::unique_ptr<std::mutex> _mutex;
		T _value;
	};

	template<typename T>
	LockedItem<T>::LockedItem(T &input)
		: _mutex(std::unique_ptr<std::mutex>(new std::mutex)), _value(T(input))
	{
	}

	template<typename T>
	void LockedItem<T>::lockItem()
	{
		_mutex.get()->lock();
	}

	template<typename T>
	void LockedItem<T>::unlockItem()
	{
		_mutex.get()->unlock();
	}

	template<typename T>
	int LockedItem<T>::trylockItem()
	{
		return _mutex.get()->try_lock();
	}

	template<typename T>
	T &LockedItem<T>::getItem()
	{
		return _value;
	}
}
#endif //BSPLAZZA_LOCKEDITEM_HPP
