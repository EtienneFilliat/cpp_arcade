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
	_gameLib.open("./snake.so");
	_displayLib.open("./sfml.so");
	_gameLib.instantiate();
	_displayLib.instantiate();
	_game.reset(_gameLib.load());
	_display.reset(_displayLib.load());
}

arc::Core::~Core()
{}
