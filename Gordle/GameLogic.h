#pragma once
#include <string>
#include "WordManager.h"

class GameLogic
{
	private:
		std::string checkGuess(std::string guess);
		bool checkHard(std::string guess, std::string oldGuess, std::string guessCheck);
		std::string target;
		WordManager* wordList;
	public:

		GameLogic();
		~GameLogic();
		int runGame();
};

