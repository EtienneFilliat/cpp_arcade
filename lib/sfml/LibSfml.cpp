/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** LibSfml
*/

#include <iostream>
#include <memory>
#include "LibSfml.hpp"
#include "Exception.hpp"

extern "C" std::unique_ptr<arc::IDisplay> create_object()
{
	std::unique_ptr<arc::IDisplay> ptr(new arc::LibSfml);
	return std::move(ptr);
}

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
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::O))
			_key.push(arc::Keys::PREV_LIB);
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
			_key.push(arc::Keys::NEXT_LIB);
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
			_key.push(arc::Keys::PREV_GAME);
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
			_key.push(arc::Keys::NEXT_GAME);
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			_key.push(arc::Keys::QUIT);
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
	auto texture = std::unique_ptr<sf::Texture>(new sf::Texture);
	auto sp = std::unique_ptr<spriteStruct>(new spriteStruct);
	auto search = _map.find(item.name);

	if (search == _map.end()) {
		if (!texture->loadFromFile(item.spritePath))
			throw arc::Exception("Cannot load sprite", "LibSFML");
		sprite->setTexture(*texture);
		sprite->setPosition(item.x, item.y);
		std::cout << item.name << std::endl;
		_window.draw(*sprite);
		sp->sprite = std::move(sprite);
		sp->texture = std::move(texture);
		_map.emplace(item.name, std::move(sp));
	} else {
		search->second->sprite->setPosition(item.x, item.y);
		_window.draw(*search->second->sprite);
	}
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
