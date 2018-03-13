/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** LibSfml
*/

#ifndef LIBSFML_HPP_
	#define LIBSFML_HPP_

	#include <SFML/Graphics.hpp>
	#include "IDisplay.hpp"

namespace arc {

class LibSfml : public IDisplay {
	public:
		LibSfml();
		~LibSfml();
		arc::KeysList getKeys();
		void refresh();
		void clear();

	private:
		void setKeys();
		arc::KeysList _key;
		sf::RenderWindow _window;
		sf::CircleShape _shape;
};
}

#endif /* !LIBSFML_HPP_ */
