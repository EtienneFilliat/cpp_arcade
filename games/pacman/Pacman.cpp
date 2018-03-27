/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Pacman
*/

#include <iostream>
#include <fstream>
#include "Pacman.hpp"

arc::Pacman::Pacman()
{
	std::string S;

	std::ifstream F ("pacman_map.txt", std::ifstream::in);
	if (!F)
		throw arc::Exception("Cannot initialise file stream",
					"Pacman");
	while (getline(F, S))
		_map.push_back(S);
	setItems();
}

arc::Pacman::~Pacman()
{
}

void arc::Pacman::setItems() noexcept
{
	int x_axis = 0;
	int y_axis = 0;

	for (std::vector<std::string>::iterator x = _map.begin(); x < _map.end(); x++) {
		for (std::string::iterator y = x->begin(); y < x->end(); y++) {
			std::cout << "Found data at: (";
			std::cout << x_axis;
			std::cout << ",";
			std::cout << y_axis;
			std::cout << ") with value ";
			std::cout << *y << std::endl;
			y_axis++;
		}
		y_axis = 0;
		x_axis++;
		std::cout << "NEW LINE" << std::endl;
	}

}
