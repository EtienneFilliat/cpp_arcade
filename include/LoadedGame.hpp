//
// EPITECH PROJECT, 2018
// arcade
// File description:
// game lib manager hpp
//


#ifndef LOADEDGAME_HPP_
	#define LOADEDGAME_HPP_
	#include <string>
	#include <memory>
	#include "IGame.hpp"

namespace arc {

	class LoadedGame {
	public:
		LoadedGame(arc::IGame *libObject);
		~LoadedGame();
	private:
		std::unique_ptr<arc::IGame> _object;
	};
}

#endif /* !LOADEDGAME_HPP_ */
