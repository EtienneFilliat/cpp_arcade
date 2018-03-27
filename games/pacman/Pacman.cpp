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
			if (*y == '#') {
				item = createItem(*y, x_axis, y_axis);
				_mapItems.push_back(item);
			}
			y_axis++;
		}
		y_axis = 0;
		x_axis++;
	}
}

arc::Item arc::Pacman::createItem(const char type, int posx, int posy)
{
	arc::Item item;
	arc::Sprite sprite;

	(void) type;
	sprite.path = "games/pacman/sprites/blue_wall.png";
	sprite.name = "bluewall";
	sprite.substitute = '#';
	item.name = "Wall" + std::to_string(posx) + '_' + std::to_string(posy);
	std::cout << item.name << std::endl;
	sprite.color = arc::Color::BLUE;
	sprite.x = 0;
	sprite.y = 0;
	sprite.rotation = 0;
	item.sprites.push_back(sprite);
	item.spritesPath = "";
	item.x = posy;
	item.y = posx;
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
