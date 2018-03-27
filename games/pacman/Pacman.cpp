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
	for (auto it = _map.begin(); it < _map.end(); it++){
		std::cout << *it << std::endl;
	}
}

arc::Pacman::~Pacman()
{
}
