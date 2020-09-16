/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** Internal functions
*/

#include <chrono>
#include <time.h>
#include <iostream>
#include "Log.hpp"

void Log::addLog(const char *fmt, ...)
{
	time_t theTime = time(nullptr);
	struct tm *aTime = localtime(&theTime);

	auto time = std::string("[" + std::to_string(aTime->tm_hour) + ":" + std::to_string(aTime->tm_min) + ":" +
		std::to_string(aTime->tm_sec) + "] ");
	auto newFmt = time + std::string(fmt);
	fmt = const_cast<char *>(newFmt.c_str());
	int old_size = Buf.size();

	va_list args;
	va_start(args, fmt);
	Buf.appendfv(fmt, args);
	va_end(args);
	for (int new_size = Buf.size(); old_size < new_size; old_size++)
		if (Buf[old_size] == '\n')
			LineOffsets.push_back(old_size);
	ScrollToBottom = true;
}

void Log::draw(const char *title, sf::Vector2i size, sf::Vector2i pos)
{
	ImGui::SetNextWindowSize(size);
	ImGui::SetNextWindowPos(pos);
	ImGui::Begin(title, nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);
	ImGui::SameLine();
	ImGui::SameLine();
	Filter.Draw("Filter", -100.0f);
	ImGui::Separator();
	ImGui::BeginChild("scrolling", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);
	if (Filter.IsActive()) {
		const char *buf_begin = Buf.begin();
		const char *line = buf_begin;
		for (int line_no = 0; line != nullptr; line_no++) {
			const char *line_end =
				(line_no < LineOffsets.Size) ? buf_begin + LineOffsets[line_no] : nullptr;
			if (Filter.PassFilter(line, line_end))
				ImGui::TextUnformatted(line, line_end);
			line = line_end && line_end[1] ? line_end + 1 : nullptr;
		}
	} else {
		ImGui::TextUnformatted(Buf.begin());
	}

	if (ScrollToBottom)
		ImGui::SetScrollHere(1.0f);
	ScrollToBottom = false;
	ImGui::EndChild();
	ImGui::End();
}