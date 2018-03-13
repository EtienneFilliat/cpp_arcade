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
	: _currentHandle(nullptr)
{}

arc::Core::~Core()
{
	_game.release();
}

void arc::Core::loadLibs()
{
	arc::DynamicLib<IGame>::fptr create;
	arc::DynamicLib<arc::IGame> gameLib("libgame.so");
	gameLib.open();
	create = gameLib.instantiate();
	_game.reset(create());
	_game->printKK();
}
