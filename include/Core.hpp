//
// EPITECH PROJECT, 2018
// arcade
// File description:
// core hpp
//

#ifndef CORE_HPP_
	#define CORE_HPP_
	#include <memory>
	#include "IGame.hpp"
	#include "IDisplay.hpp"
	#include "DynamicLib.hpp"

namespace arc {

	class Core {
	public:
		Core();
		~Core();
		void launchGame();
		void gameLoop(Item &item);
		void switchGraphics(const std::string &cmd);
		bool computeKeys(arc::Item &item, KeysList &keys);
	private:
		DynamicLib<IGame> _gameLib;
		DynamicLib<IDisplay> _displayLib;
		std::unique_ptr<IGame> _game;
		std::unique_ptr<IDisplay> _display;
		std::vector<std::string> _displayList;
		std::vector<std::string>::iterator _it;
	};
}

#endif /* !CORE_HPP_ */