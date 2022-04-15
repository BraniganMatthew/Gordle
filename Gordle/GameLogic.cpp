#include "GameLogic.h"
#include "WordManager.h"
#include <iostream>

int GameLogic::runGame()
{
	target = wordList.getRandomWord();
	//Do things
	int guesses = 0;
	std::string guess = "00000";
	while (guesses < 6 && guess != target) {
		bool valid = false;
		while (!valid) {
			//get user guess
			//search wordlist
			std::cout << "Enter guess: ";
			std::cin >> guess;
			valid = wordList.isValid(guess);
		}
		guesses++;
		std::cout << checkGuess(guess) << std::endl;
	}
	std::cout << target << std::endl;
	return guesses;
}

std::string GameLogic::checkGuess(std::string guess)
{
	std::unordered_map<char, std::pair<std::unordered_set<int>, int>> targetWord;
	std::string checked = "00000";
	for (int i = 0; i < 5; i++) {
		targetWord[target.at(i)].first.insert(i);
		targetWord[target.at(i)].second++;
	}

	for (int i = 0; i < 5; i++) {
		if (targetWord[guess.at(i)].second > 0) {
			if (targetWord[guess.at(i)].first.find(i) != targetWord[guess.at(i)].first.end()) {
				checked[i] = 'G';
				targetWord[guess.at(i)].second--;
			}
		}
	}

	for (int i = 0; i < 5; i++) {
		if (checked[i] == 'G')
			continue;
		if (targetWord[guess.at(i)].second > 0) {
			checked[i] = 'Y';
			targetWord[guess.at(i)].second--;
		}
		else {
			checked[i] = 'E';
		}
	}

	/*for (int i = 0; i < 5; i++) {
		std::cout << checked[i] << std::endl;
	}*/
	return checked;
}