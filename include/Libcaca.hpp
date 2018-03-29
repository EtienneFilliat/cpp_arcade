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
namespace arc {
	class Libcaca;
}
class arc::Libcaca : public arc::IDisplay
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
		const std::vector<struct arc::Position> &) final;
	void setStep(uint) final;
	arc::InteractionList getInteractions() final;
private:
	arc::InteractionList _interactions;
	caca_display_t *_window;
	caca_canvas_t *_canvas;
	uint _step;
	void setInteractions();
	caca_color getColor(const arc::Color &);
};

#endif //PROJECT_LIBCACA_HPP
