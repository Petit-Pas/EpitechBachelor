/*
** EPITECH PROJECT, 2021
** cpp_inidie_studio
** File description:
** internal functions
*/

#ifndef CPP_INIDIE_STUDIO_TIMEDOBJECT_HPP
# define CPP_INIDIE_STUDIO_TIMEDOBJECT_HPP

#include <chrono>

template<typename T>
class TimedObject {
public:
	TimedObject(T &object, int length);
	~TimedObject() = default;
	bool isOver();
	T &getItem();
private:
	T _contained;
	std::chrono::steady_clock::time_point _tikTak;
	int _length;
};

template<typename T>
TimedObject<T>::TimedObject(T &object, int length) : _contained(object), _tikTak(std::chrono::steady_clock::now()),
	_length(length)
{
}

template<typename T>
bool TimedObject<T>::isOver()
{
	const long diff = std::chrono::duration_cast<std::chrono::milliseconds>(
		std::chrono::steady_clock::now() - _tikTak).count();

	if (diff >= _length)
		return true;
	return false;
}

template<typename T>
T &TimedObject<T>::getItem()
{
	return _contained;
}

#endif //CPP_INIDIE_STUDIO_TIMEDOBJECT_HPP
