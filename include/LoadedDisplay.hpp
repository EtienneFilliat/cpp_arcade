//
// EPITECH PROJECT, 2018
// arcade
// File description:
// display lib manager hpp
//

#ifndef LOADEDDISPLAY_HPP_
	#define LOADEDDISPLAY_HPP_
	#include <memory>
	#include "IDisplay.hpp"

namespace arc {

	class LoadedDisplay {
	public:
		LoadedDisplay(IDisplay *displayObject);
		~LoadedDisplay();
	private:
		std::unique_ptr<IDisplay> _object;
	};
}

#endif /* !LOADEDDISPLAY_HPP_ */
