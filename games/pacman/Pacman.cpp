/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Pacman
*/

#include <iostream>
#include <fstream>
#include <memory>
#include <cmath>
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
	_direction = arc::Interaction::MOVE_RIGHT;
	_eating = 0;
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
			_mapItems.push_back(createFirstPacman(posx, posy));
			break;
		case '.':
			_mapItems.insert(it, createPacgum(posx, posy));
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
	sprite.background = arc::Color::BLUE;
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

arc::Item arc::Pacman::createFirstPacman(const int x, const int y) noexcept
{
	arc::Item item;
	arc::Sprite sprite1;

	sprite1.path = "games/pacman/sprites/pacman1.png";
	sprite1.name = "pacman";
	sprite1.substitute = 'C';

	item.name = "pacman";
	sprite1.color = arc::Color::YELLOW;
	sprite1.background = arc::Color::BLACK;
	sprite1.x = 0;
	sprite1.y = 0;
	sprite1.rotation = 0;
	item.sprites.push_back(sprite1);
	this->createSecondPacman(item);
	item.spritesPath = "";
	item.x = y;
	item.y = x;
	item.currSpriteIdx = 0;
	return (item);
}

arc::Item arc::Pacman::createPacgum(const int x, const int y) noexcept
{
	arc::Item item;
	arc::Sprite sprite;

	sprite.path = "games/pacman/sprites/pacgum.png";
	sprite.name = "pacgum";
	sprite.substitute = '-';
	item.name = "pacgum" + std::to_string(x) + '_'
			+ std::to_string(y);
	sprite.color = arc::Color::CYAN;
	sprite.background = arc::Color::BLACK;
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

void arc::Pacman::createSecondPacman(Item &item) noexcept
{
	arc::Sprite sprite2;

	sprite2.path = "games/pacman/sprites/pacman2.png";
	sprite2.name = "pacman";
	sprite2.substitute = 'c';
	sprite2.color = arc::Color::YELLOW;
	sprite2.background = arc::Color::BLACK;
	sprite2.x = 0;
	sprite2.y = 0;
	sprite2.rotation = 0;
	item.sprites.push_back(sprite2);
}

const arc::ItemList &arc::Pacman::getItems() const noexcept
{
	return (_mapItems);
}

const arc::IGame::Specs &arc::Pacman::getSpecs() const noexcept
{
	return (_spec);
}

void arc::Pacman::envUpdate() noexcept
{
	autorun();
}

void arc::Pacman::autorun() noexcept
{
	arc::Item &item = getItemFromName("pacman");

	_eating += 0.15;
	if (_eating > 2) {
		item.currSpriteIdx = 0;
		_eating = 0;
	}
	else if (_eating > 1)
		item.currSpriteIdx = 1;
	if (isAWall(_direction, item.x, item.y)) {
		movePos(_direction, item);
		removePacgum(item);
		teleport(item);
	}
}

void arc::Pacman::teleport(Item &item) noexcept
{
	char pos = findInMap(item.x, item.y);

	if (pos == 'G')
		item.x = 26;
	if (pos == 'D')
		item.x = 1;
}

void arc::Pacman::removePacgum(const Item &item) noexcept
{
	std::string pacG = "pacgum";
	int x = std::floor(item.x + 0.5);
	int y = std::floor(item.y + 0.5);

	pacG += std::to_string(y) + '_' +
		std::to_string(x);
	removeItem(pacG);
}

bool arc::Pacman::processInteraction(Interaction &key) noexcept
{
	arc::Item &item = getItemFromName("pacman");

	if (isAWall(key, item.x, item.y)) {
		_direction = key;
		return true;
	}
	return false;
}

bool arc::Pacman::isAWall(Interaction &key, const float &itemX,
				const float &itemY) noexcept
{
	char check1;
	char check2;
	float x = itemX;
	float y = itemY;

	checkCollision1(key, x, y);
	check1 = findInMap(x, y);
	x = itemX;
	y = itemY;
	checkCollision2(key, x, y);
	check2 = findInMap(x, y);
	if (check1 != ' ' && check1 != 'P' && check1 != '.' && check1 != 'G' && 	check1 != 'D')
		return false;
	else if (check2 != ' ' && check2 != 'P' && check2 != '.' &&
			check1 != 'G' && check1 != 'D')
		return false;
	else
		return true;
}

void arc::Pacman::checkCollision1(Interaction &key, float &x, float &y) noexcept
{
	switch (key) {
		case arc::Interaction::MOVE_LEFT:
			x -= 0.1;
			break;
		case arc::Interaction::MOVE_RIGHT:
			x += 1;
			break;
		case arc::Interaction::MOVE_UP:
			y -= 0.1;
			break;
		case arc::Interaction::MOVE_DOWN:
			y += 1;
			break;
		default:
			return;
	}
}

void arc::Pacman::checkCollision2(Interaction &key, float &x, float &y) noexcept
{
	switch (key) {
		case arc::Interaction::MOVE_LEFT:
			x -= 0.1;
			y += 0.9;
			break;
		case arc::Interaction::MOVE_RIGHT:
			x += 1;
			y += 0.9;
			break;
		case arc::Interaction::MOVE_UP:
			x += 0.9;
			y -= 0.1;
			break;
		case arc::Interaction::MOVE_DOWN:
			x += 0.9;
			y += 1;
			break;
		default:
			return;
	}
}

void arc::Pacman::movePos(Interaction &key, Item &item) noexcept
{
	switch (key) {
		case arc::Interaction::MOVE_LEFT:
			item.x -= 0.1;
			item.sprites[item.currSpriteIdx].rotation = 180;
			break;
		case arc::Interaction::MOVE_RIGHT:
			item.x += 0.1;
			item.sprites[item.currSpriteIdx].rotation = 0;
			break;
		case arc::Interaction::MOVE_UP:
			item.y -= 0.1;
			item.sprites[item.currSpriteIdx].rotation = -90;
			break;
		case arc::Interaction::MOVE_DOWN:
			item.y += 0.1;
			item.sprites[item.currSpriteIdx].rotation = 90;
			break;
		default:
			return;
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

void arc::Pacman::removeItem(const std::string &name)
{

	for (auto it = _mapItems.begin(); it < _mapItems.end(); it++) {
		if (it->name == name) {
			_mapItems.erase(it);
			return;
		}
	}
}

char arc::Pacman::findInMap(const float posx, const float posy) noexcept
{
	int x_axis = 0;
	int y_axis = 0;
	int iposx = std::floor(posy);
	int iposy = std::floor(posx);


	for (std::vector<std::string>::iterator x = _map.begin();
		x < _map.end(); x++)
	{
		for (std::string::iterator y = x->begin(); y < x->end(); y++) {
			if (x_axis >= iposx && y_axis >= iposy) {
				return *y;
			}
			y_axis++;
		}
		y_axis = 0;
		x_axis++;
	}
	return 0;
}
