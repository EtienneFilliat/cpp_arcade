/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** LibSdl2
*/

#ifndef LIBSDL2_HPP_
	#define LIBSDL2_HPP_
	#include <SDL2/SDL.h>
	#include <SDL2/SDL_ttf.h>
	#include <SDL2/SDL_image.h>
	#include <unordered_map>
	#include "IDisplay.hpp"

namespace arc {

class LibSdl2 : public arc::IDisplay {
	public:
		LibSdl2();
		~LibSdl2() final;
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
		void setInteractions();
		TTF_Font* _font;
		SDL_Color _fontcolor;
		SDL_Window *_window;
		SDL_Renderer *_renderer;
		InteractionList _inter;
		uint _step;
		// struct spriteStruct {
		// 	// SDL_Texture *sprite;
		// 	std::unique_ptr<SDL_Texture> texture;
		// 	std::unique_ptr<SDL_Rect> rect;
		// };
		// using spriteMap = std::unordered_map<
		// 	std::string, std::unique_ptr<spriteStruct>>;
		// spriteMap _map;
};
}

#endif /* !LIBSDL2_HPP_ */
