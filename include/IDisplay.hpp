/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** IDisplay
*/

#ifndef IDISPLAY_HPP_
	#define IDISPLAY_HPP_

	#include "Arc.hpp"

namespace arc {

class IDisplay {
public:
	virtual ~IDisplay() = default;
	virtual KeysList getKeys() = 0;
	virtual void drawSprite(const Item &) = 0;
	virtual void refresh() = 0;
	virtual void clear() = 0;
	virtual void drawSprite(const Item &) = 0;
};
}

#endif /* !IDISPLAY_HPP_ */
