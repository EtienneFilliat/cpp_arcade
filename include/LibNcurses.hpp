/*
** EPITECH PROJECT, 2018
** Project
** File description:
** Created by hexa,
*/

#ifndef PROJECT_LIBNCURSES_HPP
	#define PROJECT_LIBNCURSES_HPP
	#include <ncurses.h>
	#include "IDisplay.hpp"
class LibNcurses : public arc::IDisplay
{
public:
	LibNcurses();
	~LibNcurses() override;
	arc::KeysList getKeys();
	void drawSprite(const arc::Item &sprite);
	void refresh();
	void clear();
private:
	arc::KeysList _keys;
	WINDOW *_window;
	void setKeys();
};
#endif //PROJECT_LIBNCURSES_HPP
