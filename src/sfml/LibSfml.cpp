/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** LibSfml
*/

#include <stdexcept>
#include <iostream>
#include "LibSfml.hpp"

arc::LibSfml::LibSfml()
{
	_window.create(sf::VideoMode(200, 200), "Cpp_Arcade");
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
	_window.display();
}

void arc::LibSfml::clear()
{
	_window.clear();
}

void arc::LibSfml::drawSprite(const arc::Item &item)
{
	auto sprite = std::unique_ptr<sf::Sprite>(new sf::Sprite);
	sf::Texture texture;
	sf::Vector2f pos;
	auto search = _map.find(item.name);

	// std::cout << "item.x = " << item.x << std::endl;
	// std::cout << "item.y = " << item.y << std::endl;
	if (search == _map.end()) {
		texture.loadFromFile(item.spritePath);
		sprite->setTexture(texture);
		sprite->setPosition(item.x, item.y);
		pos = sprite->getPosition();
		_window.draw(*sprite);
		_map.emplace(item.name, std::move(sprite));
	} else {
		search->second->setPosition(item.x, item.y);
		_window.draw(*search->second);
	}
	std::cout << "x = " << pos.x << std::endl;
	std::cout << "y = " << pos.y << std::endl;
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
