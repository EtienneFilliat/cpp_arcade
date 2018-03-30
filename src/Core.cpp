/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Core
*/

#include <unistd.h>
#include <iostream>
#include <algorithm>
#include <dirent.h>
#include "Core.hpp"
#include "DynamicLib.hpp"
#include "IGame.hpp"

arc::Core::Core()
	: _tryInteraction(0)
{}

arc::Core::~Core()
{}

void arc::Core::initCore(const std::string &firstGraphics,
				const std::string &displayDir,
				const std::string &gameDir)
{
	initGraphics(displayDir);
	initGames(gameDir);
	setFirstGraphics(firstGraphics);
	showGraphicsAvailable();
	if (_gameList.empty())
		throw Exception("No game library found in \'./games\'!",
					"Core");
	showGamesAvailable();
	setFirstGame();
}

void arc::Core::initGraphics(const std::string &directory)
{
	DIR *dir;
	struct dirent *ent;
	std::string name;

	dir = opendir(directory.c_str());
	if (dir == nullptr)
		throw Exception("No \'" + directory +
				"\' folder found!", "Core");
	ent = readdir(dir);
	while (ent != nullptr) {
		name = ent->d_name;
		if (ent->d_type == DT_DIR && name != "." && name != "..")
			initGraphics(directory + "/" + name);
		else if (ent->d_type == DT_REG)
			searchDisplayLib(directory + "/" + name);
		ent = readdir(dir);
	}
	closedir(dir);
}

void arc::Core::initGames(const std::string &directory)
{
	DIR *dir;
	struct dirent *ent;
	std::string name;

	dir = opendir(directory.c_str());
	if (dir == nullptr)
		throw Exception("No \'" + directory +
				"\' folder found!", "Core");
	ent = readdir(dir);
	while (ent != nullptr) {
		name = ent->d_name;
		if (ent->d_type == DT_DIR && name != "." && name != "..")
			initGames(directory + "/" + name);
		else if (ent->d_type == DT_REG)
			searchGameLib(directory + "/" + name);
		ent = readdir(dir);
	}
	closedir(dir);
}

void arc::Core::searchDisplayLib(const std::string &fullPathName)
{

	auto n = fullPathName.find(".so");
	size_t len = fullPathName.length();

	if (len >= 3)
		len -= 3;
	if (n != std::string::npos) {
		if (n == len)
			_displayList.push_back(fullPathName);
	}
}

void arc::Core::searchGameLib(const std::string &fullPathName)
{

	auto n = fullPathName.find(".so");
	size_t len = fullPathName.length();

	if (len >= 3)
		len -= 3;
	if (n != std::string::npos) {
		if (n == len)
			_gameList.push_back(fullPathName);
	}
}

int arc::Core::displayUsage()
{
	std::cout << "USAGE:" << std::endl;
	std::cout << "\t./arcade \'graphics_library.so\'" << std::endl;
	std::cout << std::endl << "All graphics libraries available are";
	std::cout << " in the \'lib/\' directory"<< std::endl;
	return 84;
}

void arc::Core::showGraphicsAvailable()
{
	std::cout << "GRAPHIC LIBRARIES AVAILABLE:" << std::endl;
	for (auto it = _displayList.begin(); it != _displayList.end(); it++) {
		std::cout << "\t" << *it << std::endl;
	}
	std::cout << std::endl;
}

void arc::Core::showGamesAvailable()
{
	std::cout << "GAME LIBRARIES AVAILABLE:" << std::endl;
	for (auto it = _gameList.begin(); it != _gameList.end(); it++) {
		std::cout << "\t" << *it << std::endl;
	}
}

void arc::Core::setFirstGraphics(const std::string &fullPathName)
{
	bool alreadyInList = false;
	std::string libName = fullPathName;
	auto isADir = fullPathName.find_last_of("/");

	_displayLib.open(fullPathName);
	_displayLib.instantiate();
	_display = _displayLib.load();
	if (isADir != std::string::npos)
		libName = fullPathName.substr(isADir + 1);
	for (auto it = _displayList.begin(); it != _displayList.end(); it++) {
		if ((*it).substr((*it).find_last_of("/") + 1) == libName) {
			alreadyInList = true;
			_displayName = *it;
		}
	}
	if (!alreadyInList) {
		_displayList.push_back(fullPathName);
		_displayName = fullPathName;
	}
}

