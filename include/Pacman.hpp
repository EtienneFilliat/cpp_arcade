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
	#include <ctime>

namespace arc {

class Pacman : public arc::IGame {
	public:
		Pacman();
		~Pacman();
		const ItemList &getItems() const noexcept final;
		const Specs &getSpecs() const noexcept final;
		bool processInteraction(Interaction &) noexcept final;
		void envUpdate() noexcept final;
		int getScore() noexcept final;
	private:
		Item &getItemFromName(const std::string &);
		bool removeItem(const std::string &);
		void createItem(const char, const int, const int) noexcept;
		void setItems() noexcept;
		Item createWall(const int, const int) noexcept;
		Item createBlackWall(const int x, const int y) noexcept;
		Item createPacgum(const int, const int) noexcept;
		Item createFirstPacman(const int, const int) noexcept;
		void createSecondPacman(Item &item) noexcept;
		Item createGhost(const int, const int) noexcept;
		Item createSuperPacgum(const int, const int) noexcept;
		void createSecondGhost(Item &item) noexcept;
		char findInMap(const float, const float) noexcept;
		void autorun();
		bool isAWall(Interaction &key, const float &itemX,
				const float &itemY) noexcept;
		void checkCollision1(Interaction &, float &, float &) noexcept;
		void checkCollision2(Interaction &, float &, float &) noexcept;
		void movePos(Interaction &, Item &item) noexcept;
		void removePacgum(const Item &item) noexcept;
		void teleport(Item &item) noexcept;
		void moveGhosts(const int i) noexcept;
		void movePosGhost(Interaction &, Item &item) noexcept;
		void checkIntersec(arc::Item &item,
					arc::Interaction &dir) noexcept;
		void chooseGhostDirection(std::vector<Interaction> &vec,
						arc::Interaction &dir) noexcept;
		void killPacman(arc::Item &ghost, arc::Item &pacman) noexcept;
		void reset();
		void chooseGhostColor(arc::Sprite &sprite,
					const int i) noexcept;
		void goInReverse(arc::Interaction &dir) noexcept;
		void eatSuperPacgum(arc::Item &item) noexcept;
		void checkTime() noexcept;
		std::vector<std::string> _map;
		ItemList _mapItems;
		Specs _spec;
		Interaction _direction;
		float _eating;
		int _score;
		int _ghNbr;
		using GhostMap = std::unordered_map<std::string, Interaction>;
		GhostMap _ghostDirection;
		using GhostSpriteState = std::unordered_map<std::string, float>;
		GhostSpriteState _ghostmov;
		bool _eatGhosts;
		std::chrono::high_resolution_clock::time_point _startTimer;
};
}

#endif /* !PACMAN_HPP_ */
