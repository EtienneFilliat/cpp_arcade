/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Main
*/

#include <dlfcn.h>
#include "DynamicLib.hpp"
#include "GameLibManager.hpp"

int main(void)
{
	DynamicLib<IGame> gameLib("./monKAKA.so");
	gameLib.open();
	gameLib.instantiate();
	GameLibManager myGame(gameLib.getObject());
	myGame.display();
	return 0;
}
