/*
** EPITECH PROJECT, 2021
** bsPlazza
** File description:
** internal functions
*/

#include <stdio.h>
#include <functional>
#include <thread>
#include <vector>
#include <map>
#include <unistd.h>
#include <csignal>
#include "LockedItem.hpp"
#include "ThreadData.hpp"
#include "Thread.hpp"
#include "ThreadPoolManager.hpp"
#include "Master.hpp"
#include "MasterGUI.hpp"

bool plz::endG = false;

static void sigHandler(__attribute__((unused)) int signum)
{
	plz::endG = true;
}

int main(int ac, char **av)
{
	signal(SIGINT, sigHandler);
	if (ac != 2) {
		std::cerr << "missing argument" << std::endl;
		return 84;
	}
	if (atoi(av[1]) < 1) {
		std::cerr << "invalid argument" << std::endl;
		return 84;
	}
	plz::GUI::MasterGUI master(atoi(av[1]), 640, 480, 30, "plazza");

	master.manageCmdLoop();
	return 0;
}
