/*
** EPITECH PROJECT, 2021
** cpp_arcade
** File description:
** Created by angevil,
*/

#include <dlfcn.h>
#include <iostream>
#include "CoreManager.hpp"

ar::CoreManager::CoreManager() : _graphicInterface(nullptr), _displayID(0), _gameID(0)
{
}

void ar::CoreManager::loadNextGraphMenu(const std::vector<std::string> &choices, const std::string title,
	const std::vector<userInterface> &UI
)
{
	std::vector<std::string> graphicalLibraries;
	for (auto display : _displays) {
		graphicalLibraries.push_back(display.second->fileName);
	}
	_graphicInterface->destroyMenu();
	unloadCurrentDisplay();
	_displayID += 1;
	if (_displayID == static_cast<int>(_displays.size()))
		_displayID = 0;
	loadCurrentDisplay();
	_graphicInterface->initMenu(choices, title, graphicalLibraries);
	_graphicInterface->refreshMenu(AR_UNKNOWN, UI);
}

void ar::CoreManager::loadPrevGraphMenu(const std::vector<std::string> &choices, const std::string title,
	const std::vector<userInterface> &UI
)
{
	std::vector<std::string> graphicalLibraries;
	for (auto display : _displays) {
		graphicalLibraries.push_back(display.second->fileName);
	}
	_graphicInterface->destroyMenu();
	unloadCurrentDisplay();
	_displayID -= 1;
	if (_displayID == -1)
		_displayID = static_cast<int>(
			_displays.size() - 1);
	loadCurrentDisplay();
	_graphicInterface->initMenu(choices, title, graphicalLibraries);
	_graphicInterface->refreshMenu(AR_UNKNOWN, UI);
}

ar::Event ar::CoreManager::loopMenuGameOver(const std::vector<userInterface> &GameOverUI,
	const std::vector<std::string> &gameOverChoices, int &id
)
{
	ar::Event key = AR_UNKNOWN;
	int realKey;

	while (key != AR_VALIDATE) {
		key = _graphicInterface->getEvent(realKey);
		if (realKey && !(key == ar::AR_UP || key == ar::AR_DOWN || key == AR_RESIZE))
			_graphicInterface->refreshMenu(key, GameOverUI);
		if (key == ar::AR_UP || key == ar::AR_DOWN || key == AR_RESIZE)
			id = _graphicInterface->refreshMenu(key, GameOverUI);
		else if (key == ar::AR_NEXT_GRAPH_LIB) {
			loadNextGraphMenu(gameOverChoices, "GAME OVER", GameOverUI);
			id = 0;
		} else if (key == ar::AR_PREV_GRAPH_LIB) {
			loadPrevGraphMenu(gameOverChoices, "GAME OVER", GameOverUI);
			id = 0;
		} else if (key == AR_EXIT) {
			return AR_EXIT;
		}
	}
	if (id == 2)
		return AR_EXIT;
	else if (id == 0)
		key = AR_UNKNOWN;
	else
		key = AR_MENU;
	return key;
}

ar::Event ar::CoreManager::gameOverMenu(std::vector<userInterface> &UIs)
{
	int id;
	ar::Event key = AR_UNKNOWN;
	std::vector<std::string> gameOverChoices;
	std::vector<userInterface> gameOverUI;
	userInterface ui;

	gameOverChoices.push_back("REPLAY");
	gameOverChoices.push_back("GO TO MENU");
	gameOverChoices.push_back("EXIT");

	while (key != ar::AR_MENU) {
		key = selectGameAndDisplay();
		ui = {_games.at(_gameID)->UI.score, UIs.at(0).username, 0};
		gameOverUI = {};
		gameOverUI.push_back(ui);
		gameOverUI.push_back(ui);
		if (key == ar::AR_EXIT)
			return AR_EXIT;
		if (key == ar::AR_GAME_OVER) {
			_graphicInterface->initMenu(gameOverChoices, "GAME OVER", {});
			_graphicInterface->refreshMenu(key, gameOverUI);
			id = 0;
			key = loopMenuGameOver(gameOverUI, gameOverChoices, id);
			_graphicInterface->destroyMenu();
			if (key == AR_EXIT)
				return AR_EXIT;
			_games.at(_gameID)->gameDestructor(_games.at(_gameID)->gameInterface);
			_games.at(_gameID)->gameInterface = _games.at(_gameID)->gameConstructor();
		}
	}
	return key;
}

