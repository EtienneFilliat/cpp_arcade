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
{}

arc::Core::~Core()
{}

void arc::Core::loadLibs()
{
	_gameLib.open("libgame.so");
	_gameLib.instantiate();
	_game.reset(_gameLib.create());
}
