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

namespace arc {
	class LibNcurses;
}

class arc::LibNcurses : public arc::IDisplay
{
public:
	LibNcurses();
	~LibNcurses() final;
	void clear() final;
	void refresh() final;
	void putStr(const std::string &, int x, int y) final;
	void putItem(const arc::Item &) final;
	void putItem(const arc::Item &, int, int) final;
	void putItem(const arc::Item &,
		const std::vector<struct arc::Position> &) final;
	void setStep(uint) final;
	arc::InteractionList getInteractions() final;
private:
	arc::InteractionList _interactions;
	WINDOW *_window;
	uint _step;
	void setInteractions();
	void initColorPairs();
	void setColor(const Color &color);
};
#endif //PROJECT_LIBNCURSES_HPP
