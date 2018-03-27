/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Pacman
*/

#ifndef PACMAN_HPP_
	#define PACMAN_HPP_
	#include "IGame.hpp"
	#include "Exception.hpp"

namespace arc {
class Pacman {
	public:
		Pacman();
		~Pacman();
		// void getItems() noexcept;
	private:
		void setItems() noexcept;
		std::vector<std::string> _map;

};
}

#endif /* !PACMAN_HPP_ */