ar::Event ar::CoreManager::mainMenu(std::vector<ar::userInterface> &UIs, std::vector<std::string> menuChoices)
{
	ar::Event key = AR_UNKNOWN;
	int realKey;
	int id = 0;

	std::vector<std::string> graphicalLibraries;
	for (auto display : _displays) {
		graphicalLibraries.push_back(display.second->fileName);
	}
	_graphicInterface->initMenu(menuChoices, "ARCADE", graphicalLibraries);
	id = _graphicInterface->refreshMenu(key, UIs);
	while (key != AR_VALIDATE) {
		key = _graphicInterface->getEvent(realKey);
		for (auto &UI : UIs) {
			_graphicInterface->refreshUsername(UI.username, realKey);
			refreshNames(UIs);
		}
		if (realKey && !(key == ar::AR_UP || key == ar::AR_DOWN || key == AR_RESIZE))
			_graphicInterface->refreshMenu(key, UIs);
		if (key == ar::AR_UP || key == ar::AR_DOWN || key == AR_RESIZE)
			id = _graphicInterface->refreshMenu(key, UIs);
		else if (key == ar::AR_VALIDATE) {
			if (id == static_cast<int>(_games.size()))
				return AR_EXIT;
			_gameID = id;
		} else if (key == ar::AR_NEXT_GRAPH_LIB) {
			loadNextGraphMenu(menuChoices, "ARCADE", UIs);
			id = 0;
		} else if (key == ar::AR_PREV_GRAPH_LIB) {
			loadPrevGraphMenu(menuChoices, "ARCADE", UIs);
			id = 0;
		} else if (key == AR_EXIT) {
			return AR_EXIT;
		}
	}
	return key;
}

void ar::CoreManager::refreshNames(std::vector<userInterface> &UIs)
{
	std::string nameStock = UIs.at(0).username;
	UIs = {};
	auto it = _games.begin();
	while (it != _games.end()) {
		(*it).second->UI.username = nameStock;
		UIs.push_back((*it).second->UI);
		it++;
	}
}

void ar::CoreManager::menu()
{
	std::vector<userInterface> UIs;
	ar::Event key = ar::AR_UNKNOWN;
	std::vector<std::string> menuChoices;
	std::string name;
	userInterface ui;

	auto it = _games.begin();
	while (it != _games.end()) {
		menuChoices.push_back((*it).second->gameInterface->getGameName());
		(*it).second->UI.username = name;
		UIs.push_back((*it).second->UI);
		it++;
	}
	menuChoices.push_back("Exit");

	while (key != AR_EXIT) {
		key = mainMenu(UIs, menuChoices);
		_graphicInterface->destroyMenu();
		while (key != AR_EXIT && key != AR_MENU) {
			refreshNames(UIs);
			key = gameOverMenu(UIs);
		}
	}
}

ar::Event ar::CoreManager::game()
{
	int realKey;
	ar::Event key = ar::AR_PAUSE;
	ar::IGame *game = _games.at(_gameID)->gameInterface;

	if (!_graphicInterface->canHandleSprites()) {
		_graphicInterface->loadResources(game->getColors());
	} else
		_graphicInterface->loadResources(game->getSpritesPath(), game->getSprites());
	while (!game->isGameOver() && key != ar::AR_EXIT) {
		key = _graphicInterface->getEvent(realKey);
		if (key == AR_RESTART) {
			restartCurrentGame();
			game = _games.at(_gameID)->gameInterface;
		}
		game->manageKey(key);
		game->loop();
		_games.at(_gameID)->UI.score = game->refreshScore();
		_games.at(_gameID)->UI.time = game->refreshTimer();
		_graphicInterface->displayGame(_games.at(_gameID)->UI, game->getMap());
		if (key == ar::AR_PREV_GAME || key == ar::AR_NEXT_GAME || key == ar::AR_NEXT_GRAPH_LIB ||
			key == ar::AR_PREV_GRAPH_LIB || key == ar::AR_MENU) {
			game->setPause();
			return key;
		}
	}
	if (game->isGameOver())
		return AR_GAME_OVER;
	return AR_EXIT;
}

void ar::CoreManager::loadAllGames(std::vector<std::string> names)
{
	int i = 0;
	auto it = names.begin();
	while (it != names.end()) {
		dlGames(it, i);
	}
	if (_games.empty())
		throw std::runtime_error("No game could be loaded");
}

