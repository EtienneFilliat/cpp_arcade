/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Pacman
*/

#include <iostream>
#include <fstream>
#include <memory>
#include "Pacman.hpp"

extern "C" std::unique_ptr<arc::IGame> create_object()
{
	std::unique_ptr<arc::IGame> ptr(new arc::Pacman);
	return std::move(ptr);
}

arc::Pacman::Pacman()
{
	std::string S;

	_spec.x = 0;
	_spec.y = 0;
	_spec.fps = 0;
	_spec.pixelStep = 32;
	std::ifstream F ("./games/pacman/pacman_map.txt", std::ifstream::in);
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
	arc::Item item;
	int x_axis = 0;
	int y_axis = 0;

	for (std::vector<std::string>::iterator x = _map.begin();
		x < _map.end(); x++) {
		for (std::string::iterator y = x->begin(); y < x->end(); y++) {
			createItem(*y, x_axis, y_axis);
			y_axis++;
		}
		y_axis = 0;
		x_axis++;
	}
}

void arc::Pacman::createItem(const char type, const int posx,
				const int posy) noexcept
{
	auto it = _mapItems.begin();

	switch (type) {
		case '#':
			_mapItems.insert(it, createWall(posx, posy));
			break;
		case 'P':
			_mapItems.push_back(createPacman(posx, posy));
			break;
		default:
			return;
	}
}

arc::Item arc::Pacman::createWall(const int x, const int y) noexcept
{
	arc::Item item;
	arc::Sprite sprite;

	sprite.path = "games/pacman/sprites/blue_wall.png";
	sprite.name = "bluewall";
	sprite.substitute = '#';
	item.name = "Wall" + std::to_string(x) + '_' + std::to_string(y);
	sprite.color = arc::Color::BLUE;
	sprite.x = 0;
	sprite.y = 0;
	sprite.rotation = 0;
	item.sprites.push_back(sprite);
	item.spritesPath = "";
	item.x = y;
	item.y = x;
	item.currSpriteIdx = 0;
	return (item);
}

arc::Item arc::Pacman::createPacman(const int x, const int y) noexcept
{
	arc::Item item;
	arc::Sprite sprite;

	sprite.path = "games/pacman/sprites/pacman.png";
	sprite.name = "pacman";
	sprite.substitute = 'C';
	item.name = "pacman";
	sprite.color = arc::Color::YELLOW;
	sprite.x = 0;
	sprite.y = 0;
	sprite.rotation = 0;
	item.sprites.push_back(sprite);
	item.spritesPath = "";
	item.x = y;
	item.y = x;
	item.currSpriteIdx = 0;
	return (item);
}

arc::ItemList &arc::Pacman::getItems() noexcept
{
	return (_mapItems);
}

const arc::IGame::Specs &arc::Pacman::getSpecs() const noexcept
{
	return (_spec);
}

void arc::Pacman::processInteraction(Interaction &key) noexcept
{
	arc::Item &item = getItemFromName("pacman");
	int x = item.x;
	int y = item.y;
	char c;

	switch (key) {
		case arc::Interaction::MOVE_LEFT: x -= 1;
			break;
		case arc::Interaction::MOVE_RIGHT: x += 1;
			break;
		case arc::Interaction::MOVE_UP: y -= 1;
			break;
		case arc::Interaction::MOVE_DOWN: y += 1;
			break;
		default: return;
	}
	c = findInMap(x, y);
	if (c == ' ' || c == 'P') {
		item.x = x;
		item.y = y;
	}
}

arc::Item &arc::Pacman::getItemFromName(const std::string &name)
{
	for (auto it = _mapItems.begin(); it < _mapItems.end(); it++) {
		if (it->name == name)
			return *it;
	}
	return *_mapItems.begin();
}

char arc::Pacman::findInMap(const int posx, const int posy) noexcept
{
	int x_axis = 0;
	int y_axis = 0;

	for (std::vector<std::string>::iterator x = _map.begin();
		x < _map.end(); x++)
	{
		for (std::string::iterator y = x->begin(); y < x->end(); y++) {
			if (x_axis == posy && y_axis == posx) {
				return *y;
			}
			y_axis++;
		}
		y_axis = 0;
		x_axis++;
	}
	return 0;
}
