/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** SDL2
*/

#include <memory>
#include <iostream>
#include "LibSdl2.hpp"
#include "Exception.hpp"

extern "C" std::unique_ptr<arc::IDisplay> create_object()
{
	std::unique_ptr<arc::IDisplay> ptr(new arc::LibSdl2);
	return std::move(ptr);
}

arc::LibSdl2::LibSdl2()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	_window = SDL_CreateWindow("CPP_ARCADE SLD2", SDL_WINDOWPOS_CENTERED,
					SDL_WINDOWPOS_CENTERED,1180, 1000, SDL_WINDOW_SHOWN);
	_renderer = SDL_CreateRenderer(_window, -1, 0);
	_font = TTF_OpenFont("lib/sdl2/FiraMono-Medium.ttf", 24);
	_fontcolor = {255, 255, 255, 0};
	_step = 1;
}

arc::LibSdl2::~LibSdl2()
{
	SDL_DestroyRenderer(_renderer);
	SDL_DestroyWindow(_window);
	SDL_Quit();
}

void arc::LibSdl2::clear()
{
	SDL_RenderClear(_renderer);
	return;
}

void arc::LibSdl2::refresh()
{
	SDL_RenderPresent(_renderer);
	return;
}

void arc::LibSdl2::putStr(const std::string &text, int x, int y)
{
	int text_width;
	int text_height;
	SDL_Surface *surface;
	SDL_Texture *texture;
	SDL_Rect rect;

	surface = TTF_RenderText_Solid(_font, text.c_str(), _fontcolor);
	texture = SDL_CreateTextureFromSurface(_renderer, surface);
	text_width = surface->w;
	text_height = surface->h;
	SDL_FreeSurface(surface);
	rect.x = x * 32;
	rect.y = y * 32;
	rect.w = text_width;
	rect.h = text_height;
	SDL_RenderCopy(_renderer, texture, NULL, &rect);
	SDL_DestroyTexture(texture);
	return;
}

void arc::LibSdl2::putItem(const arc::Item &item)
{
	// auto search = _map.find(item.name);
	// auto sp = std::unique_ptr<spriteStruct>(new spriteStruct);
	// auto texture = std::make_unique<SDL_Texture>();
	// auto rect = std::unique_ptr<SDL_Rect>(new SDL_Rect);
	SDL_Texture *texture;
	SDL_Rect rect;
	int w;
	int h;

	// if (search == _map.end()) {
		// texture.reset(IMG_LoadTexture(_renderer,
				// item.sprites[item.currSpriteIdx].path.c_str()));
		texture = IMG_LoadTexture(_renderer,
				item.sprites[item.currSpriteIdx].path.c_str());
		SDL_QueryTexture(texture, NULL, NULL, &w, &h);
		rect.x = item.x * 32;
		rect.y = item.y * 32;
		rect.w = w;
		rect.h = h;
		// sp->texture = std::move(texture);
		// sp->rect = std::move(rect);
		// _map.emplace(item.name, std::move(sp));
		SDL_RenderCopy(_renderer, texture, NULL, &rect);
		SDL_DestroyTexture(texture);
	// } else {
		// SDL_RenderCopy(_renderer, search->second->texture.get(), NULL,
				// search->second->rect.get());
	// }
	return;
}

void arc::LibSdl2::putItem(const arc::Item &item, int x, int y)
{
	(void) item;
	(void) x;
	(void) y;
	return;
}

void arc::LibSdl2::putItem(const arc::Item &item,
			const std::vector<struct Position> &pos)
{
	(void) item;
	(void) pos;
	return;
}

void arc::LibSdl2::setStep(uint step)
{
	_step = step;
	return;
}

void arc::LibSdl2::setInteractions()
{
	SDL_Event ev;

	if (SDL_PollEvent(&ev)) {
		if (ev.type == SDL_KEYDOWN){
			if (ev.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
				_inter.push(arc::Interaction::QUIT);
			if (ev.key.keysym.scancode == SDL_SCANCODE_TAB)
				_inter.push(arc::Interaction::MENU);
		}
	}
}

arc::InteractionList arc::LibSdl2::getInteractions()
{
	arc::InteractionList tmp;
	arc::InteractionList empty;

	setInteractions();
	tmp = _inter;
	std::swap(this->_inter, empty);
	return tmp;
}
