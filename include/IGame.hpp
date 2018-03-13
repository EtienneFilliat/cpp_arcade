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
	class IGame;
};

class arc::IGame {
public:
	struct GridInfo {
		int x;
		int y;
		int pixelStep;
	};

	virtual ~IGame() = default;
	virtual arc::ItemList &getItemList() = 0;
	virtual GridInfo &getGridInfo() = 0;
	virtual void ComputeKey(arc::Keys &) = 0;
};

#endif /* !IGAME_HPP_ */
