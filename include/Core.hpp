//
// EPITECH PROJECT, 2018
// arcade
// File description:
// core hpp
//

#ifndef CORE_HPP_
	#define CORE_HPP_
	#include <memory>
	#include <chrono>
	#include "IGame.hpp"
	#include "IDisplay.hpp"
	#include "DynamicLib.hpp"

namespace arc {

	class Core {
	public:
		Core();
		~Core();
		int displayUsage() const noexcept;
		void initCore(const std::string &firstGraphics,
				const std::string &displayDir = "lib",
				const std::string &gameDir = "games");
		void gameLoop();
	private:
		void initRandom() const noexcept;
		void initGraphics(const std::string &directory);
		void initGames(const std::string &directory);
		void searchDisplayLib(const std::string &fullPathName)
					noexcept;
		void searchGameLib(const std::string &fullPathName) noexcept;
		void setFirstGraphics(const std::string &fullPathName);
		void setFirstGame();
		void showGraphicsAvailable() const noexcept;
		void showGamesAvailable() const noexcept;
		void switchToNextGraphics();
		void switchToPrevGraphics();
		bool computeKeys(InteractionList &);
		void tryToProcessInteraction(arc::InteractionList &keys)
						noexcept;
		void switchToNextGame();
		void switchToPrevGame();
		void displayText();
		void waitCycle() const noexcept;
		void menu();
		void getPlayerName();
		size_t getGameNumber();
		DynamicLib<IGame> _gameLib;
		DynamicLib<IDisplay> _displayLib;
		std::unique_ptr<IGame> _game;
		std::unique_ptr<IDisplay> _display;
		std::vector<std::string> _displayList;
		std::vector<std::string> _gameList;
		std::string _displayName;
		std::string _gameName;
		std::string _userName;
		std::chrono::high_resolution_clock::time_point _startLoop;
		int _tryInteraction;
	};
}

#endif /* !CORE_HPP_ */
