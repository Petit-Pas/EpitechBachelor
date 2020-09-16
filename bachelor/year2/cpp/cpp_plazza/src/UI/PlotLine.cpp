/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** Internal functions
*/

#include <cstdlib>
#include <cstdio>
#include <imgui.h>
#include <iostream>
#include "PlotLine.hpp"

void plz::GUI::PlotLine::addValue(float value)
{
	_values.push_back(value);
	if (_values.size() > 100)
		_values.pop_front();
}

void plz::GUI::PlotLine::load(const plz::GUI::Vector2Int &size)
{
	char buff[128];
	sprintf(buff, "Slave %05i\n%01i IN QUEUE", _id, _queue);
	float stock[100];
	int i = 0;
	for (auto &it : _values) {
		stock[i] = it;
		i++;
	}
	ImGui::PlotLines(buff, stock, static_cast<int>(_values.size()), 0, "", 0, 100,
		ImVec2(size.x, size.y));
}

plz::GUI::PlotLine::PlotLine(int id) : _id(id), _queue(0)
{
	for (int i = 0; i < 100; ++i) {
		_values.push_back(0);
	}
}

void plz::GUI::PlotLine::setQueue(int queue)
{
	_queue = queue;
}

int plz::GUI::PlotLine::getId() const
{
	return _id;
}

