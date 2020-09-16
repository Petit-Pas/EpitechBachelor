/*
** EPITECH PROJECT, 2021
** cpp_arcade
** File description:
** Created by angevil,
*/

#include <iostream>
#include <cstring>
#include <caca.h>
#include "CacaDisplay.hpp"

ar::CacaDisplay::CacaDisplay() : _canvas(std::unique_ptr<caca::Canvas>(new caca::Canvas)),
	_event(std::unique_ptr<caca::Event>(new caca::Event)), _selected(0), _selectedItem(0)
{
	_canvas->setSize(240, 64);
	_caca = std::unique_ptr<caca::Caca>(new caca::Caca(_canvas.get()));
	_caca->setTitle("Arcade");
	_caca->setDisplayTime(200);
}

ar::CacaDisplay::~CacaDisplay()
{
}

ar::Event ar::CacaDisplay::getEvent(int &realKey)
{
	_caca->getEvent(caca::Event::CACA_EVENT_ANY, _event.get(), 0);
	realKey = 0;
	if (_event->getE().type == CACA_EVENT_RESIZE) {
		_canvas->Clear();
		return AR_RESIZE;
	}
	if (_event->getE().type == CACA_EVENT_KEY_PRESS) {
		realKey = _event->getE().data.key.ch;
		switch (realKey) {
		case CACA_KEY_UP:
			return AR_UP;
		case CACA_KEY_DOWN:
			return AR_DOWN;
		case CACA_KEY_RIGHT:
			return AR_RIGHT;
		case CACA_KEY_LEFT:
			return AR_LEFT;
		case 13:
			return AR_VALIDATE;
		case ' ':
			return AR_ACTION;
		case 'p':
			return AR_PAUSE;
		case '1':
			return AR_PREV_GAME;
		case '2':
			return AR_NEXT_GAME;
		case '3':
			return AR_PREV_GRAPH_LIB;
		case '4':
			return AR_NEXT_GRAPH_LIB;
		case 27:
			return AR_EXIT;
		case 'm':
			return AR_MENU;
		case 'r':
			return AR_RESTART;
		default:
			break;
		}
	}
	return AR_UNKNOWN;
}

bool ar::CacaDisplay::canHandleSprites()
{
	return false;
}

void ar::CacaDisplay::displayMap(Map &map)
{
	for (int i = 0; i < map.getHeight(); ++i) {
		for (int j = 0; j < map.getWidth() * 2 - 1; j += 2) {
			_canvas->setColorARGB(_colors.find(map[i][j / 2])->second, _colors.find(map[i][j / 2])->second);
			int x = ((_canvas->getWidth() - map.getWidth() * 2) / 2) + j;
			int y = ((_canvas->getHeight() - map.getHeight()) / 2) + i;
			if (!((x < 0 || x >= static_cast<int>(_canvas->getWidth())) &&
				(y < 0 || y >= static_cast<int>(_canvas->getHeight()))))
				_canvas->Printf(x, y, "%i%i", 1, 1);
			_canvas->setColorARGB(_colors.find(0)->second, _colors.find(1)->second);
		}
	}
}

void ar::CacaDisplay::displayGame(const ar::userInterface &UI, Map &map
)
{
	char szbuffer[200];
	snprintf(szbuffer, 200, " NAME : '%s'   HIGH SCORE : %i   TIME : %i   ", UI.username.c_str(), UI.score,
		UI.time);
	size_t size = strlen(szbuffer);
	if (_caca->getEvent(caca::Event::CACA_EVENT_RESIZE, _event.get(), 0))
		_canvas->Clear();
	_canvas->setColorARGB(_colors.find(0)->second, _colors.find(1)->second);
	_canvas->Printf(static_cast<int>((_canvas->getWidth() - size) / 2), (7) / 2,
		" NAME : '%s'   HIGH SCORE : %i   TIME : %i   ", UI.username.c_str(), UI.score, UI.time);
	displayMap(map);
	_caca->Display();
}

