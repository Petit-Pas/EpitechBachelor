/*
** EPITECH PROJECT, 2021
** cpp_arcade
** File description:
** Created by angevil,
*/

#include <iostream>
#include <cstring>
#include <Map.hpp>
#include <cmath>
#include "SFMLDisplay.hpp"

ar::SFMLDisplay::SFMLDisplay() : _window(sf::VideoMode(1920, 1080), "Arcade")
{
	if (!_font.loadFromFile("./resources/arcade2.ttf"))
		throw std::runtime_error("Failed to load the font");
	_score = sf::Text("", _font, 30);
	_score.setPosition(_window.getSize().x / 2 - 325, 30);
	_time = sf::Text("", _font, 30);
	_time.setPosition(50, 30);
	_username = sf::Text("", _font, 30);
	_username.setPosition(_window.getSize().x / 2 + 200, 30);
	_selected = 0;
}

ar::SFMLDisplay::~SFMLDisplay()
{
	_window.close();
}

ar::Event ar::SFMLDisplay::getEvent(int &realKey)
{
	static sf::Clock clock;
	sf::Event event{};
	realKey = 0;
	while (_window.pollEvent(event)) {
		if (event.type == sf::Event::TextEntered ||
			(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::BackSpace))
			realKey = event.key.code;
		if (event.type == sf::Event::Closed)
			return AR_EXIT;
		if (event.type == sf::Event::KeyPressed) {
			int key = event.key.code;
			switch (key) {
			case sf::Keyboard::Up:
				return AR_UP;
			case sf::Keyboard::Down:
				return AR_DOWN;
			case sf::Keyboard::Right:
				return AR_RIGHT;
			case sf::Keyboard::Left:
				return AR_LEFT;
			case sf::Keyboard::Space:
				return AR_ACTION;
			case sf::Keyboard::P:
				return AR_PAUSE;
			case sf::Keyboard::Num1:
				return AR_PREV_GAME;
			case sf::Keyboard::Num2:
				return AR_NEXT_GAME;
			case sf::Keyboard::Num3:
				return AR_PREV_GRAPH_LIB;
			case sf::Keyboard::Num4:
				return AR_NEXT_GRAPH_LIB;
			case 51:
				return AR_NEXT_GRAPH_LIB;
			case sf::Keyboard::Return:
				return AR_VALIDATE;
			case sf::Keyboard::Escape:
				return AR_EXIT;
			case sf::Keyboard::M:
				return AR_MENU;
			case sf::Keyboard::R:
				return AR_RESTART;
			default:
				return AR_UNKNOWN;
			}
		}
		if (event.type == sf::Event::Resized) {
			_window.setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
			return AR_RESIZE;
		}
	}
	clock.restart();
	return AR_UNKNOWN;
}

bool ar::SFMLDisplay::canHandleSprites()
{
	return true;
}

float ar::SFMLDisplay::getPixelFactorMap(Map &map)
{
	float pixelFactorMap = 50 / static_cast<float>(map.getHeight());
	float pixelFactor = ((static_cast<float>(_window.getSize().y) / 1025));
	if (pixelFactor > ((static_cast<float>(_window.getSize().x) / 1920)))
		pixelFactor = ((static_cast<float>(_window.getSize().x) / 1920));
	return pixelFactor * pixelFactorMap;
}

float ar::SFMLDisplay::getPixelFactor()
{
	float pixelFactor = ((static_cast<float>(_window.getSize().y) / 1025));
	if (pixelFactor > ((static_cast<float>(_window.getSize().x) / 1920)))
		pixelFactor = ((static_cast<float>(_window.getSize().x) / 1920));
	return pixelFactor;
}

