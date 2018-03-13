/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** IDisplay
*/

#ifndef IDISPLAY_HPP_
	#define IDISPLAY_HPP_

	#include <queue>

namespace arc {

	class IDisplay {
	public:
		enum Keys {
			MOVE_UP,
			MOVE_DOWN,
			MOVE_LEFT,
			MOVE_RIGHT,
			NEXT_LIB,
			PREV_LIB,
			NEXT_GAME,
			PREV_GAME,
			QUIT,
		};
		using KeysList = std::queue<Keys>;

		virtual ~IDisplay() = default;
		virtual KeysList getKeys() = 0;
		virtual void refresh() = 0;
		virtual void clear() = 0;
	};
}

#endif /* !IDISPLAY_HPP_ */