void ar::CoreManager::dlGames(std::vector<std::string>::iterator &it, int &i)
{
	auto *game = new gameHdl;
	game->gameHandler = dlopen((*it).c_str(), RTLD_LAZY);
	if (game->gameHandler == nullptr) {
		std::cerr << "Couldn't open the shared library for game: " << *it << std::endl;
		it++;
		return;
	}
	game->gameConstructor = (createGame *)dlsym(game->gameHandler, "createGame");
	if (dlerror() != nullptr) {
		std::cerr << "Couldn't load create symbol for: " << *it << std::endl;
		it++;
		return;
	}
	game->gameDestructor = (destroyGame *)dlsym(game->gameHandler, "destroyGame");
	if (dlerror() != nullptr) {
		std::cerr << "Couldn't load destroy symbol for: " << *it << std::endl;
		it++;
		return;
	}
	game->gameInterface = game->gameConstructor();
	game->UI = (userInterface){0, "", 0};
	game->fileName = std::string(*it);
	_games.insert(std::pair<int, gameHdl *>(i, game));
	i += 1;
	it++;
}

void ar::CoreManager::unloadAllGames()
{
	auto it = _games.begin();
	while (it != _games.end()) {
		(*it).second->gameDestructor((*it).second->gameInterface);
		dlclose((*it).second->gameHandler);
		delete (*it).second;
		it++;
	}
	_games.clear();
}

ar::Event ar::CoreManager::selectGameAndDisplay()
{
	ar::Event key = ar::AR_UNKNOWN;

	while (key != AR_EXIT && key != ar::AR_MENU && key != ar::AR_GAME_OVER) {
		key = game();
		if (key == ar::AR_PREV_GAME) {
			_gameID -= 1;
			if (_gameID == -1)
				_gameID = static_cast<int>(_games.size() - 1);
		} else if (key == ar::AR_NEXT_GAME) {
			_gameID += 1;
			if (_gameID == static_cast<int>(_games.size()))
				_gameID = 0;
		} else if (key == ar::AR_PREV_GRAPH_LIB) {
			unloadCurrentDisplay();
			_displayID -= 1;
			if (_displayID == -1)
				_displayID = static_cast<int>(_displays.size() - 1);
			loadCurrentDisplay();
		} else if (key == ar::AR_NEXT_GRAPH_LIB) {
			unloadCurrentDisplay();
			_displayID += 1;
			if (_displayID == static_cast<int>(_displays.size()))
				_displayID = 0;
			loadCurrentDisplay();
		}
	}
	return key;
}

void ar::CoreManager::loadAllDisplay(std::vector<std::string> names)
{
	int i = 0;
	auto it = names.begin();
	while (it != names.end()) {
		dlDisplay(it, i, names);
	}
	if (_displays.empty())
		throw std::runtime_error("No display could be loaded");
}

void ar::CoreManager::dlDisplay(std::vector<std::string>::iterator &it, int &i, const std::vector<std::string> &names)
{
	displayHdl *display;
	display = new displayHdl;
	display->displayHandler = dlopen((*it).c_str(), RTLD_LAZY);
	if (display->displayHandler == nullptr) {
		if ((*it) == names.at(names.size() - 1))
			throw std::runtime_error("Couldn't open the shared library for Display: " + *it);
		std::cerr << "Couldn't open the shared library for Display: " << *it << std::endl;
		it++;
		_displayID = 0;
		return;
	}
	display->displayConstructor = (createDisplay *)dlsym(display->displayHandler, "createDisplay");
	if (dlerror() != nullptr) {
		std::cerr << "Couldn't load create symbol for: " << *it << std::endl;
		it++;
		return;
	}
	display->displayDestructor = (destroyDisplay *)dlsym(display->displayHandler, "destroyDisplay");
	if (dlerror() != nullptr) {
		std::cerr << "Couldn't load destroy symbol for: " << *it << std::endl;
		it++;
		return;
	}
	display->fileName = std::string(*it);
	_displays.insert(std::pair<int, displayHdl *>(i, display));
	i += 1;
	it++;
}

void ar::CoreManager::unloadAllDisplay()
{
	_displays.at(_displayID)->displayDestructor(_graphicInterface);
	auto it = _displays.begin();
	while (it != _displays.end()) {
		dlclose((*it).second->displayHandler);
		delete (*it).second;
		it++;
	}
	_displays.clear();
}

void ar::CoreManager::unloadCurrentDisplay()
{
	if (_graphicInterface != nullptr)
		_displays.at(_displayID)->displayDestructor(_graphicInterface);
}

void ar::CoreManager::loadCurrentDisplay()
{
	if (_displayID >= static_cast<int>(_displays.size()))
		throw std::runtime_error("Invalid argument");
	_graphicInterface = _displays.at(_displayID)->displayConstructor();
}

void ar::CoreManager::setDisplayID(int displayID)
{
	_displayID = displayID;
}

void ar::CoreManager::restartCurrentGame()
{
	_games.at(_gameID)->gameDestructor(_games.at(_gameID)->gameInterface);
	_games.at(_gameID)->gameInterface = _games.at(_gameID)->gameConstructor();
}

