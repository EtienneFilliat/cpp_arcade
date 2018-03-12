//
// EPITECH PROJECT, 2018
// arcade
// File description:
// game lib manager cpp
//

#include "IGame.hpp"
#include "GameLibManager.hpp"

GameLibManager::GameLibManager(IGame *libObject)
	: _object(libObject)
{}

GameLibManager::~GameLibManager()
{}

void GameLibManager::display()
{
	_object->displaySomeShit();
}
