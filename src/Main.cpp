/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Main
*/

#include <dlfcn.h>
#include "IGame.hpp"
#include "DynamicLib.hpp"
#include "LoadedLib.hpp"

int main(void)
{
	arc::DynamicLib<IGame> gameLib("./myLib.so");
	gameLib.open();
	gameLib.instantiate();
	arc::LoadedLib<IGame> myGame(gameLib.getObject());
	return 0;
}
