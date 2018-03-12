//
// EPITECH PROJECT, 2018
// arcade
// File description:
// game lib manager hpp
//


#ifndef GAMELIBMANAGER_HPP_
	#define GAMELIBMANAGER_HPP_
	#include <string>
	#include <memory>
	#include "IGame.hpp"

	class GameLibManager {
		public:
			GameLibManager(IGame *libObject);
			~GameLibManager();
			void display();

		private:
			std::unique_ptr<IGame> _object;
	};

#endif /* !GAMELIBMANAGER_HPP_ */
