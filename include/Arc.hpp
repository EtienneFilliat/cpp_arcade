/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Arc
*/

#ifndef ARC_HPP_
	#define ARC_HPP_

	#include <queue>
	#include <string>
	#include <vector>

namespace arc {
	enum Keys {
		MOVE_UP,
		MOVE_DOWN,
		MOVE_LEFT,
		MOVE_RIGHT,
		NEXT_LIB,
		PREV_LIB,
		NEXT_GAME,
		PREV_GAME,
		QUIT,
	};
	using KeysList = std::queue<Keys>;

	struct Item {
		std::string name;
		std::string spritePath;
		uint8_t spriteChar;
		int x;
		int y;

	};
	using ItemList = std::vector<Item>;
}

#endif /* !ARC_HPP_ */