void ar::CacaDisplay::loadResources(const std::map<unsigned char, ar::colorVector> &map
)
{
	_colors = {};
	_canvas->Clear();
	int16_t colors = 0;
	for (auto &item : map) {
		colors = colors << 4;
		colors |= (char)15;
		colors = colors << 4;
		colors |= (char)((item.second.red / 255) * 15);
		colors = colors << 4;
		colors |= (char)((item.second.green / 255) * 15);
		colors = colors << 4;
		colors |= (char)((item.second.blue / 255) * 15);
		_colors.insert(std::pair<unsigned char, int16_t>(item.first, colors));
	}
	colors = static_cast<int16_t>(0xffffffff);
	_colors.insert(std::pair<unsigned char, int16_t>(0, colors));
	colors = static_cast<int16_t>(0xff000000);
	_colors.insert(std::pair<unsigned char, int16_t>(1, colors));
}

void ar::CacaDisplay::loadResources([[gnu::unused]] const std::string &filePath,
	const std::map<unsigned char, ar::spriteCoords> &
)
{
}

void ar::CacaDisplay::initMenu(const std::vector<std::string> &menuChoices, const std::string &menuName,
	const std::vector<std::string> &display
)
{
	_canvas->Clear();
	_canvas->setColorANSI(CACA_WHITE, CACA_BLACK);
	_choices = menuChoices;
	_menuName = menuName;
	_selectedItem = 0;
	_selected = 0;
	_graphicalLibraries = display;
}

void ar::CacaDisplay::displayUI(std::vector<ar::userInterface> dataArray
)
{
	if (_selectedItem != static_cast<int>(dataArray.size())) {
		char szbuffer[200];
		snprintf(szbuffer, 200, " NAME : '%s'   HIGH SCORE : %i   ",
			dataArray.at(_selectedItem).username.c_str(), dataArray.at(_selectedItem).score);
		size_t size = strlen(szbuffer);
		_canvas->Printf(static_cast<int>((_canvas->getWidth() - size) / 2), (15) / 2,
			" NAME : '%s'   HIGH SCORE : %i   ", dataArray.at(_selectedItem).username.c_str(),
			dataArray.at(_selectedItem).score);
	} else {
		_canvas->Printf(static_cast<int>((_canvas->getWidth() - 50) / 2), (_canvas->getHeight() - 15) / 2,
			" \t\t\t\t\t\t\t\t\t\t\t\t\t\t\t");
	}
	_canvas->Printf(static_cast<int>((_canvas->getWidth() - _menuName.size()) / 2), (15), "%s", _menuName.c_str());
}

void ar::CacaDisplay::handleMenuInput(ar::Event key, std::vector<ar::userInterface> dataArray
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

int ar::CacaDisplay::refreshMenu(const ar::Event &key, const std::vector<ar::userInterface> &dataArray
)
{
	handleMenuInput(key, dataArray);
	_canvas->Clear();
	displayUI(dataArray);
	int i = 0;
	for (auto &text : _choices) {
		if (_selected == i)
			_canvas->setColorANSI(CACA_BLACK, CACA_WHITE);
		_canvas->Printf(static_cast<int>((_canvas->getWidth() - strlen(text.c_str())) / 2),
			static_cast<int>((_canvas->getHeight() - _choices.size()) / 2 + i), "%s", text.c_str());
		_canvas->setColorANSI(CACA_WHITE, CACA_BLACK);
		i++;
	}
	i = 1;
	for (auto &text : _graphicalLibraries) {
		_canvas->Printf(static_cast<int>((_canvas->getWidth() - strlen(text.c_str()))),
			static_cast<int>((_canvas->getHeight()) - i), "%s", text.c_str());
		_canvas->setColorANSI(CACA_WHITE, CACA_BLACK);
		i++;
	}
	_caca->Display();
	return _selected;
}

void ar::CacaDisplay::refreshUsername(std::string &name, int realKey)
{
	int c = realKey;
	if (isalpha(c) && name.length() < 4)
		name += static_cast<char>(toupper(c));
	if ((c == CACA_KEY_BACKSPACE || c == 127) && !name.empty())
		name.pop_back();
}

void ar::CacaDisplay::destroyMenu()
{
	_choices.clear();
	_graphicalLibraries.clear();
	_canvas->Clear();
}

extern "C" ar::IDisplay *createDisplay()
{
	return new ar::CacaDisplay;
}

extern "C" void destroyDisplay(ar::IDisplay *Caca)
{
	delete Caca;
}