void ar::SFMLDisplay::displayGame(const ar::userInterface &UI, Map &map
)
{
	_window.clear();
	_username.setString("USERNAME \n" + UI.username);
	_score.setString("SCORE \n" + std::to_string(UI.score));
	_time.setString("TIME \n" + std::to_string(UI.time));
	_time.setPosition((_window.getSize().x / 6) * 1 - (_time.getLocalBounds().width / 2), 30);
	_username.setPosition((_window.getSize().x / 6) * 3 - (_username.getLocalBounds().width / 2), 30);
	_score.setPosition((_window.getSize().x / 6) * 5 - (_score.getLocalBounds().width / 2), 30);

	float pixelFactor = getPixelFactorMap(map);

	int pixelSize = pixelFactor * _sprites.at(2).coords.height;
	_time.setCharacterSize(static_cast<unsigned int>(getPixelFactor() * 25));
	_username.setCharacterSize(static_cast<unsigned int>(getPixelFactor() * 25));
	_score.setCharacterSize(static_cast<unsigned int>(getPixelFactor() * 25));
	displayMap(map, pixelSize, pixelFactor);
	_window.draw(_username);
	_window.draw(_score);
	_window.draw(_time);
	_window.display();
}

void ar::SFMLDisplay::loadResources(const std::map<unsigned char, ar::colorVector> &)
{
}

void ar::SFMLDisplay::initMenu(const std::vector<std::string> &menuChoices, const std::string &menuName,
	const std::vector<std::string> &display
)
{
	int i = 0;
	_selected = 0;
	_selectedItem = 0;
	for (auto &item : menuChoices) {
		sf::Text text(item, _font, 50);
		text.setPosition(((_window.getSize().x - text.getLocalBounds().width) / 2),
			i * 60 + ((_window.getSize().y - text.getLocalBounds().height - 200) / 2));
		text.setStyle(1);
		text.setFillColor(sf::Color(255, 255, 255, 170));
		text.setOutlineThickness(3);
		text.setOutlineColor(sf::Color(0, 0, 0, 170));
		_choices.push_back(text);
		i++;
	}
	i = 0;
	for (auto &item : display) {
		sf::Text text(item, _font, 10);
		text.setPosition(((_window.getSize().x - text.getLocalBounds().width) / 2),
			i * 10 + ((_window.getSize().y - text.getLocalBounds().height - 300) / 2));
		text.setFillColor(sf::Color(255, 255, 255, 170));
		text.setOutlineThickness(1);
		text.setOutlineColor(sf::Color(0, 0, 0, 170));
		_graphicalLibraries.push_back(text);
		i++;
	}

	_menuName = sf::Text(menuName, _font, 50);
	_menuName.setPosition(((_window.getSize().x - _menuName.getLocalBounds().width) / 2),
		((_window.getSize().y - _menuName.getLocalBounds().height - 400) / 2));
	_menuName.setStyle(1);
	_menuName.setFillColor(sf::Color(255, 255, 255, 255));
	_menuName.setOutlineColor(sf::Color(255, 0, 0, 230));
	_menuName.setOutlineThickness(3);
}

void ar::SFMLDisplay::handleMenuInput(ar::Event key, std::vector<ar::userInterface> dataArray
)
{
	switch (key) {
	case AR_UP:
		if (_selectedItem > 0 && _selected == _selectedItem)
			_selectedItem -= 1;
		if (_selected > 0)
			_selected -= 1;
		break;
	case AR_DOWN:
		if (_selectedItem < static_cast<int>(dataArray.size() - 1))
			_selectedItem += 1;
		if (_selected < static_cast<int>(dataArray.size()))
			_selected += 1;
		break;
	default:
		break;
	}
}

int ar::SFMLDisplay::refreshMenu(const ar::Event &key, const std::vector<ar::userInterface> &dataArray
)
{
	handleMenuInput(key, dataArray);
	_window.clear();
	_username.setString("USERNAME \n" + dataArray.at(_selectedItem).username);
	_score.setString("SCORE \n" + std::to_string(dataArray.at(_selectedItem).score));
	_username.setPosition((_window.getSize().x / 6) * 2 - (_username.getLocalBounds().width / 2), 30);
	_score.setPosition((_window.getSize().x / 6) * 4 - (_score.getLocalBounds().width / 2), 30);
	_menuName.setPosition(((_window.getSize().x - _menuName.getLocalBounds().width) / 2),
		((_window.getSize().y - _menuName.getLocalBounds().height - 400) / 2));
	int i = 0;
	for (auto &text : _choices) {
		sf::Text tmp(text);
		if (i == _selected) {
			tmp.setFillColor(sf::Color(255, 255, 255, 255));
			tmp.setOutlineColor(sf::Color(255, 0, 0, 230));
		}
		tmp.setPosition(((_window.getSize().x - text.getLocalBounds().width) / 2),
			i * 60 + ((_window.getSize().y - text.getLocalBounds().height - 200) / 2));
		_window.draw(tmp);
		i++;
	}
	for (auto &text : _graphicalLibraries) {
		sf::Text tmp(text);
		if (i == _selected) {
			tmp.setFillColor(sf::Color(255, 255, 255, 255));
			tmp.setOutlineColor(sf::Color(255, 0, 0, 230));
		}
		text.setPosition(((_window.getSize().x - text.getLocalBounds().width)),
			((_window.getSize().y - text.getLocalBounds().height)) - i * 10);
		_window.draw(tmp);
		i++;
	}
	if (_selected != static_cast<int>(dataArray.size())) {
		_window.draw(_username);
		_window.draw(_score);
	}
	_window.draw(_menuName);
	_window.display();
	return _selected;
}

