/*
** EPITECH PROJECT, 2021
** cpp_inidie_studio
** File description:
** internal functions
*/

#include <cmath>
#include "Wall.hpp"

Wall::Wall(const std::pair<float, float> &pos, int id) : AEntity(pos, Element::Type::HARDWALL, id)
{
}
