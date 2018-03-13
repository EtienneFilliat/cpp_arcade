//
// EPITECH PROJECT, 2018
// arcade
// File description:
// game lib manager cpp
//

#include <memory>
#include "LoadedGame.hpp"

arc::LoadedGame::LoadedGame(arc::IGame *gameObject)
	: _object(gameObject)
{}

arc::LoadedGame::~LoadedGame()
{}
