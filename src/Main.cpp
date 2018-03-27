/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Main
*/

#include <iostream>
#include "Core.hpp"

int main(int ac, char **av)
{
	arc::Core core;

	if (ac != 2)
		return core.displayUsage();
	try {
		core.initCore(av[1]);
		core.gameLoop();
	}
	catch (std::exception &err) {
		std::cerr << err.what() << std::endl;
		return 84;
	}
	return 0;
}
