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
#include <thread>
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
	initRandom();
	initGraphics(displayDir);
	initGames(gameDir);
	if (_gameList.empty())
		throw Exception("No game library found in \'./games\'!",
					"Core");
	menu();
	setFirstGraphics(firstGraphics);
}

void arc::Core::initRandom() const noexcept
{
	srand(getpid());
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

void arc::Core::searchDisplayLib(const std::string &fullPathName) noexcept
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

void arc::Core::searchGameLib(const std::string &fullPathName) noexcept
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

int arc::Core::displayUsage() const noexcept
{
	std::cout << "USAGE:" << std::endl;
	std::cout << "\t./arcade \'graphics_library.so\'" << std::endl;
	std::cout << std::endl << "All graphics libraries available are";
	std::cout << " in the \'lib/\' directory"<< std::endl;
	return 84;
}

void arc::Core::showGraphicsAvailable() const noexcept
{
	std::cout << "GRAPHIC LIBRARIES AVAILABLE:" << std::endl;
	for (auto it = _displayList.begin(); it != _displayList.end(); it++) {
		std::cout << "\t\t" << *it << std::endl;
	}
}

void arc::Core::showGamesAvailable() const noexcept
{
	size_t count = 1;
	size_t nameIdx;
	size_t nameLen;
	std::string gameName;

	std::cout << "GAME LIBRARIES AVAILABLE:";
	for (auto it = _gameList.begin(); it != _gameList.end(); it++) {
		nameIdx = (*it).find_last_of("_") + 1;
		nameLen = (*it).find_last_of(".") - nameIdx;
		gameName = (*it).substr(nameIdx, nameLen);
		std::cout << std::endl;
		std::cout << "\t\tGame library:\t" << *it << std::endl;
		std::cout << "\t\tGame name:\t" << gameName << std::endl;
		std::cout << "\t\tGame number:\t" << count << std::endl;
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
		_startLoop = std::chrono::high_resolution_clock::now();
		_display->clear();
		for (auto it = items.begin(); it < items.end(); it++)
			_display->putItem(*it);
		displayText();
		_display->refresh();
		if (keys.empty())
			keys = _display->getInteractions();
		else
			keys.pop();
		_game->envUpdate();
		items = _game->getItems();
		waitCycle();
	}
}

void arc::Core::displayText()
{
	_display->putStr("PLAYER:", 30, 1);
	_display->putStr(_userName, 30, 2);
	_display->putStr("SCORE:", 30, 4);
	_display->putStr(std::to_string(_game->getScore()), 30, 5);
}

void arc::Core::waitCycle() const noexcept
{
	auto endLoop = std::chrono::high_resolution_clock::now();
	millisec diff = endLoop - _startLoop;
	millisec wait(0.1 - diff.count());

	std::this_thread::sleep_for(wait);

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

void arc::Core::tryToProcessInteraction(arc::InteractionList &keys) noexcept
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

void arc::Core::menu()
{
	std::cout << "\033[2J\033[H";
	std::cout << "\t\t\tARCADE PROJECT" << std::endl << std::endl;
	showGraphicsAvailable();
	std::cout << std::endl << std::endl;
	showGamesAvailable();
	std::cout << std::endl;
	getPlayerName();
	std::cout << std::endl;
	_gameName = _gameList[getGameNumber()];
	_gameLib.open(_gameName);
	_gameLib.instantiate();
	_game = _gameLib.load();
}

void arc::Core::getPlayerName()
{
	std::cout << "Enter your name (< 12 characters): ";
	std::getline(std::cin, _userName);
	while (_userName.length() >= 12) {
		std::cout << "Your name is too long!" << std::endl;
		std::cout << "Enter a shorter name: ";
		std::getline(std::cin, _userName);
	}
}

size_t arc::Core::getGameNumber()
{
	std::string input;
	size_t nb = 0;

	std::cout << "Enter game number :";
	std::cin >> input;
	if (input.find_first_not_of("0123456789") == std::string::npos)
		nb = std::stoi(input);
	while (nb > _gameList.size() || nb == 0) {
		std::cout << "Wrong game number!" << std::endl;
		std::cout << "Enter another game number :";
		std::cin >> input;
		if (input.find_first_not_of("0123456789") == std::string::npos)
			nb = std::stoi(input);
	}
	return nb - 1;
}
