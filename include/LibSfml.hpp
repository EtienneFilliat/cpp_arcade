/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** LibSfml
*/

#ifndef LIBSFML_HPP_
	#define LIBSFML_HPP_

	#include <unordered_map>
	#include <memory>
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
		void drawSprite(const Item &);

	private:
		void setKeys();
		arc::KeysList _key;
		sf::RenderWindow _window;
		// struct spriteStruct {
		// 	sf::Sprite *sprite;
		// 	sf::Texture *texture;
		// };
		using spriteMap = std::unordered_map<
			std::string, std::unique_ptr<sf::Sprite>>;
		spriteMap _map;
};
}

#endif /* !LIBSFML_HPP_ */