void arc::Core::setFirstGame()
{
	_gameName = _gameList.front();
	_gameLib.open(_gameName);
	_gameLib.instantiate();
	_game = _gameLib.load();
}

void arc::Core::switchToNextGraphics()
{
	auto it = std::find(_displayList.begin(),
				_displayList.end(), _displayName);

	if (it == std::end(_displayList))
		throw Exception("Display library \'" + _displayName +
				"\' not found in library list!", "Core");
	_display->~IDisplay();
	it = std::next(it, 1);
	if (it == _displayList.end())
		it = _displayList.begin();
	_displayName = *it;
	_displayLib.open(_displayName);
	_displayLib.instantiate();
	_display.release();
	_display = _displayLib.load();
}

void arc::Core::switchToPrevGraphics()
{
	auto it = std::find(_displayList.begin(),
				_displayList.end(), _displayName);

	if (it == std::end(_displayList))
		throw Exception("Display library \'" + _displayName +
				"\' not found in library list!", "Core");
	_display->~IDisplay();
	if (it == _displayList.begin())
		it = _displayList.end();
	it = std::prev(it, 1);
	_displayName = *it;
	_displayLib.open(_displayName);
	_displayLib.instantiate();
	_display.release();
	_display = _displayLib.load();
}

void arc::Core::switchToNextGame()
{
	auto it = std::find(_gameList.begin(),
				_gameList.end(), _gameName);

	if (it == std::end(_gameList))
		throw Exception("Game library \'" + _gameName +
				"\' not found in library list!", "Core");
	_game->~IGame();
	it = std::next(it, 1);
	if (it == _gameList.end())
		it = _gameList.begin();
	_gameName = *it;
	_gameLib.open(_gameName);
	_gameLib.instantiate();
	_game.release();
	_game = _gameLib.load();
}

void arc::Core::switchToPrevGame()
{
	auto it = std::find(_gameList.begin(),
				_gameList.end(), _gameName);

	if (it == std::end(_gameList))
		throw Exception("Game library \'" + _gameName +
				"\' not found in library list!", "Core");
	_game->~IGame();
	if (it == _gameList.begin())
		it = _gameList.end();
	it = std::prev(it, 1);
	_gameName = *it;
	_gameLib.open(_gameName);
	_gameLib.instantiate();
	_game.release();
	_game = _gameLib.load();
}

void arc::Core::gameLoop()
{
	arc::InteractionList keys = _display->getInteractions();
	arc::ItemList items = _game->getItems();

	while (computeKeys(keys)) {
		_display->clear();
		for (auto it = items.begin(); it < items.end(); it++)
			_display->putItem(*it);
		_display->refresh();
		if (keys.empty())
			keys = _display->getInteractions();
		else
			keys.pop();
		_game->envUpdate();
		items = _game->getItems();
		usleep(1000);
	}
}

bool arc::Core::computeKeys(arc::InteractionList &keys)
{
	if (!keys.empty()) {
		switch (keys.front()) {
			case arc::Interaction::LIB_NEXT:
				switchToNextGraphics();
				break;
			case arc::Interaction::LIB_PREV:
				switchToPrevGraphics();
				break;
			case arc::Interaction::GAME_NEXT:
				switchToNextGame();
				break;
			case arc::Interaction::GAME_PREV:
				switchToPrevGame();
				break;
			case arc::Interaction::QUIT:
				return false;
			default:
				tryToProcessInteraction(keys);
		}
	}
	return true;
}

void arc::Core::tryToProcessInteraction(arc::InteractionList &keys)
{
	if (!_game->processInteraction(keys.front())) {
		if (_tryInteraction < 6)
			keys.push(keys.front());
		else
			_tryInteraction = 0;
	}
	else
		_tryInteraction = 0;
	_tryInteraction++;
}
