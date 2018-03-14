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
