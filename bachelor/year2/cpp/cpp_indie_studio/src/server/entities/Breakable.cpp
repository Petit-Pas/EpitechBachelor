/*
** EPITECH PROJECT, 2021
** cpp_inidie_studio
** File description:
** internal functions
*/

#include "Breakable.hpp"

Breakable::Breakable(const std::pair<float, float> &pos, int id) : AEntity(pos, Element::Type::SOFTWALL, id)
{
}
