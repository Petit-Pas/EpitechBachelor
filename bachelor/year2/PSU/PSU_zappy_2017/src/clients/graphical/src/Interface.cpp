/*
** EPITECH PROJECT, 2018
** Graphical
** File description:
** Created by martin.van-elslande@epitech.eu,
*/

#include <algorithm>
#include <iostream>
#include "imgui-SFML.hpp"
#include "imgui.hpp"
#include "Resources.hpp"
#include "Interface.hpp"

Interface::Interface(const std::string &addr, int port) : _mapSize({-1, -1}),
	_tiles({}), _players({}), _teams({}), _timeUnit(0),
	_gameFinished(false), _winningTeam(""), _tileWidth(0),
	_tracker(_players),
	_backend(addr, port, _mapSize, _tiles, _players, _eggs, _incantations,
		_teams, _timeUnit, _gameFinished, _winningTeam, _tileWidth,
		_log),
	_window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Zappy"),
	_view(sf::FloatRect(0, 0, WIDTH, HEIGHT)), _zoomIdx(0),
	_showTracker(true), _showLog(true), _showHelp(true)
{
	_lastTileClicked = nullptr;
	_window.setFramerateLimit(60);
	_font.loadFromFile("resources/default.ttf");
	_clock.restart();
	_moveClock.restart();
	ImGui::SFML::Init(_window);
	ImGui::GetIO().IniFilename = nullptr;
}

Interface::~Interface()
{
	ImGui::SFML::Shutdown();
	_window.close();
}

void Interface::clickManager(const sf::Event::MouseButtonEvent &mouse)
{
	for (auto &tmp : _tiles) {
		if (tmp.second.hitbox.contains(_window.mapPixelToCoords(
			sf::Vector2i(mouse.x, mouse.y)))) {
			if (_lastTileClicked &&
				tmp.second.pos.x == _lastTileClicked->pos.x &&
				tmp.second.pos.y == _lastTileClicked->pos.y)
				_lastTileClicked = nullptr;
			else
				_lastTileClicked = std::make_unique<Tile>(
					tmp.second);
		}
	}
}

void Interface::simpleKeyManager(sf::Event &event)
{
	switch (event.key.code) {
	case sf::Keyboard::Escape:
		_window.close();
		break;
	case sf::Keyboard::Up:
		_view.move(0,
			-HEIGHT / (_mapSize.y + ((_mapSize.y / 4) * _zoomIdx)));
		break;
	case sf::Keyboard::Down:
		_view.move(0,
			HEIGHT / (_mapSize.y + ((_mapSize.y / 4) * _zoomIdx)));
		break;
	case sf::Keyboard::Right:
		_view.move(WIDTH / (_mapSize.x + ((_mapSize.x / 4) * _zoomIdx)),
			0);
		break;
	case sf::Keyboard::Left:
		_view.move(
			-WIDTH / (_mapSize.x + ((_mapSize.x / 4) * _zoomIdx)),
			0);
		break;
	case sf::Keyboard::F1:
		_showHelp = !_showHelp;
	default:
		break;
	}
}

void Interface::keyboardManager(sf::Event &event)
{
	simpleKeyManager(event);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
		switch (event.key.code) {
		case sf::Keyboard::L:
			_showLog = !_showLog;
			break;
		case sf::Keyboard::T:
			_showTracker = !_showTracker;
			break;
		case sf::Keyboard::R:
			_zoomIdx = 0;
			_view.setSize(WIDTH, HEIGHT);
			_view.setCenter(WIDTH / 2, HEIGHT / 2);
			break;
		case sf::Keyboard::I:
			if (_zoomIdx < 4) {
				_view.zoom(0.5f);
				_zoomIdx++;
			}
			break;
		case sf::Keyboard::O:
			if (_zoomIdx > 0) {
				_view.zoom(2.0f);
				_zoomIdx--;
			}
			break;
		default:
			break;
		}
	}
}

void Interface::eventManager()
{
	sf::Event event{};

	while (_window.pollEvent(event) && _window.isOpen()) {
		ImGui::SFML::ProcessEvent(event);
		if (event.type == sf::Event::Closed)
			_window.close();
		else if (event.type == sf::Event::MouseButtonPressed)
			clickManager(event.mouseButton);
		else if (event.type == sf::Event::Resized)
			_view.setSize(WIDTH + (WIDTH / event.size.width),
				HEIGHT + (HEIGHT / event.size.height));
		else if (event.type == sf::Event::KeyPressed) {
			keyboardManager(event);
		}
	}
}

void Interface::dumpResourcesOnTile(const std::map<int, Resource> &resources)
{
	if (ImGui::TreeNode(std::string(
		"Resources " + std::to_string(_lastTileClicked->pos.x) +
			std::to_string(_lastTileClicked->pos.y)).c_str(),
		"Resources")) {
		ImGui::BulletText("%i FOOD", resources.at(0).quantity);
		ImGui::BulletText("%i LINEMATE", resources.at(1).quantity);
		ImGui::BulletText("%i DERAUMERE", resources.at(2).quantity);
		ImGui::BulletText("%i SIBUR", resources.at(3).quantity);
		ImGui::BulletText("%i MENDIANE", resources.at(4).quantity);
		ImGui::BulletText("%i PHIRAS", resources.at(5).quantity);
		ImGui::BulletText("%i THYSTAME", resources.at(6).quantity);
		ImGui::TreePop();
	}
}

