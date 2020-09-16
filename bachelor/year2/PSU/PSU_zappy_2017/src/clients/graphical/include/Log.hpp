/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** Internal functions
*/

#ifndef ZAPPY_LOG_HPP
# define ZAPPY_LOG_HPP

#include "imgui.hpp"

class Log {
public:
	void addLog(const char *fmt, ...)
	IM_FMTARGS(2);
	void draw(const char *title, sf::Vector2i size, sf::Vector2i pos);
private:
	ImGuiTextBuffer Buf;
	ImGuiTextFilter Filter;
	ImVector<int> LineOffsets;        // Index to lines offset
	bool ScrollToBottom = true;
};

#endif //ZAPPY_LOG_HPP
