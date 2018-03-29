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

	/* Controls Interactions */

	enum Interaction {
		MOVE_UP,
		MOVE_DOWN,
		MOVE_LEFT,
		MOVE_RIGHT,
		ACTION_1,
		LIB_NEXT,
		LIB_PREV,
		GAME_NEXT,
		GAME_PREV,
		QUIT,
	};

	using InteractionList = std::queue<Interaction>;

	/* Position */

	struct Position {
		int x;
		int y;
		Interaction interact;
	};

	/* Colors */

	enum Color {
		BLUE,
		RED,
		GREEN,
		YELLOW,
		CYAN,
		MAGENTA,
		WHITE,
		BLACK,
		UNDEFINED,
		DFT_COLOR_RET_ERROR,
	};

	/* Sprites & Items */

	struct Sprite {
		int x;
		int y;
		int rotation;
		char substitute;
		std::string name;
		std::string path;
		Color color;
	};

	using SpriteList = std::vector<Sprite>;

	struct Item {
		std::string name;
		std::string spritesPath;
		SpriteList sprites;
		int currSpriteIdx;
		float x;
		float y;
	};

	using ItemList = std::vector<Item>;
}

#endif /* !ARC_HPP_ */
