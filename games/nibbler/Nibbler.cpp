/*
** EPITECH PROJECT, 2018
** Project
** File description:
** Created by hexa,
*/

#include <iostream>
#include <unistd.h>
#include <ctime>
#include <memory>
#include <algorithm>
#include "Nibbler.hpp"
#include "Exception.hpp"

extern "C" std::unique_ptr<arc::IGame> create_object()
{
	std::unique_ptr<arc::IGame> ptr(new arc::Nibbler);
	return std::move(ptr);
}

arc::Nibbler::Nibbler() noexcept
	: _direction(MOVE_RIGHT)
{
	this->_specs.x = 0;
	this->_specs.y = 0;
	this->_specs.pixelStep = 0;
	this->_specs.fps = 0;
	this->_score = -4;
	this->_isOver = false;
	this->createWalls(30, 26);
	this->createSnake();
	this->growSnake();
	this->growSnake();
	this->growSnake();
	this->growSnake();
	this->createGrower();
	this->updateItems();
}

arc::Nibbler::~Nibbler() noexcept
{}

const arc::ItemList &arc::Nibbler::getItems() const noexcept
{
	usleep(25000);
	return (this->_items);
}

const arc::IGame::Specs &arc::Nibbler::getSpecs() const noexcept
{
	return (this->_specs);
}

bool arc::Nibbler::processInteraction(Interaction &interaction) noexcept
{
	this->updateItems();
	if ((this->_direction == MOVE_UP &&
		interaction != MOVE_DOWN) ||
		(this->_direction == MOVE_DOWN &&
		interaction != MOVE_UP))
			this->_direction = interaction;
	else if ((this->_direction == MOVE_LEFT &&
		interaction != MOVE_RIGHT) ||
		(this->_direction == MOVE_RIGHT &&
		interaction != MOVE_LEFT))
			this->_direction = interaction;
	return (true);
}

void arc::Nibbler::envUpdate() noexcept
{
	switch (this->_direction) {
	case MOVE_RIGHT:
		this->moveRight();
		break;
	case MOVE_LEFT:
		this->moveLeft();
		break;
	case MOVE_UP:
		this->moveUp();
		break;
	case MOVE_DOWN:
		this->moveDown();
		break;
	default:
		break;
	}
}

void arc::Nibbler::createSnake() noexcept
{
	this->_snake.push_back(this->createSnakeItem("snake", 5, 5));
}

void arc::Nibbler::createGrower() noexcept
{
	int x;
	int y;

	srand(time(nullptr));
	x = rand() % 30;
	srand(time(nullptr));
	y = rand() % 26;
	if (x == 0)
		x += (rand() % 4) + 1;
	if (y == 0)
		y += (rand() % 4) + 1;
	if (y >= 25)
		y -= (rand() % 4) + 1;
	this->_grower.push_back(this->createSnakeItem("grower", x, y));
}

void arc::Nibbler::createWalls(int w, int h) noexcept
{
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			if (y == 0 || y == (h - 1) || x == 0 || x == (w - 1))
				this->_walls.push_back(
					this->createWallItem(x, y));
		}
	}
}

void arc::Nibbler::growSnake() noexcept
{
	float x = (this->_snake.back()).x;
	float y = (this->_snake.back()).y;

	switch (this->_direction) {
		case arc::Interaction::MOVE_RIGHT:
			x += this->_step;
			break;
		case arc::Interaction::MOVE_LEFT:
			x -= this->_step;
			break;
		case arc::Interaction::MOVE_UP:
			y -= this->_step;
			break;
		case arc::Interaction::MOVE_DOWN:
			y += this->_step;
			break;
		default:
			break;
	}
	this->_snake.push_back(this->createSnakeItem("snake_body", x, y));
	this->_score++;
}

arc::Item arc::Nibbler::createSnakeItem(const std::string &name,
	float x, float y) noexcept
{
	Item snake;
	Sprite sprite;

	sprite.name = name;
	sprite.x = 0;
	sprite.y = 0;
	sprite.rotation = 0;
	sprite.path = "games/nibbler/sprites/snake.png";
	sprite.substitute = 'O';
	sprite.color = GREEN;
	sprite.background = BLACK;
	snake.name = name;
	snake.x = x;
	snake.y = y;
	snake.currSpriteIdx = 0;
	snake.spritesPath = "";
	snake.sprites.push_back(sprite);
	return (snake);
}

