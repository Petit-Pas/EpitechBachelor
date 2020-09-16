/*
** EPITECH PROJECT, 2021
** cpp_inidie_studio
** File description:
** internal functions
*/

#ifndef CPP_INIDIE_STUDIO_FIRE_HPP
# define CPP_INIDIE_STUDIO_FIRE_HPP

#include <chrono>
#include "AEntity.hpp"

class Fire : public AEntity {
public:
	Fire(const std::pair<float, float> &pos, int id);
	void update();
	bool isOver();
	bool canSpawnBonus();
	void canNowSpawnBonus();

private:
	std::chrono::steady_clock::time_point _tikTak;
	bool _over;
	bool _canSpawnBonus;
};

#endif //CPP_INIDIE_STUDIO_FIRE_HPP
