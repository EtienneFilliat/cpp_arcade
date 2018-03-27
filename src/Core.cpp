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
{}

arc::Core::~Core()
{}

void arc::Core::initCore(const std::string &firstGraphics,
				const std::string &displayDir)
{
	initGraphics(displayDir);
	setFirstGraphics(firstGraphics);
	showGraphicsAvailable();
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

int arc::Core::displayUsage()
{
	std::cout << "USAGE:" << std::endl;
	std::cout << "\t./arcade \'graphics_library.so\'" << std::endl;
	std::cout << std::endl << "All graphics libraries available are";
	std::cout << " in the \'lib/\' directory"<< std::endl;
	return 0;
}

void arc::Core::showGraphicsAvailable()
{
	std::cout << "GRAPHIC LIBRARIES AVAILABLE:" << std::endl;
	for (auto it = _displayList.begin(); it != _displayList.end(); it++) {
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

void arc::Core::launchGame()
{
	arc::Item item;
	arc::Sprite sprite;

	sprite.path = "lib/sfml/Lunatic.png";
	sprite.name = "lapin";
	sprite.substitute = '#';
	sprite.x = 0;
	sprite.y = 0;
	sprite.color = arc::Color::WHITE;
	sprite.rotation = 0;
	item.name = "lapin";
	item.sprites.push_back(sprite);
	item.spritesPath = "";
	item.x = 0;
	item.y = 0;
	gameLoop(item);
}

void arc::Core::gameLoop(arc::Item &item)
{
	arc::InteractionList keys;

	keys = _display->getInteractions();
	while (computeKeys(item, keys)) {
		usleep(30000);
		_display->clear();
		_display->putItem(item);
		_display->refresh();
		keys = _display->getInteractions();
	}
}

bool arc::Core::computeKeys(arc::Item &item, arc::InteractionList &keys)
{
	while (!keys.empty()) {
		if (keys.front() == arc::Interaction::MOVE_UP)
			item.y -= 2;
		else if (keys.front() == arc::Interaction::MOVE_DOWN)
			item.y += 2;
		else if (keys.front() == arc::Interaction::MOVE_LEFT)
			item.x -= 2;
		else if (keys.front() == arc::Interaction::MOVE_RIGHT)
			item.x += 2;
		else if (keys.front() == arc::Interaction::LIB_NEXT)
			switchToNextGraphics();
		else if (keys.front() == arc::Interaction::LIB_PREV)
			switchToPrevGraphics();
		else if (keys.front() == arc::Interaction::QUIT)
			return false;
		keys.pop();
	}
	return true;
}