void Interface::dumpPlayerOnTile(const Tile *tile)
{
	if (ImGui::TreeNode(std::string(
		"Teams " + std::to_string(_lastTileClicked->pos.x) +
			std::to_string(_lastTileClicked->pos.y)).c_str(),
		"Teams")) {
		for (const auto &team : _teams) {
			if (ImGui::TreeNode(team.c_str())) {
				for (const auto &player : _players) {
					if (player.second->getPos() ==
						tile->pos &&
						player.second->getTeamName() ==
							team) {
						player.second->dump();
					}
				}
				ImGui::TreePop();
			}
		}
		ImGui::TreePop();
	}
}

void Interface::dumpEggOnTile(const Tile *tile)
{
	if (ImGui::TreeNode(std::string(
		"Eggs " + std::to_string(_lastTileClicked->pos.x) +
			std::to_string(_lastTileClicked->pos.y)).c_str(),
		"Eggs")) {
		for (const auto &team : _teams) {
			if (ImGui::TreeNode(team.c_str())) {
				for (const auto &egg : _eggs) {
					if (egg.second.pos == tile->pos &&
						egg.second.teamName == team) {
						if (ImGui::TreeNode(
							std::to_string(
								egg.second.id).c_str(),
							"Egg %i",
							egg.second.id)) {
							ImGui::TreePop();
						}
					}
				}
				ImGui::TreePop();
			}
		}
		ImGui::TreePop();
	}
}

void Interface::displayManager()
{
	_window.clear();
	if (!_backend.isGameFinished()) {
		_window.setView(_view);
		for (const auto &tmp : _tiles) {
			_window.draw(tmp.second.shape);
			for (const auto &tmp_resource : tmp.second.resources) {
				if (tmp_resource.second.quantity > 0)
					_window.draw(tmp_resource.second.shape);
			}
		}
		if (_moveClock.getElapsedTime().asMicroseconds() * 1000 >=
			_backend.getTimeUnit()) {
			for (auto &tmp : _players)
				tmp.second.get()->stepMove();
			_moveClock.restart();
		}
		for (const auto &tmp : _eggs)
			_window.draw(tmp.second.shape);
		for (const auto &tmp : _players)
			_window.draw(tmp.second->getShape());

		ImGui::SFML::Update(_window, _clock.restart());

		if (_lastTileClicked) {
			ImGui::SetNextWindowSize(sf::Vector2i(
				static_cast<int>(_window.getSize().x / 2.30),
				_window.getSize().y / 3));
			ImGui::SetNextWindowPos(sf::Vector2i(
				static_cast<int>(_window.getSize().x -
					(_window.getSize().x / 2.30)), 0));
			ImGui::Begin("Tile Content", nullptr,
				ImGuiWindowFlags_NoResize |
					ImGuiWindowFlags_NoMove |
					ImGuiWindowFlags_NoCollapse);
			ImGui::BulletText("Position (%i;%i)",
				_lastTileClicked->pos.x,
				_lastTileClicked->pos.y);
			dumpResourcesOnTile(_lastTileClicked->resources);
			dumpPlayerOnTile(_lastTileClicked.get());
			dumpEggOnTile(_lastTileClicked.get());
			ImGui::End();
		}
		if (_showLog)
			_log.draw("Log", sf::Vector2i(
				static_cast<int>(_window.getSize().x / 2.30),
				_window.getSize().y / 3), sf::Vector2i(
				static_cast<int>(_window.getSize().x -
					(_window.getSize().x / 2.30)),
				(_window.getSize().y / 3) * 2));
		if (_showTracker)
			_tracker.draw("Player Tracked", sf::Vector2i(
				static_cast<int>(_window.getSize().x / 2.30),
				_window.getSize().y / 3), sf::Vector2i(
				static_cast<int>(_window.getSize().x -
					(_window.getSize().x / 2.30)),
				(_window.getSize().y / 3) * 1));
		if (_showHelp) {
			ImGui::SetNextWindowSize(
				sf::Vector2i(_window.getSize().x,
					_window.getSize().y));
			ImGui::SetNextWindowPos(sf::Vector2i(0, 0));
			ImGui::Begin("HELP", nullptr,
				ImGuiWindowFlags_NoResize |
					ImGuiWindowFlags_NoMove |
					ImGuiWindowFlags_NoCollapse);
			ImGui::BulletText("HELP");
			ImGui::BulletText("F1      : Show this window");
			ImGui::BulletText("CTRL + L: Toggle Log window");
			ImGui::BulletText("CTRL + T: Toggle Tracker window");
			ImGui::BulletText("CTRL + O: Zoom out on the map");
			ImGui::BulletText("CTRL + I: Zoom in on the map");
			ImGui::BulletText("CTRL + R: Reset position");
			ImGui::BulletText("Arrows  : Navigate on the map");
			ImGui::End();
		}
		ImGui::SFML::Render(_window);
	} else {
		/* Game finished display prototype */
		sf::Text text("Winner : " + _backend.getWinningTeam(), _font,
			48);

		text.setFillColor(sf::Color::White);
		text.setOrigin(text.getGlobalBounds().width / 2,
			text.getGlobalBounds().height / 2);
		text.setPosition(WIDTH / 2, HEIGHT / 2);
		_window.clear(sf::Color::Red);
		_window.draw(text);
		_window.display();
	}
	_window.display();
}

void Interface::run()
{
	while (_window.isOpen()) {
		std::string msg;

		eventManager();
		_backend.refresh();
		if (!_backend.isMapSet())
			continue;
		displayManager();
	}
}
