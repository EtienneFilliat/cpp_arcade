/*
** EPITECH PROJECT, 2018
** Project
** File description:
** Created by hexa,
*/

#ifndef PROJECT_LIBCACA_HPP
	#define PROJECT_LIBCACA_HPP
	#include <caca.h>
	#include "IDisplay.hpp"
class Libcaca : public arc::IDisplay
{
public:
	Libcaca();
	~Libcaca() override;
	arc::KeysList getKeys();
	void drawSprite(const arc::Item &sprite);
	void refresh();
	void clear();
private:
	arc::KeysList _keys;
	caca_display_t *_window;
	caca_canvas_t *_canvas;
	void setKeys();
};
#endif //PROJECT_LIBCACA_HPP
