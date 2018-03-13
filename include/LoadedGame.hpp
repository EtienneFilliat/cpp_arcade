//
// EPITECH PROJECT, 2018
// arcade
// File description:
// game lib manager hpp
//


#ifndef LOADEDGAME_HPP_
	#define LOADEDGAME_HPP_
	#include <memory>
	#include "IGame.hpp"

namespace arc {

	class LoadedGame {
	public:
		LoadedGame(IGame *gameObject);
		~LoadedGame();
	private:
		std::unique_ptr<IGame> _object;
	};
}

#endif /* !LOADEDGAME_HPP_ */
