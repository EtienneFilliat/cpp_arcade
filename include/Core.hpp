//
// EPITECH PROJECT, 2018
// arcade
// File description:
// core hpp
//

#ifndef CORE_HPP_
	#define CORE_HPP_
	#include <memory>
	#include "IGame.hpp"
	#include "IDisplay.hpp"
	#include "DynamicLib.hpp"

namespace arc {

	class Core {
	public:
		Core();
		~Core();
		int displayUsage();
		void initCore();
		void initGraphics(const std::string &directory);
		void searchDisplayLib(const std::string &fullPathName);
		void setFirstGraphics(const std::string &fullPathName);
		void launchGame();
		void gameLoop(Item &item);
		void switchToNextGraphics();
		void switchToPrevGraphics();
		bool computeKeys(arc::Item &item, KeysList &keys);
	private:
		DynamicLib<IGame> _gameLib;
		DynamicLib<IDisplay> _displayLib;
		std::unique_ptr<IGame> _game;
		std::unique_ptr<IDisplay> _display;
		std::vector<std::string> _displayList;
		std::string _displayName;
	};
}

#endif /* !CORE_HPP_ */