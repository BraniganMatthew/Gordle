#pragma once
#include <string>
#include "WordManager.h"

class GameLogic
{
	private:
		std::string checkGuess(std::string guess);
		std::string target;
		WordManager wordList;
	public:

		//GameLogic();
		int runGame();
};

