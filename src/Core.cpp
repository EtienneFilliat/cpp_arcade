/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Core
*/

#include <unistd.h>
#include "Core.hpp"
#include "DynamicLib.hpp"
#include "IGame.hpp"

arc::Core::Core()
{
	_displayList.push_back("./lib_arcade_sfml.so");
	_displayList.push_back("./lib_arcade_libcaca.so");
	_it = _displayList.begin();
	_displayLib.open(*_it);
	_displayLib.instantiate();
	_display.reset(_displayLib.load());
}

arc::Core::~Core()
{}

void arc::Core::switchGraphics()
{
	//_display->~IDisplay();
	// _it++;
	// if (_it == _displayList.end())
	// 	_it = _displayList.begin();
	_displayLib.open(*_it);
	_displayLib.instantiate();
	_display.reset(_displayLib.load());
}

void arc::Core::launchGame()
{
	arc::Item item;

	item.name = "lapin";
	item.spritePath = "lib/sfml/Lunatic.png";
	item.spriteChar = '#';
	item.x = 50;
	item.y = 50;
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
		else if (keys.front() == arc::Keys::NEXT_LIB) {
			switchGraphics();
			return true;
		}
		else if (keys.front() == arc::Keys::QUIT)
			return false;
		keys.pop();
	}
	return true;
}
