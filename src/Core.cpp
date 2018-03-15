/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Core
*/

#include <unistd.h>
#include <iostream>
#include <algorithm>
#include "Core.hpp"
#include "DynamicLib.hpp"
#include "IGame.hpp"

arc::Core::Core()
{
	_displayList.push_back("./lib_arcade_ncurses.so");
	_displayList.push_back("./lib_arcade_libcaca.so");
	_displayList.push_back("./lib_arcade_sfml.so");
}

arc::Core::~Core()
{}

int arc::Core::displayUsage()
{
	std::cout << "USAGE:" << std::endl;
	std::cout << "\t./arcade libname" << std::endl;
	return 0;
}

void arc::Core::setFirstGraphics(const std::string &libName)
{
	_displayName = libName;
	_displayLib.open(_displayName);
	_displayLib.instantiate();
	_display = _displayLib.load();
}

void arc::Core::switchToNextGraphics()
{
	auto it = std::find(_displayList.begin(),
				_displayList.end(), _displayName);

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

	item.name = "lapin";
	item.spritePath = "lib/sfml/Lunatic.png";
	item.spriteChar = '#';
	item.x = 0;
	item.y = 0;
	gameLoop(item);
}

void arc::Core::gameLoop(arc::Item &item)
{
	arc::KeysList keys;

	keys = _display->getKeys();
	while (computeKeys(item, keys)) {
		usleep(30000);
		_display->clear();
		_display->drawSprite(item);
		_display->refresh();
		keys = _display->getKeys();
	}
}

bool arc::Core::computeKeys(arc::Item &item, arc::KeysList &keys)
{
	while (!keys.empty()) {
		if (keys.front() == arc::Keys::MOVE_UP)
			item.y -= 2;
		else if (keys.front() == arc::Keys::MOVE_DOWN)
			item.y += 2;
		else if (keys.front() == arc::Keys::MOVE_LEFT)
			item.x -= 2;
		else if (keys.front() == arc::Keys::MOVE_RIGHT)
			item.x += 2;
		else if (keys.front() == arc::Keys::NEXT_LIB)
			switchToNextGraphics();
		else if (keys.front() == arc::Keys::PREV_LIB)
			switchToPrevGraphics();
		else if (keys.front() == arc::Keys::QUIT)
			return false;
		keys.pop();
	}
	return true;
}
