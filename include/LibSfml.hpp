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
	class LibSfml;
}

class arc::LibSfml : public arc::IDisplay {
	public:
		LibSfml();
		~LibSfml() final;
		void clear() final;
		void refresh() final;
		void putStr(const std::string &, int x, int y) final;
 		void putItem(const arc::Item &) final;
		void putItem(const arc::Item &, int, int) final;
		void putItem(const arc::Item &,
			const std::vector<struct Position> &) final;
		void setStep(uint) final;
		arc::InteractionList getInteractions() final;

	private:
		struct spriteStruct {
			std::unique_ptr<sf::Sprite> sprite;
			std::unique_ptr<sf::Texture> texture;
		};
		using spriteMap = std::unordered_map<
			std::string, std::unique_ptr<spriteStruct>>;
		void setInteractions();
		arc::InteractionList _interactions;
		std::unique_ptr<sf::RenderWindow> _window;
		spriteMap _map;
		uint _step;
		sf::Font _font;
		sf::Text _text;
};

#endif /* !LIBSFML_HPP_ */
