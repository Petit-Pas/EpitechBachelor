/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** Internal functions
*/

#include <iostream>
#include <imgui.h>
#include "Display.hpp"

plz::GUI::Display::Display(unsigned int width, unsigned int height, unsigned int framerate, std::string name) : _window(
	width, height, framerate, name), _taskManager(plz::GUI::Widget("Task Manager",
	ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse)), _commandManager(
	plz::GUI::Widget("Command Manager",
		ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse |
			ImGuiWindowFlags_NoScrollbar))
{
}

void plz::GUI::Display::displayButtons()
{
	_textValidate.clear();
	if (ImGui::Button("IP_ADDRESS", ImVec2(_window.getSize().x / 3, 20))) {
		std::string textString(_textString);
		textString += " IP_ADDRESS";
		_textValidate = textString;
	};
	if (ImGui::Button("PHONE_NUMBER", ImVec2(_window.getSize().x / 3, 20))) {
		std::string textString(_textString);
		textString += " PHONE_NUMBER";
		_textValidate = textString;
	};
	if (ImGui::Button("EMAIL_ADDRESS", ImVec2(_window.getSize().x / 3, 20))) {
		std::string textString(_textString);
		textString += " EMAIL_ADDRESS";
		_textValidate = textString;
	};
	if (ImGui::Button("Validate without end", ImVec2(_window.getSize().x / 3, 20))) {
		_textValidate = _textString;
	};
}

void plz::GUI::Display::handleInputs()
{
	static char text[1024 * 100] = "";
	ImGui::InputTextMultiline("", text, IM_ARRAYSIZE(text), ImVec2(-2.0f, _window.getSize().y - 150),
		ImGuiInputTextFlags_AllowTabInput);
	_textString = std::string(text);
}

std::string plz::GUI::Display::loop()
{
	_window.handleClose();
	_window.update();
	_commandManager.load(plz::GUI::Vector2Int(_window.getSize().x / 3, _window.getSize().y),
		plz::GUI::Vector2Int(0, 0));
	handleInputs();
	displayButtons();
	_commandManager.unload();
	_taskManager.load(plz::GUI::Vector2Int(_window.getSize().x / 3 * 2, _window.getSize().y),
		plz::GUI::Vector2Int(_window.getSize().x / 3, 0));
	displaySlaves();
	_taskManager.unload();
	_window.render();
	return _textValidate;
}

void plz::GUI::Display::displaySlaves()
{
	for (auto &it : _slaves)
		it.load(plz::GUI::Vector2Int(_window.getSize().x / 3 * 2 - 125, _window.getSize().y / 15));
}

bool plz::GUI::Display::isOpen()
{
	return _window.isOpen();
}

void plz::GUI::Display::updateSlave(int id, float value, int queue)
{
	for (auto &slave : _slaves) {
		if (slave.getId() == id) {
			slave.addValue(value);
			slave.setQueue(queue);
			return;
		}
	}
	PlotLine tmp(id);
	tmp.setQueue(queue);
	tmp.addValue(value);
	_slaves.push_back(tmp);
}

void plz::GUI::Display::setDeadSlave(int id)
{
	auto it = _slaves.begin();
	while (it != _slaves.end()) {
		if ((*it).getId() == id)
			_slaves.erase(it);
		else
			it++;
	}
}
