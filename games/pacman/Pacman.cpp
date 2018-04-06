/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Pacman
*/

#include <iostream>
#include <fstream>
#include <memory>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include "Pacman.hpp"

extern "C" std::unique_ptr<arc::IGame> create_object()
{
	std::unique_ptr<arc::IGame> ptr(new arc::Pacman);
	return std::move(ptr);
}

arc::Pacman::Pacman()
{
	std::string S;
	std::ifstream F ("./games/pacman/pacman_map.txt", std::ifstream::in);

	_spec.x = 0;
	_spec.y = 0;
	_spec.fps = 0;
	_spec.pixelStep = 32;
	_direction = arc::Interaction::MOVE_RIGHT;
	_eating = 0;
	_ghNbr = 0;
	_score = 0;
	_eatGhosts = false;
	_Over = false;
	_startTimer = std::chrono::high_resolution_clock::now();
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

	for (auto x = _map.begin();
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
		case 'M':
			_mapItems.insert(it, createBlackWall(posx, posy));
			break;
		case '#':
			_mapItems.insert(it, createWall(posx, posy));
			break;
		case 'P':
			_mapItems.push_back(createFirstPacman(posx, posy));
			break;
		case '.':
			_mapItems.insert(it, createPacgum(posx, posy));
			break;
		case 'H':
			_mapItems.push_back(createGhost(posx, posy));
			break;
		case 'S':
			_mapItems.insert(it, createSuperPacgum(posx, posy));
			break;
		default:
			return;
	}
}

