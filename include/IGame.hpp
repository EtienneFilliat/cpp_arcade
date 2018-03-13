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
		struct GridInfo {
			int x;
			int y;
			int pixelStep;
		};

		struct Item {
			std::string name;
			std::string spritePath;
			int x;
			int y;

		};
		using ItemList = std::vector<Item>;

		virtual ~IGame() = default;
		virtual ItemList &getItemList() = 0;
		virtual GridInfo &getGridInfo() = 0;
		virtual void ComputeKey(IDisplay::Keys &) = 0;
	};
}

#endif /* !IGAME_HPP_ */
