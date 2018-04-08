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
					SDL_WINDOWPOS_CENTERED, 1180, 1000,
					SDL_WINDOW_SHOWN);
	if (!_window)
		throw arc::Exception(SDL_GetError(), "LibSDL2");
	_renderer = SDL_CreateRenderer(_window, -1, 0);
	if (!_renderer)
		throw arc::Exception(SDL_GetError(), "LibSDL2");
	_font = TTF_OpenFont("lib/sdl2/FiraMono-Medium.ttf", 24);
	if (!_font)
		throw arc::Exception(SDL_GetError(), "LibSDL2");
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
	millisec wait(10);

	SDL_RenderPresent(_renderer);
	std::this_thread::sleep_for(wait);
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
	if (!surface)
		throw arc::Exception(SDL_GetError(), "LibSDL2");
	texture = SDL_CreateTextureFromSurface(_renderer, surface);
	if (!texture)
		throw arc::Exception(SDL_GetError(), "LibSDL2");
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

int arc::LibSdl2::setAngle(int angle)
{
	switch (angle) {
		case 90:
			return 270;
		case 180:
			return 0;
		case -90:
			return 90;
		default:
			return 180;
	}
}

void arc::LibSdl2::putItem(const arc::Item &item)
{
	auto search = _map.find(item.name);
	auto sp = std::unique_ptr<spriteStruct>(new spriteStruct);
	SDL_Texture *texture;
	SDL_Rect rect;
	int angle = 0;
	int w;
	int h;

	rect.x = item.x * 32;
	rect.y = item.y * 32;
	rect.w = 32;
	rect.h = 32;
	if (item.name == "pacman")
		angle = setAngle(item.sprites[item.currSpriteIdx].rotation);
	if (search == _map.end()) {
		texture = IMG_LoadTexture(_renderer,
				item.sprites[item.currSpriteIdx].path.c_str());
		if (!texture)
			throw arc::Exception(SDL_GetError(), "LibSDL2");
		SDL_QueryTexture(texture, NULL, NULL, &w, &h);
		sp->texture = std::make_unique<SDL_Texture *>(texture);
		sp->rect = std::make_unique<SDL_Rect>(rect);
		sp->lastindex = item.currSpriteIdx;
		SDL_RenderCopyEx(_renderer, texture, NULL, &rect, angle, NULL,
					SDL_FLIP_HORIZONTAL);
		_map.emplace(item.name, std::move(sp));
		return;
	} else if (item.currSpriteIdx != search->second->lastindex) {
		SDL_DestroyTexture(*search->second->texture);
		texture = IMG_LoadTexture(_renderer,
			item.sprites[item.currSpriteIdx].path.c_str());
		if (!texture)
			throw arc::Exception(SDL_GetError(), "LibSDL2");
		search->second->texture =
			std::make_unique<SDL_Texture *>(texture);
		search->second->lastindex = item.currSpriteIdx;
	}
	SDL_RenderCopyEx(_renderer, *search->second->texture, NULL, &rect,
				angle, NULL, SDL_FLIP_HORIZONTAL);
	return;
}

void arc::LibSdl2::putItem(const arc::Item &item, int x, int y)
{
	auto search = _map.find(item.name);
	auto sp = std::unique_ptr<spriteStruct>(new spriteStruct);
	SDL_Texture *texture;
	SDL_Rect rect;
	int angle = 0;
	int w;
	int h;

	rect.x = x * 32;
	rect.y = y * 32;
	rect.w = 32;
	rect.h = 32;
	if (item.name == "pacman")
		angle = setAngle(item.sprites[item.currSpriteIdx].rotation);
	if (search == _map.end()) {
		texture = IMG_LoadTexture(_renderer,
				item.sprites[item.currSpriteIdx].path.c_str());
		if (!texture)
			throw arc::Exception(SDL_GetError(), "LibSDL2");
		SDL_QueryTexture(texture, NULL, NULL, &w, &h);
		sp->texture = std::make_unique<SDL_Texture *>(texture);
		sp->rect = std::make_unique<SDL_Rect>(rect);
		sp->lastindex = item.currSpriteIdx;
		SDL_RenderCopyEx(_renderer, texture, NULL, &rect, angle, NULL,
					SDL_FLIP_HORIZONTAL);
		_map.emplace(item.name, std::move(sp));
		return;
	} else if (item.currSpriteIdx != search->second->lastindex) {
		SDL_DestroyTexture(*search->second->texture);
		texture = IMG_LoadTexture(_renderer,
			item.sprites[item.currSpriteIdx].path.c_str());
		if (!texture)
			throw arc::Exception(SDL_GetError(), "LibSDL2");
		search->second->texture =
			std::make_unique<SDL_Texture *>(texture);
	}
	SDL_RenderCopyEx(_renderer, *search->second->texture, NULL, &rect,
				angle, NULL, SDL_FLIP_HORIZONTAL);
	return;
}

void arc::LibSdl2::putItem(const arc::Item &item,
			const std::vector<struct Position> &pos)
{
	auto it = pos.begin();

	while (it != pos.end()) {
		this->putItem(item,
			(*it).x / this->_step,
			(*it).y / this->_step);
		std::next(it);
	}
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
			if (ev.key.keysym.scancode == SDL_SCANCODE_W)
				_inter.push(arc::Interaction::MOVE_UP);
			if (ev.key.keysym.scancode == SDL_SCANCODE_S)
				_inter.push(arc::Interaction::MOVE_DOWN);
			if (ev.key.keysym.scancode == SDL_SCANCODE_A)
				_inter.push(arc::Interaction::MOVE_LEFT);
			if (ev.key.keysym.scancode == SDL_SCANCODE_D)
				_inter.push(arc::Interaction::MOVE_RIGHT);
			if (ev.key.keysym.scancode == SDL_SCANCODE_O)
				_inter.push(arc::Interaction::LIB_PREV);
			if (ev.key.keysym.scancode == SDL_SCANCODE_P)
				_inter.push(arc::Interaction::LIB_NEXT);
			if (ev.key.keysym.scancode == SDL_SCANCODE_L)
				_inter.push(arc::Interaction::GAME_PREV);
			if (ev.key.keysym.scancode == SDL_SCANCODE_M)
				_inter.push(arc::Interaction::GAME_NEXT);
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
