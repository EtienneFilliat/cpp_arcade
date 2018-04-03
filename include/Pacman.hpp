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
	#include <unordered_map>

namespace arc {

class Pacman : public arc::IGame {
	public:
		Pacman();
		~Pacman();
		const ItemList &getItems() const noexcept final;
		const Specs &getSpecs() const noexcept final;
		bool processInteraction(Interaction &) noexcept final;
		void envUpdate() noexcept final;
	private:
		Item &getItemFromName(const std::string &);
		void removeItem(const std::string &);
		void createItem(const char, const int, const int) noexcept;
		void setItems() noexcept;
		Item createWall(const int, const int) noexcept;
		Item createPacgum(const int, const int) noexcept;
		Item createFirstPacman(const int, const int) noexcept;
		void createSecondPacman(Item &item) noexcept;
		Item createGhost(const int, const int) noexcept;
		char findInMap(const float, const float) noexcept;
		void autorun() noexcept;
		bool isAWall(Interaction &key, const float &itemX,
				const float &itemY) noexcept;
		void checkCollision1(Interaction &, float &, float &) noexcept;
		void checkCollision2(Interaction &, float &, float &) noexcept;
		void movePos(Interaction &, Item &item) noexcept;
		void removePacgum(const Item &item) noexcept;
		void teleport(Item &item) noexcept;
		void moveGhosts(const int i) noexcept;
		std::vector<std::string> _map;
		ItemList _mapItems;
		Specs _spec;
		Interaction _direction;
		float _eating;
		int _ghNbr;
		using GhostMap = std::unordered_map<std::string, Interaction>;
		GhostMap _ghostDirection;

};
}

#endif /* !PACMAN_HPP_ */
