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
	_step = 1;
	_window.reset(new sf::RenderWindow(sf::VideoMode(900, 1000),
			"Cpp_Arcade"));
	if (!_window.get())
		throw arc::Exception("Cannot create window", "LibSFML");
}

arc::LibSfml::~LibSfml()
{
}

void arc::LibSfml::refresh()
{
	_window->display();
}

void arc::LibSfml::clear()
{
	_window->clear();
}

void arc::LibSfml::putStr(const std::string &str, int x, int y)
{
	//@TODO: il faut le faire mdr
	(void) str;
	(void) x;
	(void) y;
}

void arc::LibSfml::putItem(const arc::Item &item)
{
	auto sprite = std::unique_ptr<sf::Sprite>(new sf::Sprite);
	auto texture = std::unique_ptr<sf::Texture>(new sf::Texture);
	auto sp = std::unique_ptr<spriteStruct>(new spriteStruct);
	auto search = this->_map.find(item.name);
	int x = item.x * 32 + 16;
	int y = item.y * 32 + 16;
	std::string spritePath = item.sprites[item.currSpriteIdx].path;

	if (!texture->loadFromFile(spritePath))
		throw arc::Exception("Cannot load sprite", "LibSFML");
	if (search == this->_map.end()) {
		sprite->setTexture(*texture);
		sprite->setPosition(x / this->_step, y / this->_step);
		sprite->setOrigin(16, 16);
		sp->sprite = std::move(sprite);
		sp->texture = std::move(texture);
		this->_map.emplace(item.name, std::move(sp));
	} else {
		search->second->sprite->setTexture(*texture);
		search->second->sprite->setPosition(x, y);
		search->second->sprite->setRotation(
			item.sprites[item.currSpriteIdx].rotation);
		this->_window->draw(*search->second->sprite);
	}
}

void arc::LibSfml::putItem(const arc::Item &item, int x, int y)
{
	auto sprite = std::unique_ptr<sf::Sprite>(new sf::Sprite);
	auto texture = std::unique_ptr<sf::Texture>(new sf::Texture);
	auto sp = std::unique_ptr<spriteStruct>(new spriteStruct);
	auto search = this->_map.find(item.name);
	std::string spritePath = item.sprites[item.currSpriteIdx].path;

	if (!texture->loadFromFile(spritePath))
		throw arc::Exception("Cannot load sprite", "LibSFML");
	if (search == this->_map.end()) {
		sprite->setTexture(*texture);
		sprite->setPosition(x / this->_step, y / this->_step);
		sprite->setOrigin(16, 16);
		sp->sprite = std::move(sprite);
		sp->texture = std::move(texture);
		this->_map.emplace(item.name, std::move(sp));
	} else {
		search->second->sprite->setTexture(*texture);
		search->second->sprite->setPosition(x, y);
		search->second->sprite->setRotation(
			item.sprites[item.currSpriteIdx].rotation);
		this->_window->draw(*search->second->sprite);
	}
}

void arc::LibSfml::putItem(const arc::Item &item,
	const std::vector<struct Position> &position)
{
	auto it = position.begin();

	while (it != position.end()) {
		this->putItem(item,
			(*it).x / this->_step,
			(*it).y / this->_step);
		std::next(it);
	}
}

void arc::LibSfml::setStep(uint step)
{
	if (step > 0)
		this->_step = step;
}

void arc::LibSfml::setInteractions(){
	if (this->_window->isOpen()) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
			this->_interactions.push(arc::Interaction::MOVE_UP);
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			this->_interactions.push(arc::Interaction::MOVE_DOWN);
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
			this->_interactions.push(arc::Interaction::MOVE_LEFT);
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			this->_interactions.push(arc::Interaction::MOVE_RIGHT);
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::O))
			this->_interactions.push(arc::Interaction::LIB_PREV);
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
			this->_interactions.push(arc::Interaction::LIB_NEXT);
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
			this->_interactions.push(arc::Interaction::GAME_PREV);
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
			this->_interactions.push(arc::Interaction::GAME_NEXT);
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			this->_interactions.push(arc::Interaction::QUIT);
	}
}

arc::InteractionList arc::LibSfml::getInteractions()
{
	arc::InteractionList tmp;
	arc::InteractionList empty;

	setInteractions();
	tmp = this->_interactions;
	std::swap(this->_interactions, empty);
	return tmp;
}
