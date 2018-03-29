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
		const ItemList &getItems() const noexcept final;
		const Specs &getSpecs() const noexcept final;
		void processInteraction(Interaction &) noexcept final;
		void envUpdate() noexcept final;
	private:
		Item &getItemFromName(const std::string &);
		void createItem(const char, const int, const int) noexcept;
		void setItems() noexcept;
		Item createWall(const int, const int) noexcept;
		Item createPacman(const int, const int) noexcept;
		char findInMap(const float, const float,
				const Interaction) noexcept;
		void autorun() noexcept;
		bool isAWall(Interaction &key, const float &itemX,
				const float &itemY) noexcept;
		void checkCollision1(Interaction &, float &, float &) noexcept;
		void checkCollision2(Interaction &, float &, float &) noexcept;
		void movePos(Interaction &, Item &item) noexcept;
		std::vector<std::string> _map;
		ItemList _mapItems;
		Specs _spec;
		Interaction _direction;

};
}

#endif /* !PACMAN_HPP_ */
