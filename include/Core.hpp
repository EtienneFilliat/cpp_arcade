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
		struct highScore {
			std::string gameLibName;
			std::string player;
			int score;
		};
	private:
		void initRandom() const noexcept;
		void initGraphics(const std::string &directory);
		void initGames(const std::string &directory);
		void searchDisplayLib(const std::string &fullPathName)
					noexcept;
		void searchGameLib(const std::string &fullPathName) noexcept;
		void setFirstGraphics(const std::string &fullPathName);
		void showCommands() const noexcept;
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
		void menu(bool isFirstCall);
		void loadFromMenu(bool isFirstCall) noexcept;
		void getPlayerName();
		size_t getGameNumber();
		void initHighScores(const std::string &fileName
					= "src/HighScores.txt");
		void createHighScore(const std::string &line);
		bool findInHighScores(const std::string &gameLibName) noexcept;
		void showGameHighScore(const std::string &GameLibName) const noexcept;
		DynamicLib<IGame> _gameLib;
		DynamicLib<IDisplay> _displayLib;
		std::unique_ptr<IGame> _game;
		std::unique_ptr<IDisplay> _display;
		std::vector<std::string> _displayList;
		std::vector<std::string> _gameList;
		std::vector<highScore> _highScores;
		std::string _displayName;
		std::string _gameName;
		std::string _userName;
		std::chrono::high_resolution_clock::time_point _startLoop;
		int _tryInteraction;
	};
}

#endif /* !CORE_HPP_ */
