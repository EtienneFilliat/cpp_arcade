/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** IGame
*/

#ifndef IGAME_HPP_
	#define IGAME_HPP_

class IGame {
	public:
		virtual ~IGame() = default;
		virtual void displaySomeShit() = 0;
	protected:
	private:
};

#endif /* !IGAME_HPP_ */