void ar::SFMLDisplay::refreshUsername(std::string &name, __attribute__((unused)) int realKey
)
{
	int c = realKey;
	if (isalpha(c) && name.length() < 4)
		name += static_cast<char>(toupper(c));
	if ((c == sf::Keyboard::BackSpace || c == 127) && !name.empty())
		name.pop_back();
}

void ar::SFMLDisplay::destroyMenu()
{
	_choices.clear();
	_graphicalLibraries.clear();
}

void ar::SFMLDisplay::loadResources(const std::string &filePath,
	const std::map<unsigned char, ar::spriteCoords> &sprites
)
{
	_sprites = {};
	for (auto &it : sprites) {
		ar::SFMLDisplay::Sprite sprite = ar::SFMLDisplay::Sprite();
		sprite.texture.loadFromFile(filePath);
		sprite.coords = it.second;
		_sprites.insert(std::pair<unsigned char, ar::SFMLDisplay::Sprite>(it.first, sprite));
	}
}

void ar::SFMLDisplay::displayMap(Map &map, int pixelSize, float pixelFactor
)
{
	for (int i = 0; i < map.getHeight(); ++i) {
		for (int j = 0; j < map.getWidth(); ++j) {
			float y = static_cast<float >((_window.getSize().x - map.getWidth() * pixelSize * 0.250 * 64 /
				static_cast<float>(_sprites.at(2).coords.width)) / 2 +
				j * pixelSize * 0.250 * 64 / static_cast<float>(_sprites.at(2).coords.width));
			float x = static_cast<float >((_window.getSize().y - map.getHeight() * pixelSize * 0.250 * 64 /
				static_cast<float>(_sprites.at(2).coords.width)) / 2 +
				i * pixelSize * 0.250 * 64 / static_cast<float>(_sprites.at(2).coords.width));
			setSpriteAttr(map[i][j], pixelFactor);
			setSpriteAttr(2, pixelFactor);
			_sprites.at(2).sprite.setPosition(std::ceil(y), std::ceil(x));
			_sprites.at(map[i][j]).sprite.setPosition(std::ceil(y), std::ceil(x));
			_window.draw(_sprites.at(2).sprite);
			_window.draw(_sprites.at(map[i][j]).sprite);
		}
	}
}

void ar::SFMLDisplay::setSpriteAttr(int sprite, float pixelFactor)
{

	_sprites.at(sprite).sprite.setTexture(_sprites.at(sprite).texture);
	_sprites.at(sprite).sprite.setTextureRect(
		sf::IntRect(_sprites.at(sprite).coords.x, _sprites.at(sprite).coords.y,
			_sprites.at(sprite).coords.height, _sprites.at(sprite).coords.width));
	float scale = std::ceil(static_cast<float>(std::ceil((0.25 * pixelFactor) * 100) / 100 * 64 /
		static_cast<float>(_sprites.at(2).coords.width)) * 100) / 100;
	_sprites.at(sprite).sprite.setScale(scale, scale);
}

extern "C" ar::IDisplay *createDisplay()
{
	return new ar::SFMLDisplay;
}

extern "C" void destroyDisplay(ar::IDisplay *sfml)
{
	delete sfml;
}
