/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** IGame
*/

#ifndef IGAME_HPP_
	#define IGAME_HPP_

	#include <string>
	#include <vector>
	#include "IDisplay.hpp"

namespace arc {

class IGame {
public:
	struct Specs {
		int x;
		int y;
		uint pixelStep;
		uint fps;
	};

	virtual ~IGame() = default;
	// virtual void dump() const noexcept = 0;
	virtual const ItemList &getItems() const noexcept = 0;
	//virtual Item &getItemFromName(const std::string &) = 0;
	virtual const Specs &getSpecs() const noexcept = 0;
	virtual bool processInteraction(Interaction &) noexcept = 0;
	virtual void envUpdate() noexcept = 0;
	//virtual const std::vector<struct Position> &getBulletPos() = 0;
};
};

#endif /* !IGAME_HPP_ */
