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
	private:
		DynamicLib<IGame> _gameLib;
		DynamicLib<IDisplay> _displayLib;
		std::unique_ptr<IGame> _game;
		std::unique_ptr<IDisplay> _display;
	};
}

#endif /* !CORE_HPP_ */