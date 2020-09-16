/*
** EPITECH PROJECT, 2021
** cpp_inidie_studio
** File description:
** internal functions
*/

#ifndef CPP_INIDIE_STUDIO_THREAD_HPP
# define CPP_INIDIE_STUDIO_THREAD_HPP

#include <thread>
#include "Packet.hpp"

template<typename T>
class Thread {
public:
	Thread() = default;
	Thread(T &toLaunch);
	std::thread &getThread();
private:
	std::thread _self;
};

template<typename T>
Thread<T>::Thread(T &toLaunch)
{
	_self = std::thread(&T::run, std::ref(toLaunch));
}

template<typename T>
std::thread &Thread<T>::getThread()
{
	return _self;
}

#endif //CPP_INIDIE_STUDIO_THREAD_HPP
