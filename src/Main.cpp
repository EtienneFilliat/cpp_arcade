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
	DynamicLib<IGame> gameLib("./monKAKA.so");
	gameLib.open();
	gameLib.instantiate();
	LoadedLib<IGame> myGame(gameLib.getObject());
	myGame.run()->displaySomeShit();
	return 0;
}
