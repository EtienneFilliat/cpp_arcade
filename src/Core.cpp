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
	_displayList.push_back("./lib_arcade_libcaca.so");
	_displayList.push_back("./lib_arcade_ncurses.so");
	_displayList.push_back("./lib_arcade_sfml.so");
	_it = _displayList.begin();
	_displayLib.open(*_it);
	_displayLib.instantiate();
	_display = _displayLib.load();
}

arc::Core::~Core()
{}

void arc::Core::switchGraphics(const std::string &cmd)
{
	_display->closeWindow();
	_it = (cmd == "next") ? _it + 1 : _it - 1;
	if (_it == _displayList.end())
		_it = _displayList.begin();
	else if (_it < _displayList.begin()) {
		_it = _displayList.end();
		_it--;
	}
	_displayLib.open(*_it);
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
			switchGraphics("next");
		else if (keys.front() == arc::Keys::PREV_LIB)
			switchGraphics("prev");
		else if (keys.front() == arc::Keys::QUIT)
			return false;
		keys.pop();
	}
	return true;
}
