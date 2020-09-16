/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** Internal functions
*/

#include <imgui.h>
#include "Widget.hpp"

void plz::GUI::Widget::load(const plz::GUI::Vector2Int &size, const plz::GUI::Vector2Int &pos)
{
	ImGui::SetNextWindowSize(ImVec2(size.x, size.y));
	ImGui::SetNextWindowPos(ImVec2(pos.x, pos.y));
	ImGui::Begin(_name.c_str(), nullptr, _flags);
}

void plz::GUI::Widget::unload()
{
	ImGui::End();
}

plz::GUI::Widget::Widget(const std::string &name, int flags) : _name(name), _flags(flags)
{
}
