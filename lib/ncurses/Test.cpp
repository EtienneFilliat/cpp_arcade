/*
** EPITECH PROJECT, 2018
** NAME_OF_PROJECT
** File description:
** This is a description kek
*/

#include <iostream>
#include <unistd.h>
#include "LibNcurses.hpp"
#include "Exception.hpp"

int main()
{
	arc::KeysList keys;
	arc::Item sprite;

	sprite.name = "kek";
	sprite.spriteChar = 'e';
	sprite.x = 0;
	sprite.y = 0;
	try {
		LibNcurses cc;
		while (true) {
			cc.clear();
			keys = cc.getKeys();
			if (!keys.empty()) {
				if (keys.front() == arc::Keys::QUIT)
					break;
				else if (keys.front() == arc::Keys::MOVE_UP)
					sprite.y -= 1;
				else if (keys.front() == arc::Keys::MOVE_DOWN)
					sprite.y += 1;
				else if (keys.front() == arc::Keys::MOVE_LEFT)
					sprite.x -= 1;
				else if (keys.front() == arc::Keys::MOVE_RIGHT)
					sprite.x += 1;
				keys.pop();
			}
			cc.drawSprite(sprite);
			cc.refresh();
			usleep(15000);
		}
	}
	catch (const arc::Exception &e) {
		std::cout << e.what() << std::endl;
	}

	std::cout << "end" << std::endl;
	return (0);
}