arc::Item arc::Nibbler::createWallItem(int x, int y) noexcept
{
	Item wall;
	Sprite sprite;

	sprite.name = "wall";
	sprite.x = 0;
	sprite.y = 0;
	sprite.rotation = 0;
	sprite.path = "games/nibbler/sprites/blue_wall.png";
	sprite.substitute = '#';
	sprite.color = BLUE;
	sprite.background = BLUE;
	wall.name = "wall";
	wall.x = x;
	wall.y = y;
	wall.currSpriteIdx = 0;
	wall.spritesPath = "";
	wall.sprites.push_back(sprite);
	return (wall);
}

void arc::Nibbler::updateItems() noexcept
{
	this->_items.clear();
	for (auto &item : this->_snake)
		this->_items.push_back(item);
	for (const auto &item : this->_grower)
		this->_items.push_back(item);
	for (const auto &item : this->_walls)
		this->_items.push_back(item);
}

void arc::Nibbler::moveDown() noexcept
{
	(*(this->_snake.begin())).x = (this->_snake.back()).x;
	(*(this->_snake.begin())).y = (this->_snake.back()).y + this->_step;
	if (!this->growerCollision((*(this->_snake.begin())).x,
		(*(this->_snake.begin())).y)) {
		if (this->snakeCollision((*(this->_snake.begin())).x,
			(*(this->_snake.begin())).y))
			this->loose();
	}
	this->_snake.insert(this->_snake.end(), (*(this->_snake.begin())));
	this->_snake.erase(this->_snake.begin());
	this->updateItems();
}

void arc::Nibbler::moveUp() noexcept
{
	(*(this->_snake.begin())).x = (this->_snake.back()).x;
	(*(this->_snake.begin())).y = (this->_snake.back()).y - this->_step;
	if (!this->growerCollision((*(this->_snake.begin())).x,
		(*(this->_snake.begin())).y)) {
		if (this->snakeCollision((*(this->_snake.begin())).x,
			(*(this->_snake.begin())).y))
			this->loose();
	}
	this->_snake.insert(this->_snake.end(), (*(this->_snake.begin())));
	this->_snake.erase(this->_snake.begin());
	this->updateItems();
}

void arc::Nibbler::moveLeft() noexcept
{
	(*(this->_snake.begin())).x = (this->_snake.back()).x - this->_step;
	(*(this->_snake.begin())).y = (this->_snake.back()).y;
	if (!this->growerCollision((*(this->_snake.begin())).x,
		(*(this->_snake.begin())).y)) {
		if (this->snakeCollision((*(this->_snake.begin())).x,
			(*(this->_snake.begin())).y))
			this->loose();
	}
	this->_snake.insert(this->_snake.end(), (*(this->_snake.begin())));
	this->_snake.erase(this->_snake.begin());
	this->updateItems();
}

void arc::Nibbler::moveRight() noexcept
{
	(*(this->_snake.begin())).x = (this->_snake.back()).x + this->_step;
	(*(this->_snake.begin())).y = (this->_snake.back()).y;
	if (!this->growerCollision((*(this->_snake.begin())).x,
		(*(this->_snake.begin())).y)) {
		if (this->snakeCollision((*(this->_snake.begin())).x,
			(*(this->_snake.begin())).y))
			this->loose();
	}
	this->_snake.insert(this->_snake.end(), (*(this->_snake.begin())));
	this->_snake.erase(this->_snake.begin());
	this->updateItems();
}

int arc::Nibbler::getScore() noexcept
{
	return (this->_score);
}

bool arc::Nibbler::snakeCollision(float x, float y) noexcept
{
	int cnt = 0;
	for (auto it = this->_snake.begin(); it != this->_snake.end(); it++) {
		if ((*it).x == x && (*it).y == y)
			cnt++;
	}
	for (auto it = this->_walls.begin(); it != this->_walls.end(); it++) {
		if ((*it).x == x && (*it).y == y)
			return (true);
	}
	return (cnt > 1);
}

bool arc::Nibbler::growerCollision(float x, float y) noexcept
{
	for (auto it = this->_grower.begin();
		it != this->_grower.end(); it ++) {
		if ((*it).x == x && (*it).y == y) {
			this->growSnake();
			this->_grower.clear();
			this->createGrower();
			return (true);
		}
	}
	return (false);
}

bool arc::Nibbler::isOver() const noexcept
{
	return (this->_isOver);
}
void arc::Nibbler::loose() noexcept
{
	this->_score = -4;
	this->_snake.clear();
	this->_walls.clear();
	this->_grower.clear();
	this->_items.clear();
	this->createWalls(30, 26);
	this->createSnake();
	this->growSnake();
	this->growSnake();
	this->growSnake();
	this->growSnake();
	this->createGrower();
	this->updateItems();
	this->_direction = MOVE_RIGHT;
}

