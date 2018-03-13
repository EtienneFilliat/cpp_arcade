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
	typedef void (*fptrDestroy) (IGame *);
	public:
		Core();
		~Core();
		void loadLibs();
		void loadLibz();
		void clean();
	private:
		DynamicLib<IGame> _gameLib;
		DynamicLib<IGame> _displayLib;
		std::unique_ptr<IGame> _game;
		std::unique_ptr<IDisplay> _display;
		fptrDestroy _destroyGame;
	};
}

#endif /* !CORE_HPP_ */