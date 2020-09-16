/*
** EPITECH PROJECT, 2021
** cpp_arcade
** File description:
** Created by angevil,
*/

#include <iostream>
#include <cstring>
#include "NCursesDisplay.hpp"

ar::NCurseDisplay::NCurseDisplay()
{
	initscr();
	start_color();
	cbreak();
	curs_set(0);
	noecho();
	timeout(0);
	keypad(stdscr, TRUE);
	init_color(0, 0, 0, 0);
	init_color(1, 1000, 1000, 1000);
	init_pair(0, 0, 0);
	init_pair(1, 1, 0);
}

ar::NCurseDisplay::~NCurseDisplay()
{
	endwin();
}

ar::Event ar::NCurseDisplay::getEvent(int &realKey)
{
	int c = getch();
	realKey = c;
	switch (c) {
	case KEY_RESIZE:
		clear();
		return AR_RESIZE;
	case KEY_UP:
		return AR_UP;
	case KEY_DOWN:
		return AR_DOWN;
	case KEY_RIGHT:
		return AR_RIGHT;
	case KEY_LEFT:
		return AR_LEFT;
	case 10:
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
		clear();
		return AR_EXIT;
	case 'm':
		clear();
		return AR_MENU;
	case 'r':
		return AR_RESTART;
	default:
		break;
	}
	return AR_UNKNOWN;
}

bool ar::NCurseDisplay::canHandleSprites()
{
	return false;
}

void ar::NCurseDisplay::displayGame(const ar::userInterface &UI, Map &map
)
{
	char szbuffer[200];
	snprintf(szbuffer, 200, " NAME : '%s'   HIGH SCORE : %i   TIME : %i   ", UI.username.c_str(), UI.score,
		UI.time);
	size_t size = strlen(szbuffer);
	attron(COLOR_PAIR(1));
	mvprintw(1, static_cast<int>((COLS - size) / 2), " NAME : '%s'   HIGH SCORE : %i   TIME : %i   ",
		UI.username.c_str(), UI.score, UI.time);
	attroff(COLOR_PAIR(1));
	displayMap(map);
}

void ar::NCurseDisplay::displayMap(Map &map)
{
	for (int i = 0; i < map.getHeight(); ++i) {
		for (int j = 0; j < map.getWidth() * 2 - 1; j += 2) {
			attron(COLOR_PAIR(map[i][j / 2]));
			int x = ((COLS - map.getWidth() * 2) / 2) + j;
			int y = ((LINES - map.getHeight()) / 2) + i;
			mvprintw(y + 2, x, "%i%i", 1, 1);
			attroff(COLOR_PAIR(map[i][j / 2]));
		}
	}
}

void ar::NCurseDisplay::loadResources(const std::map<unsigned char, ar::colorVector> &map
)
{
	for (auto &item : map) {
		init_color(item.first, static_cast<short>((item.second.red / 255) * 1000),
			static_cast<short>((item.second.green / 255) * 1000),
			static_cast<short>((item.second.blue / 255) * 1000));
		init_pair(item.first, item.first, item.first);
	}
	init_color(0, 0, 0, 0);
	init_color(1, 1000, 1000, 1000);
	init_pair(0, 0, 0);
	init_pair(1, 1, 0);
	clear();
}

void ar::NCurseDisplay::initMenuAttr(size_t n_choices, std::vector<std::string> menuChoices
)
{
	for (int i = 0; i < static_cast<int>(n_choices); ++i) {
		char tmp[100];
		snprintf(tmp, 100, "%*s%*s", static_cast<int>(15 + strlen(menuChoices[i].c_str()) / 2),
			menuChoices[i].c_str(), static_cast<int>(15 - strlen(menuChoices[i].c_str()) / 2), "");
		_choices[i] = strdup(tmp);
		_items[i] = new_item(_choices[i], "");
	}
	_menu = new_menu(_items);
	_menuWin = newwin(5 + menuChoices.size(), 40, ((LINES - menuChoices.size()) / 2), ((COLS - 40) / 2));
	set_menu_win(_menu, _menuWin);
	set_menu_sub(_menu, derwin(_menuWin, 1+menuChoices.size(), 38, 3, 1));
	set_menu_fore(_menu, COLOR_PAIR(1) | A_REVERSE);
	set_menu_back(_menu, COLOR_PAIR(1));
	set_menu_grey(_menu, COLOR_PAIR(1));
	set_menu_mark(_menu, " > ");
	wattron(_menuWin, COLOR_PAIR(1));
	box(_menuWin, 0, 0);
	wattroff(_menuWin, COLOR_PAIR(1));
}

