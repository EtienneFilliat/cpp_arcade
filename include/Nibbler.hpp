/*
** EPITECH PROJECT, 2018
** Project
** File description:
** Created by hexa,
*/

#ifndef PROJECT_NIBBLER_HPP
#define PROJECT_NIBBLER_HPP

	#include "IGame.hpp"

namespace arc {
	class Nibbler;
}

class arc::Nibbler : public arc::IGame {
public:
	Nibbler() noexcept;
	~Nibbler() noexcept final;
	const ItemList &getItems() const noexcept final;
	const Specs &getSpecs() const noexcept final;
	bool processInteraction(Interaction &) noexcept final;
	void envUpdate() noexcept final;
	int getScore() noexcept final;
	bool isOver() const noexcept final;
private:
	struct Specs _specs;
	ItemList _snake;
	ItemList _grower;
	ItemList _walls;
	ItemList _items;
	arc::Interaction _direction;
	int _score;
	bool _isOver;
	const float _step = 1;
	void createSnake() noexcept;
	void createGrower() noexcept;
	void createWalls(int w, int h) noexcept;
	void growSnake() noexcept;
	Item createSnakeItem(const std::string &, float, float) noexcept ;
	Item createWallItem(int x, int y) noexcept;
	void updateItems() noexcept;
	void moveUp() noexcept;
	void moveDown() noexcept;
	void moveRight() noexcept;
	void moveLeft() noexcept;
	bool snakeCollision(float x, float y) noexcept;
	bool growerCollision(float x, float y) noexcept;
	void loose() noexcept;
};

#endif //PROJECT_NIBBLER_HPP