arc::Item arc::Pacman::createBlackWall(const int x, const int y) noexcept
{
	arc::Item item;
	arc::Sprite sprite;

	sprite.path = "games/pacman/sprites/black_wall.png";
	sprite.name = "blackwall";
	sprite.substitute = ' ';
	item.name = "Wall" + std::to_string(x) + '_' + std::to_string(y);
	sprite.color = arc::Color::BLACK;
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

arc::Item arc::Pacman::createSuperPacgum(const int x, const int y) noexcept
{
	arc::Item item;
	arc::Sprite sprite;

	sprite.path = "games/pacman/sprites/Spacgum.png";
	sprite.name = "Spacgum";
	sprite.substitute = '+';
	item.name = "Spacgum" + std::to_string(x) + '_'
			+ std::to_string(y);
	sprite.color = arc::Color::YELLOW;
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

arc::Item arc::Pacman::createGhost(const int x, const int y) noexcept
{
	arc::Item item;
	arc::Sprite sprite1;

	chooseGhostColor(sprite1, 1);
	sprite1.name = "ghost";
	sprite1.substitute = '@';
	item.name = "ghost" + std::to_string(_ghNbr);
	_ghostDirection[item.name] = arc::Interaction::MOVE_RIGHT;
	_ghostmov[item.name] = 0;
	sprite1.background = arc::Color::BLACK;
	sprite1.x = 0;
	sprite1.y = 0;
	sprite1.rotation = 0;
	item.sprites.push_back(sprite1);
	createSecondGhost(item);
	createFearGhost(item);
	_ghNbr++;
	item.spritesPath = "";
	item.x = y;
	item.y = x;
	item.currSpriteIdx = 0;
	return (item);
}

void arc::Pacman::createSecondGhost(arc::Item &item) noexcept
{
	arc::Sprite sprite2;

	chooseGhostColor(sprite2, 2);
	sprite2.name = "ghost" + std::to_string(_ghNbr) + "_2";
	sprite2.substitute = 'a';
	sprite2.background = arc::Color::BLACK;
	sprite2.x = 0;
	sprite2.y = 0;
	sprite2.rotation = 0;
	item.sprites.push_back(sprite2);
}

void arc::Pacman::createFearGhost(arc::Item &item) noexcept
{
	arc::Sprite sprite1;
	arc::Sprite sprite2;

	sprite1.path = "games/pacman/sprites/fear_ghost1.png";
	sprite1.color = arc::Color::CYAN;
	sprite1.substitute = 'o';
	sprite1.background = arc::Color::BLACK;
	sprite1.x = 0;
	sprite1.y = 0;
	sprite1.rotation = 0;
	item.sprites.push_back(sprite1);
	sprite2.path = "games/pacman/sprites/fear_ghost2.png";
	sprite2.color = arc::Color::CYAN;
	sprite2.substitute = 'O';
	sprite2.background = arc::Color::BLACK;
	sprite2.x = 0;
	sprite2.y = 0;
	sprite2.rotation = 0;
	item.sprites.push_back(sprite2);
}

void arc::Pacman::chooseGhostColor(arc::Sprite &sprite, const int i) noexcept
{
	int nbr;

	nbr = _ghNbr % 4;
	switch (nbr) {
		case 1:
			sprite.path = "games/pacman/sprites/green_ghost"
					+ std::to_string(i) + ".png";
			sprite.color = arc::Color::GREEN;
			break;
		case 2:
			sprite.path = "games/pacman/sprites/purple_ghost"
					+ std::to_string(i) + ".png";
			sprite.color = arc::Color::MAGENTA;
			break;
		case 3:
			sprite.path = "games/pacman/sprites/blue_ghost"
					+ std::to_string(i) + ".png";
			sprite.color = arc::Color::CYAN;
			break;
		default:
			sprite.path = "games/pacman/sprites/red_ghost"
					+ std::to_string(i) + ".png";
			sprite.color = arc::Color::RED;

	}
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
	arc::Item &item = getItemFromName("pacman");

	_Over = checkEnd();
	try {
		autorun(item);
		for (int i = 0; i < _ghNbr; i++)
			moveGhosts(i, item);
	}
	catch (std::exception &err) {
		std::cerr << err.what() << std::endl;
	}
}

bool arc::Pacman::checkEnd() noexcept
{
	for (auto it = _mapItems.begin(); it < _mapItems.end(); it++) {
		if (it->sprites[0].name == "pacgum"
			|| it->sprites[0].name == "Spacgum")
			return false;
	}
	return true;
}

void arc::Pacman::moveGhosts(const int i, arc::Item &pac) noexcept
{
	std::string name = "ghost" + std::to_string(i);
	arc::Item &item = getItemFromName(name);
	auto search = _ghostDirection.find(name);
	auto state = _ghostmov.find(name);

	state->second += 0.15;
	chooseGhostSprite(state->second, item);
	checkIntersec(item, search->second, pac);
	if (isAWall(search->second, item.x, item.y)) {
		movePosGhost(search->second, item);
		killPacman(item, pac);
		teleport(item);
	}
}

void arc::Pacman::chooseGhostSprite(float &state, arc::Item &item) noexcept
{
	if (state > 2) {
		item.currSpriteIdx = 0;
		if (_eatGhosts)
			item.currSpriteIdx = 2;
		state = 0;
	}
	else if (state > 1) {
		item.currSpriteIdx = 1;
		if (_eatGhosts)
			item.currSpriteIdx = 3;
	}
}

void arc::Pacman::killPacman(arc::Item &ghost, arc::Item &pacman) noexcept
{
	if (pacman.name != "pacman")
		return;
	if ((std::floor(ghost.x) == std::floor(pacman.x))
		&& (std::floor(ghost.y) == std::floor(pacman.y))
			&& !_eatGhosts)
		reset();
	if ((std::floor(ghost.x) == std::floor(pacman.x))
		&& (std::floor(ghost.y) == std::floor(pacman.y))
			&& _eatGhosts) {
		_score += 500;
		ghost.x = 13;
		ghost.y = 14;
	}
}

void arc::Pacman::reset()
{
	std::string S;

	_map.clear();
	_mapItems.clear();
	_ghostDirection.clear();
	_eating = 0;
	_ghNbr = 0;
	_score = 0;
	_eatGhosts = false;
	_Over = false;
	_direction = arc::Interaction::MOVE_RIGHT;
	_startTimer = std::chrono::high_resolution_clock::now();
	std::ifstream F ("./games/pacman/pacman_map.txt", std::ifstream::in);
	if (!F)
		throw arc::Exception("Cannot initialise file stream",
					"Pacman");
	while (getline(F, S))
		_map.push_back(S);
	setItems();
}

void arc::Pacman::checkIntersec(arc::Item &item,
				arc::Interaction &dir,
				arc::Item &pac) noexcept
{
	arc::Interaction key = arc::Interaction::MOVE_LEFT;
	std::vector<Interaction> available;

	if (isAWall(key, item.x, item.y) && dir != Interaction::MOVE_RIGHT)
		available.push_back(key);
	key = arc::Interaction::MOVE_RIGHT;
	if (isAWall(key, item.x, item.y) && dir != Interaction::MOVE_LEFT)
		available.push_back(key);
	key = arc::Interaction::MOVE_DOWN;
	if (isAWall(key, item.x, item.y) && dir != Interaction::MOVE_UP)
		available.push_back(key);
	key = arc::Interaction::MOVE_UP;
	if (isAWall(key, item.x, item.y) && dir != Interaction::MOVE_DOWN)
		available.push_back(key);
	if(available.empty()) {
		goInReverse(dir);
		return;
	}
	chooseGhostStrategy(item, available, dir, pac);

}

void arc::Pacman::goInReverse(arc::Interaction &dir) noexcept
{
	switch (dir) {
		case arc::Interaction::MOVE_LEFT:
			dir = arc::Interaction::MOVE_RIGHT;
			break;
		case arc::Interaction::MOVE_RIGHT:
			dir = arc::Interaction::MOVE_LEFT;
			break;
		case arc::Interaction::MOVE_UP:
			dir = arc::Interaction::MOVE_DOWN;
			break;
		case arc::Interaction::MOVE_DOWN:
			dir = arc::Interaction::MOVE_UP;
			break;
		default:
			return;
	}
}

void arc::Pacman::chooseGhostStrategy(arc::Item &ghost,
					std::vector<Interaction> &available,
					arc::Interaction &dir,
					arc::Item &pac) noexcept
{
	int choice = rand() % 3;

	if (!_eatGhosts) {
		if (choice < 2 && _score > 200)
			ghostFollowPacman(ghost, available, dir, pac);
		else
			chooseGhostDirection(available, dir);
	}
	else
		ghostFearPacman(ghost, available, dir, pac);
}

void arc::Pacman::ghostFollowPacman(arc::Item &ghost,
					std::vector<Interaction> &dirAv,
					arc::Interaction &dir,
					arc::Item &pac) noexcept
{
	if (pac.y < ghost.y &&
			isDirAvailable(dirAv, Interaction::MOVE_UP))
		dir = Interaction::MOVE_UP;
	else if (pac.y > ghost.y &&
			isDirAvailable(dirAv, Interaction::MOVE_DOWN))
		dir = Interaction::MOVE_DOWN;
	else if (pac.x < ghost.x && isDirAvailable(dirAv, Interaction::MOVE_LEFT))
		dir = Interaction::MOVE_LEFT;
	else if (pac.x > ghost.x &&
			isDirAvailable(dirAv, Interaction::MOVE_RIGHT))
		dir = Interaction::MOVE_RIGHT;
	else
		dir = dirAv.front();
}

void arc::Pacman::ghostFearPacman(arc::Item &ghost,
					std::vector<Interaction> &dirAv,
					arc::Interaction &dir,
					arc::Item &pac) noexcept
{
	if (pac.y < ghost.y &&
			isDirAvailable(dirAv, Interaction::MOVE_DOWN))
		dir = Interaction::MOVE_DOWN;
	else if (pac.y > ghost.y &&
			isDirAvailable(dirAv, Interaction::MOVE_UP))
		dir = Interaction::MOVE_UP;
	else if (pac.x < ghost.x && isDirAvailable(dirAv, Interaction::MOVE_RIGHT))
		dir = Interaction::MOVE_RIGHT;
	else if (pac.x > ghost.x &&
			isDirAvailable(dirAv, Interaction::MOVE_LEFT))
		dir = Interaction::MOVE_LEFT;
	else
		dir = dirAv.front();
}

bool arc::Pacman::isDirAvailable(std::vector<Interaction> &available,
					arc::Interaction dir) noexcept
{
	if (std::find(available.begin(), available.end(),
		dir) == std::end(available))
		return false;
	else
		return true;
}

void arc::Pacman::chooseGhostDirection(std::vector<Interaction> &vec,
					arc::Interaction &dir) noexcept
{
	int rnd;
	int i = 0;

	rnd = vec.size();
	if (rnd > 1) {
		rnd = rand() % rnd;
		for (auto it = vec.begin(); it < vec.end(); it++) {
			if (i == rnd)
				dir = *it;
			i++;
		}
	} else {
		dir = vec.front();
	}
}

void arc::Pacman::autorun(arc::Item &item)
{
	if (_eatGhosts)
		checkTime();
	_eating += 0.15;
	if (_eating > 2) {
		item.currSpriteIdx = 0;
		_eating = 0;
	}
	else if (_eating > 1)
		item.currSpriteIdx = 1;
	if (isAWall(_direction, item.x, item.y)) {
		movePos(_direction, item);
		if(!removePacgum(item.x, item.y))
			eatSuperPacgum(item);
		teleport(item);
	}
}

void arc::Pacman::checkTime() noexcept
{
	auto newTime = std::chrono::high_resolution_clock::now();
	millisec diff = newTime - _startTimer;

	if (diff.count() >= 10000)
		_eatGhosts = false;
}

void arc::Pacman::eatSuperPacgum(const Item &item) noexcept
{
	std::string pacG = "Spacgum";
	int x = std::floor(item.x + 0.5);
	int y = std::floor(item.y + 0.5);

	pacG += std::to_string(y) + '_' +
		std::to_string(x);
	if (removeItem(pacG)) {
		_score += 300;
		_startTimer = std::chrono::high_resolution_clock::now();
		_eatGhosts = true;
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

bool arc::Pacman::removePacgum(const float x, const float y) noexcept
{
	std::string pacG = "pacgum";
	int xp = std::floor(x + 0.5);
	int yp = std::floor(y + 0.5);

	pacG += std::to_string(yp) + '_' +
		std::to_string(xp);
	if (removeItem(pacG)) {
		_score += 10;
		return true;
	}
	return false;
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
	if (check1 != ' ' && check1 != 'P' && check1 != '.' && check1 != 'G' && 	check1 != 'D' && check1 != 'H' && check1 != 'S')
		return false;
	else if (check2 != ' ' && check2 != 'P' && check2 != '.' &&
			check2 != 'G' && check2 != 'D' && check2 != 'H' &&
			check2 != 'S')
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

void arc::Pacman::movePosGhost(Interaction &key, Item &item) noexcept
{
	switch (key) {
		case arc::Interaction::MOVE_LEFT:
			item.x -= 0.1;
			break;
		case arc::Interaction::MOVE_RIGHT:
			item.x += 0.1;
			break;
		case arc::Interaction::MOVE_UP:
			item.y -= 0.1;
			break;
		case arc::Interaction::MOVE_DOWN:
			item.y += 0.1;
			break;
		default:
			return;
	}
}

arc::Item &arc::Pacman::getItemFromName(const std::string &name)
{
	std::string err;
	for (auto it = _mapItems.begin(); it < _mapItems.end(); it++) {
		if (it->name == name)
			return *it;
	}
	err += "Item name: " + name + " don't exist";
	throw arc::Exception(err, "Pacman");
	return *_mapItems.begin();
}

bool arc::Pacman::removeItem(const std::string &name)
{

	for (auto it = _mapItems.begin(); it < _mapItems.end(); it++) {
		if (it->name == name) {
			_mapItems.erase(it);
			return true;
		}
	}
	return false;
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

int arc::Pacman::getScore() noexcept
{
	return _score;
}

bool arc::Pacman::isOver() const noexcept
{
	return _Over;
}
