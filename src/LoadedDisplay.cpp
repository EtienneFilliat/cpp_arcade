//
// EPITECH PROJECT, 2018
// arcade
// File description:
// display lib manager cpp
//

#include <memory>
#include "LoadedDisplay.hpp"

arc::LoadedDisplay::LoadedDisplay(IDisplay *gameObject)
	: _object(gameObject)
{}

arc::LoadedDisplay::~LoadedDisplay()
{}
