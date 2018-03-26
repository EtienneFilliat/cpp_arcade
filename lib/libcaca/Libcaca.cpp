/*
** EPITECH PROJECT, 2018
** Project
** File description:
** Created by hexa,
*/

#include <iostream>
#include <memory>
#include "Libcaca.hpp"
#include "Exception.hpp"

extern "C" std::unique_ptr<arc::IDisplay> create_object()
{
	std::unique_ptr<arc::IDisplay> ptr(new Libcaca);
	return std::move(ptr);
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

void Libcaca::clear()
{
	caca_clear_canvas(this->_canvas);
}

void Libcaca::refresh()
{
	caca_refresh_display(this->_window);
}

void Libcaca::putStr(const std::string &str, int x, int y)
{
	caca_put_str(this->_canvas, x, y, str.c_str());
}

void Libcaca::putItem(const arc::Item & item)
{
	uint32_t c;

	c = static_cast<uint32_t>(item.sprites[item.currSpriteIdx].substitute);
	caca_put_char(this->_canvas, item.x, item.y, c);
}

void Libcaca::putItem(const arc::Item &item, int x, int y)
{
	uint32_t c;

	c = static_cast<uint32_t>(item.sprites[item.currSpriteIdx].substitute);
	caca_put_char(this->_canvas, x, y, c);
}

void Libcaca::putItem(const arc::Item &item,
	const std::vector<struct Position> &position)
{
	uint32_t c;
	auto it = position.begin();

	c = static_cast<uint32_t>(item.sprites[item.currSpriteIdx].substitute);

	while (it != position.end()) {
		caca_put_char(this->_canvas, (*it).x, (*it).y, c);
		std::next(it);
	}
}

arc::InteractionList Libcaca::getInteractions(){
	arc::InteractionList Interaction_cpy;
	arc::InteractionList empty;

	this->setInteractions();
	Interaction_cpy = this->_interactions;
	std::swap(this->_interactions, empty);
	return (Interaction_cpy);
}

void Libcaca::setInteractions(){
	caca_event_t event = nullptr;

	caca_get_event(this->_window, CACA_EVENT_KEY_PRESS, &event, 0);
	if (event.data.key.ch == 'z')
		this->_interactions.push(arc::Interaction::MOVE_UP);
	else if (event.data.key.ch == 's')
		this->_interactions.push(arc::Interaction::MOVE_DOWN);
	else if (event.data.key.ch == 'q')
		this->_interactions.push(arc::Interaction::MOVE_LEFT);
	else if (event.data.key.ch == 'd')
		this->_interactions.push(arc::Interaction::MOVE_RIGHT);
	else if (event.data.key.ch == 'o')
		this->_interactions.push(arc::Interaction::LIB_PREV);
	else if (event.data.key.ch == 'p')
		this->_interactions.push(arc::Interaction::LIB_NEXT);
	else if (event.data.key.ch == 'l')
		this->_interactions.push(arc::Interaction::GAME_PREV);
	else if (event.data.key.ch == 'm')
		this->_interactions.push(arc::Interaction::GAME_NEXT);
	else if (event.data.key.ch == 27)
		this->_interactions.push(arc::Interaction::QUIT);
}
