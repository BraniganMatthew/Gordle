#pragma once
#include <string>
#include "WordManager.h"

class GameLogic
{
	private:
		std::string target;
		WordManager* wordList;
	public:

		GameLogic();
		~GameLogic();
		//int runGame();
		std::string checkGuess(std::vector<std::string> guesses, std::string target);
		bool checkHard(std::vector<std::string> guesses, std::vector<std::string> colors, std::string hardMode);
		bool checkValid(std::vector<std::string> guesses);
		std::string giveTarget(bool daily);
};

