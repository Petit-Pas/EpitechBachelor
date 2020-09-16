/*
** EPITECH PROJECT, 2021
** cpp_inidie_studio
** File description:
** internal functions
*/

#ifndef CPP_INIDIE_STUDIO_BREAKABLE_HPP
# define CPP_INIDIE_STUDIO_BREAKABLE_HPP

#include "AEntity.hpp"

class Breakable : public AEntity {
public:
	Breakable(const std::pair<float, float> &pos, int id);
};

#endif //CPP_INIDIE_STUDIO_BREAKABLE_HPP
