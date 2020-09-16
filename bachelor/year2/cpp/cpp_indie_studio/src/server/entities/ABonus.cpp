/*
** EPITECH PROJECT, 2021
** cpp_indie_studio
** File description:
** internal functions
*/

#include <cstdlib>
#include "ABonus.hpp"

ABonus::ABonus(const std::pair<float, float> &pos, int id, Element::Type kind) : AEntity(pos, kind, id)
{
}

void ABonus::apply(Player *)
{
}
