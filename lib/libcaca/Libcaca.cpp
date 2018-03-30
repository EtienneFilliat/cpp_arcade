/*
** EPITECH PROJECT, 2018
** Project
** File description:
** Created by hexa,
*/

#include <iostream>
#include <memory>
#include <thread>
#include "Libcaca.hpp"
#include "Exception.hpp"

extern "C" std::unique_ptr<arc::IDisplay> create_object()
{
	std::unique_ptr<arc::IDisplay> ptr(new arc::Libcaca);
	return std::move(ptr);
}

arc::Libcaca::Libcaca()
{
	this->_window = caca_create_display(nullptr);
	if (!this->_window)
		throw arc::Exception("Cannot create window", "LibCaca");
	this->_canvas = caca_get_canvas(this->_window);
	caca_set_color_ansi(this->_canvas, CACA_WHITE, CACA_BLACK);
	this->_step = 1;
}

arc::Libcaca::~Libcaca()
{
	caca_free_canvas(this->_canvas);
	caca_free_display(this->_window);
}

void arc::Libcaca::clear()
{
	caca_clear_canvas(this->_canvas);
}

void arc::Libcaca::refresh()
{
	caca_refresh_display(this->_window);
}

void arc::Libcaca::putStr(const std::string &str, int x, int y)
{
	caca_put_str(this->_canvas, x, y, str.c_str());
}

void arc::Libcaca::putItem(const arc::Item & item)
{
	uint32_t c;

	caca_set_color_ansi(this->_canvas,
				getColor(item.sprites[item.currSpriteIdx].
				color),
				getColor(item.sprites[item.currSpriteIdx].
				background));
	c = static_cast<uint32_t>(item.sprites[item.currSpriteIdx].substitute);
	caca_put_char(this->_canvas,
		item.x / this->_step,
		item.y / this->_step,
		c);
	caca_set_color_ansi(this->_canvas, CACA_WHITE, CACA_BLACK);
}

void arc::Libcaca::putItem(const arc::Item &item, int x, int y)
{
	uint32_t c;

	c = static_cast<uint32_t>(item.sprites[item.currSpriteIdx].substitute);
	caca_put_char(this->_canvas, x / this->_step, y / this->_step, c);
}

void arc::Libcaca::putItem(const arc::Item &item,
	const std::vector<struct Position> &position)
{
	uint32_t c;
	auto it = position.begin();

	c = static_cast<uint32_t>(item.sprites[item.currSpriteIdx].substitute);

	while (it != position.end()) {
		caca_put_char(this->_canvas,
			(*it).x / this->_step,
			(*it).y / this->_step,
			c);
		std::next(it);
	}
}

caca_color arc::Libcaca::getColor(const Color &color)
{
	switch (color) {
		case Color::BLACK:
			return CACA_BLACK;
		case Color::RED:
			return CACA_RED;
		case Color::GREEN:
			return CACA_GREEN;
		case Color::BLUE:
			return CACA_BLUE;
		case Color::YELLOW:
			return CACA_YELLOW;
		case Color::CYAN:
			return CACA_CYAN;
		case Color::MAGENTA:
			return CACA_MAGENTA;
		case Color::WHITE:
			return CACA_WHITE;
		default:
			return CACA_BLACK;
	}
}

arc::InteractionList arc::Libcaca::getInteractions(){
	arc::InteractionList Interaction_cpy;
	arc::InteractionList empty;
	millisec wait(40);

	std::this_thread::sleep_for(wait);
	this->setInteractions();
	Interaction_cpy = this->_interactions;
	std::swap(this->_interactions, empty);
	return (Interaction_cpy);
}

void arc::Libcaca::setStep(uint step)
{
	if (step > 0)
		this->_step = step;
}

void arc::Libcaca::setInteractions(){
	caca_event_t event;

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
