/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** Internal functions
*/

#include <imgui-SFML.h>
#include "Window.hpp"
#include "Plazza.hpp"

plz::GUI::Win::Win(unsigned int width, unsigned int height, unsigned int framerate, std::string name) : _window(
	sf::VideoMode(width, height), name)
{
	_window.setFramerateLimit(framerate);
	ImGui::SFML::Init(_window);
}

plz::GUI::Win::~Win()
{
	ImGui::SFML::Shutdown();
}

bool plz::GUI::Win::isOpen()
{
	return _window.isOpen();
}

void plz::GUI::Win::handleClose()
{
	sf::Event event{};
	while (_window.pollEvent(event)) {
		ImGui::SFML::ProcessEvent(event);
		if (event.type == sf::Event::Closed) {
			_window.close();
			endG = true;
		}
	}
}

plz::GUI::Vector2Int plz::GUI::Win::getSize()
{
	return plz::GUI::Vector2Int(static_cast<int>(_window.getSize().x), static_cast<int>(_window.getSize().y));
}

void plz::GUI::Win::render()
{
	_window.clear();
	ImGui::SFML::Render(_window);
	_window.display();
}

void plz::GUI::Win::update()
{
	static sf::Clock deltaClock;

	ImGui::SFML::Update(_window, deltaClock.restart());
}
