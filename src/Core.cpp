/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Core
*/

#include <dlfcn.h>
#include "Core.hpp"
#include "DynamicLib.hpp"
#include "IGame.hpp"

arc::Core::Core()
{
	_displayLib.open("./lib_arcade_sfml.so");
	_displayLib.instantiate();
	_display.reset(_displayLib.load());
}

arc::Core::~Core()
{}

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
	//arc::KeysList keys;

	while (1) {
		_display->clear();
		_display->drawSprite(item);
		_display->refresh();
		//keys = _display->getKeys();
		//keys.
	}
}