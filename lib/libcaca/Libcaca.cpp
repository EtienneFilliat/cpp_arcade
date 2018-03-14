/*
** EPITECH PROJECT, 2018
** Project
** File description:
** Created by hexa,
*/

#include <iostream>
#include "Libcaca.hpp"
#include "Exception.hpp"

extern "C" arc::IDisplay *create_object()
{
	return new Libcaca;
}

Libcaca::Libcaca()
{
	this->_window = caca_create_display(nullptr);
	if (!this->_window)
		throw arc::Exception("Cannot create window", "LibCaca");
	this->_canvas = caca_get_canvas(this->_window);
	caca_set_color_ansi(this->_canvas, CACA_WHITE, CACA_BLACK);
}

Libcaca::~Libcaca()
{
	caca_free_canvas(this->_canvas);
	caca_free_display(this->_window);
}

arc::KeysList Libcaca::getKeys()
{
	arc::KeysList keys_cpy;
	arc::KeysList empty;

	this->setKeys();
	keys_cpy = this->_keys;
	std::swap(this->_keys, empty);
	return (keys_cpy);
}

void Libcaca::drawSprite(const arc::Item &sprite)
{
	caca_put_char(this->_canvas, sprite.x, sprite.y, sprite.spriteChar);
}

void Libcaca::clear()
{
	caca_clear_canvas(this->_canvas);
}

void Libcaca::refresh()
{
	caca_refresh_display(this->_window);
}

void Libcaca::setKeys()
{
	caca_event_t event;

	caca_get_event(this->_window, CACA_EVENT_KEY_PRESS, &event, 0);
	if (event.data.key.ch == 'z')
		this->_keys.push(arc::Keys::MOVE_UP);
	else if (event.data.key.ch == 's')
		this->_keys.push(arc::Keys::MOVE_DOWN);
	else if (event.data.key.ch == 'q')
		this->_keys.push(arc::Keys::MOVE_LEFT);
	else if (event.data.key.ch == 'd')
		this->_keys.push(arc::Keys::MOVE_RIGHT);
	else if (event.data.key.ch == 'o')
		this->_keys.push(arc::Keys::PREV_LIB);
	else if (event.data.key.ch == 'p')
		this->_keys.push(arc::Keys::NEXT_LIB);
	else if (event.data.key.ch == 'l')
		this->_keys.push(arc::Keys::PREV_GAME);
	else if (event.data.key.ch == 'm')
		this->_keys.push(arc::Keys::NEXT_GAME);
	else if (event.data.key.ch == 27)
		this->_keys.push(arc::Keys::QUIT);
}
