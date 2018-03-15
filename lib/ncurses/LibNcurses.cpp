/*
** EPITECH PROJECT, 2018
** Project
** File description:
** Created by hexa,
*/

#include <iostream>
#include <memory>
#include "LibNcurses.hpp"
#include "Exception.hpp"

extern "C" std::unique_ptr<arc::IDisplay> create_object()
{
	std::unique_ptr<arc::IDisplay> ptr(new LibNcurses);
	return std::move(ptr);
}

LibNcurses::LibNcurses()
	: _window(nullptr)
{
	this->_window = initscr();
	if (this->_window == nullptr)
		throw arc::Exception("Cannot init window", "LibNCurses");
	noecho();
	nodelay(this->_window, true);
	curs_set(0);
}

LibNcurses::~LibNcurses()
{
	endwin();
}

void LibNcurses::closeWindow()
{
	this->~LibNcurses();
}

void LibNcurses::clear()
{
	wclear(this->_window);
}

void LibNcurses::refresh()
{
	wrefresh(this->_window);
}

arc::KeysList LibNcurses::getKeys()
{
	arc::KeysList keys_cpy;
	arc::KeysList empty;

	this->setKeys();
	keys_cpy = this->_keys;
	std::swap(this->_keys, empty);
	return (keys_cpy);
}

void LibNcurses::setKeys()
{
	int key;

	key = getch();
	if (key == 'q')
		this->_keys.push(arc::Keys::MOVE_LEFT);
	else if (key == 'd')
		this->_keys.push(arc::Keys::MOVE_RIGHT);
	else if (key == 'z')
		this->_keys.push(arc::Keys::MOVE_UP);
	else if (key == 's')
		this->_keys.push(arc::Keys::MOVE_DOWN);
	else if (key == 'o')
		this->_keys.push(arc::Keys::PREV_LIB);
	else if (key == 'p')
		this->_keys.push(arc::Keys::NEXT_LIB);
	else if (key == 'l')
		this->_keys.push(arc::Keys::PREV_GAME);
	else if (key == 'm')
		this->_keys.push(arc::Keys::NEXT_GAME);
	else if (key == 27)
		this->_keys.push(arc::Keys::QUIT);
}

void LibNcurses::drawSprite(const arc::Item &sprite)
{
	mvwprintw(this->_window, sprite.y, sprite.x, "%c", sprite.spriteChar);
}