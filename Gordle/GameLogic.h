#pragma once
#include <string>
#include "WordManager.h"

class GameLogic
{
	private:
		std::string checkGuess(std::vector<std::string> guesses, std::string target);
		bool checkHard(std::vector<std::string> guesses, std::vector<std::string> colors, std::string hardMode);
		bool checkValid(std::vector<std::string> guesses);
		std::string target;
		WordManager* wordList;
		std::string giveTarget(bool daily);
	public:

		GameLogic();
		~GameLogic();
		//int runGame();
};

