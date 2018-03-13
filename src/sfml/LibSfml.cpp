/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** LibSfml
*/

#include "LibSfml.hpp"

arc::LibSfml::LibSfml()
	: _shape(100.f)
{
	_window.create(sf::VideoMode(200, 200), "Cpp_Arcade");
	_shape.setFillColor(sf::Color::Green);
}

arc::LibSfml::~LibSfml()
{
	_window.close();
}

void arc::LibSfml::setKeys() {
	if (_window.isOpen()) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
			_key.push(arc::Keys::MOVE_UP);
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			_key.push(arc::Keys::MOVE_DOWN);
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
			_key.push(arc::Keys::MOVE_LEFT);
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			_key.push(arc::Keys::MOVE_RIGHT);
	}
}

void arc::LibSfml::refresh()
{
	_window.draw(_shape);
	_window.display();

}

void arc::LibSfml::clear()
{
	_window.clear();
}

arc::KeysList arc::LibSfml::getKeys()
{
	arc::KeysList tmp;
	arc::KeysList empty;

	setKeys();
	tmp = _key;
	std::swap(_key, empty);
	return tmp;
}
