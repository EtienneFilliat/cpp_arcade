/*
** EPITECH PROJECT, 2018
** Project
** File description:
** Created by hexa,
*/

#include <iostream>
#include <memory>
#include <thread>
#include <unistd.h>
#include "LibNcurses.hpp"
#include "Exception.hpp"

extern "C" std::unique_ptr<arc::IDisplay> create_object()
{
	std::unique_ptr<arc::IDisplay> ptr(new arc::LibNcurses);
	return std::move(ptr);
}

arc::LibNcurses::LibNcurses()
	: _window(nullptr), _step(1)
{
	this->_window = initscr();
	start_color();
	if (this->_window == nullptr)
		throw arc::Exception("Cannot init window", "LibNCurses");
	noecho();
	nodelay(this->_window, true);
	curs_set(0);
	this->initColorPairs();
}

void arc::LibNcurses::initColorPairs()
{
	init_pair(0, COLOR_BLACK, COLOR_BLACK);
	init_pair(1, COLOR_BLUE, COLOR_BLUE);
	init_pair(2, COLOR_YELLOW, COLOR_BLACK);
	init_pair(3, COLOR_CYAN, COLOR_BLACK);
}

void arc::LibNcurses::setColor(const Color &color)
{
	switch (color) {
		case Color::BLUE:
			attron(COLOR_PAIR(1));
			break;
		case Color::YELLOW:
			attron(COLOR_PAIR(2));
			break;
		case Color::CYAN:
			attron(COLOR_PAIR(3));
			break;
		default:
			attron(COLOR_PAIR(0));
	}
}

arc::LibNcurses::~LibNcurses()
{
	endwin();
}

void arc::LibNcurses::clear()
{
	werase(this->_window);
}

void arc::LibNcurses::refresh()
{
	millisec wait(40);

	wrefresh(this->_window);
	std::this_thread::sleep_for(wait);
}

void arc::LibNcurses::putStr(const std::string &str, int x, int y)
{
	mvwprintw(this->_window, y, x, "%s", str.c_str());
}

void arc::LibNcurses::putItem(const arc::Item & item)
{
	uint32_t c;

	setColor(item.sprites[item.currSpriteIdx].color);
	c = static_cast<uint32_t>(item.sprites[item.currSpriteIdx].substitute);
	mvwprintw(this->_window,
		item.y / this->_step,
		item.x / this->_step,
		"%c", c);
	attron(COLOR_PAIR(0));
}

void arc::LibNcurses::putItem(const arc::Item &item, int x, int y)
{
	uint32_t c;

	c = static_cast<uint32_t>(item.sprites[item.currSpriteIdx].substitute);
	mvwprintw(this->_window, y / this->_step, x / this->_step, "%c", c);
}

void arc::LibNcurses::putItem(const arc::Item &item,
	const std::vector<struct Position> &position)
{
	uint32_t c;
	auto it = position.begin();

	c = static_cast<uint32_t>(item.sprites[item.currSpriteIdx].substitute);

	while (it != position.end()) {
		mvwprintw(this->_window,
			(*it).y / this->_step,
			(*it).x / this->_step,
			"%c", c);
		std::next(it);
	}
}

void arc::LibNcurses::setStep(uint step)
{
	if (step > 0)
		this->_step = step;
}

arc::InteractionList arc::LibNcurses::getInteractions(){
	arc::InteractionList Interaction_cpy;
	arc::InteractionList empty;

	this->setInteractions();
	Interaction_cpy = this->_interactions;
	std::swap(this->_interactions, empty);
	return (Interaction_cpy);
}

void arc::LibNcurses::setInteractions()
{
	int key;

	key = getch();
	if (key == 'q')
		this->_interactions.push(arc::Interaction::MOVE_LEFT);
	else if (key == 'd')
		this->_interactions.push(arc::Interaction::MOVE_RIGHT);
	else if (key == 'z')
		this->_interactions.push(arc::Interaction::MOVE_UP);
	else if (key == 's')
		this->_interactions.push(arc::Interaction::MOVE_DOWN);
	else if (key == 'o')
		this->_interactions.push(arc::Interaction::LIB_PREV);
	else if (key == 'p')
		this->_interactions.push(arc::Interaction::LIB_NEXT);
	else if (key == 'l')
		this->_interactions.push(arc::Interaction::GAME_PREV);
	else if (key == 'm')
		this->_interactions.push(arc::Interaction::GAME_NEXT);
	else if (key == 27)
		this->_interactions.push(arc::Interaction::QUIT);
}