void ar::NCurseDisplay::initMenu(const std::vector<std::string> &menuChoices, const std::string &menuName,
	const std::vector<std::string> &display
)
{
	attron(COLOR_PAIR(1));
	clear();
	_nbChoices = menuChoices.size();
	_graphicalLibraries = display;
	_choices = static_cast<char **>(malloc(sizeof(char *) * (_nbChoices + 1)));
	_selectedItem = 0;
	_items = (ITEM **)malloc(sizeof(ITEM *) * (_nbChoices + 1));
	memset(_items, 0, sizeof(ITEM *) * (_nbChoices + 1));
	initMenuAttr(_nbChoices, menuChoices);
	_menuName = menuName;
	post_menu(_menu);
}

int ar::NCurseDisplay::refreshMenu(const ar::Event &key, const std::vector<ar::userInterface> &dataArray)
{
	switch (key) {
	case AR_UP:
		if (_selectedItem > 0)
			_selectedItem -= 1;
		menu_driver(_menu, REQ_UP_ITEM);
		break;
	case AR_DOWN:
		if (_selectedItem < static_cast<int>(dataArray.size()))
			_selectedItem += 1;
		menu_driver(_menu, REQ_DOWN_ITEM);
		break;
	case AR_RESIZE:
		resizeMenu(dataArray);
	default:
		break;
	}
	int i = 1;
	for (auto &text : _graphicalLibraries) {
		mvprintw(LINES - i, static_cast<int>(COLS - strlen(text.c_str())), "%s", text.c_str());
		i++;
	}
	displayUI(dataArray);
	refresh();
	wrefresh(_menuWin);
	return _selectedItem;
}

void ar::NCurseDisplay::refreshUsername(std::string &name, int realKey)
{
	int c = realKey;
	if (isalpha(c) && name.length() < 4)
		name += static_cast<char>(toupper(c));
	if ((c == KEY_BACKSPACE || c == 127) && !name.empty())
		name.pop_back();
}

void ar::NCurseDisplay::destroyMenu()
{
	_graphicalLibraries.clear();
	unpost_menu(_menu);
	free_menu(_menu);
	for (int i = 0; _items[i] != nullptr; ++i) {
		free_item(_items[i]);
	}
	for (size_t j = 0; j < _nbChoices; ++j) {
		free(_choices[j]);
	}
	delwin(_menuWin);
	free(_choices);
	free(_items);
	attroff(COLOR_PAIR(1));
}

void ar::NCurseDisplay::resizeMenu(std::vector<ar::userInterface> dataArray
)
{
	unpost_menu(_menu);
	clear();
	mvwin(_menuWin, ((LINES - 10) / 2), ((COLS - 40) / 2));
	wresize(_menuWin, 10, 40);
	set_menu_sub(_menu, derwin(_menuWin, 6, 38, 3, 1));

	post_menu(_menu);
	box(_menuWin, 0, 0);
	displayUI(dataArray);
	refresh();
}

void ar::NCurseDisplay::displayUI(std::vector<ar::userInterface> dataArray)
{
	mvprintw(15, static_cast<int>((COLS - _menuName.size()) / 2), "%s", _menuName.c_str());
	if (_selectedItem != static_cast<int>(dataArray.size())) {
		char szbuffer[200];
		snprintf(szbuffer, 200, " NAME : '%s'   HIGH SCORE : %i   ",
			dataArray.at(_selectedItem).username.c_str(), dataArray.at(_selectedItem).score);
		size_t size = strlen(szbuffer);
		mvprintw((15) / 2, static_cast<int>((COLS - size) / 2), " NAME : '%s'   HIGH SCORE : %i   ",
			dataArray.at(_selectedItem).username.c_str(), dataArray.at(_selectedItem).score);
	} else {
		mvprintw((15) / 2, static_cast<int>((COLS - 50) / 2), " \t\t\t\t\t\t\t\t\t\t\t\t\t\t\t");
	}
}

void ar::NCurseDisplay::loadResources([[gnu::unused]] const std::string &filePath,
	const std::map<unsigned char, ar::spriteCoords> &
)
{
}

extern "C" ar::IDisplay *createDisplay()
{
	return new ar::NCurseDisplay;
}

extern "C" void destroyDisplay(ar::IDisplay *ncurse)
{
	delete ncurse;
}
