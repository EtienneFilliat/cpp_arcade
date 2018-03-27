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

class Pacman : public arc::IGame {
	public:
		Pacman();
		~Pacman();
		ItemList &getItems() noexcept final;
		//Item &getItemFromName(const std::string &) final;
		const Specs &getSpecs() const noexcept final;
		//void proccessIteraction(Interaction &) noexcept final;
		//void envUpdate() noexcept final;
		//const std::vector<struct Position> &getBulletPos() final;
	private:
		Item createItem(const char, int, int);
		void setItems() noexcept;
		std::vector<std::string> _map;
		ItemList _mapItems;
		Specs _spec;

};
}

#endif /* !PACMAN_HPP_ */
