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
	~Libcaca() final;
	void clear() final;
	void refresh() final;
	void putStr(const std::string &, int x, int y) final;
	void putItem(const arc::Item &) final;
	void putItem(const arc::Item &, int, int) final;
	void putItem(const arc::Item &,
		const std::vector<struct Position> &) final;
	arc::InteractionList getInteractions() final;
private:
	arc::InteractionList _interactions;
	caca_display_t *_window;
	caca_canvas_t *_canvas;
	void setInteractions();
};
#endif //PROJECT_LIBCACA_HPP
