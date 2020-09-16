/*
** EPITECH PROJECT, 2021
** cpp_inidie_studio
** File description:
** internal functions
*/

#ifndef CPP_INIDIE_STUDIO_WALL_HPP
# define CPP_INIDIE_STUDIO_WALL_HPP

#include "AEntity.hpp"

class Wall : public AEntity {
public:
	Wall(const std::pair<float, float> &pos, int id);
};

#endif //CPP_INIDIE_STUDIO_WALL_HPP
