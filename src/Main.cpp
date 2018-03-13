/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Main
*/

#include <dlfcn.h>
#include "IGame.hpp"
#include "DynamicLib.hpp"
#include "LoadedGame.hpp"

int main(void)
{
	arc::DynamicLib<arc::IGame> gameLib("./myLib.so");
	gameLib.open();
	gameLib.instantiate();
	arc::LoadedGame myGame(gameLib.getObject());
	return 0;
}
