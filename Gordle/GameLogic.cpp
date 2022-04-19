#include "GameLogic.h"
#include "WordManager.h"
#include <iostream>

GameLogic::GameLogic()
{
	bool whichStruc = true;
	wordList = new WordManager(whichStruc);
}

GameLogic::~GameLogic()
{
	delete wordList;
}

int GameLogic::runGame()
{
	bool hMode = false;
	std::cout << "H for hard mode or N for normal:";
	std::string mode;
	std::cin >> mode;
	if (mode == "H") {
		hMode = true;
	}
	std::cout << "D for daily word or R for random word:";
	std::string daily;
	std::cin >> daily;
	if (daily != "D") {
		target = wordList->getRandomWord();
	}
	else {
		//get daily
		target = wordList->getDailyWord();
	}
	//Do things
	int guesses = 0;
	std::string guess = "00000";
	std::string guessCheck = "00000";
	std::string oldGuess = guess;
	std::vector<std::string> guessesMade;
	std::vector<std::string> colorsMade;
	while (guesses < 7 && guess != target) {
		bool valid = false;
		while (!valid) {
			std::cout << "Enter guess: ";
			std::cin >> guess;
			valid = wordList->isValid(guess);
			if (valid&&guesses>0&&hMode) {
				//std::cout << "guessCheck " << guessCheck << std::endl;
				valid = checkHard(guess, oldGuess, guessCheck);
				if (!valid) {
					std::cout << "hard fail " << std::endl;
				}
			}
		}
		guessesMade.push_back(guess);
		colorsMade.push_back(guessCheck);
		std::cout << guesses << std::endl;
		guesses++;
		guessCheck = checkGuess(guess);
		std::cout << guessCheck << std::endl;
		oldGuess = guess;
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

bool GameLogic::checkHard(std::string guess, std::string oldGuess, std::string guessCheck)
{
	bool valid = true;
	std::string toCheck = "";
	for (int i = 0; i < 5; i++) {
		if (guessCheck[i] == 'G') {
			if (guess[i] != oldGuess[i]) {
				valid = false;
				break;
			}
			toCheck += oldGuess[i];
		}
		else if (guessCheck[i] == 'Y') {
			toCheck += oldGuess[i];
		}
	}
	//std::cout << toCheck << std::endl;
	for (int i = 0; i < toCheck.length(); i++) {
		int clues = 0;
		int found = 0;
		for (int j = 0; j < toCheck.length(); j++) {
			if (toCheck[i] == toCheck[j]) {
				clues++;
			}
		}
		for (int k = 0; k < 5; k++) {
			if (toCheck[i] == guess[k]) {
				found++;
			}
		}
		//std::cout << toCheck[i] << clues << found << std::endl;
		if (clues > found) {
			valid = false;
			break;
		}
	}

	if (valid) {
		//std::cout << "valid" << std::endl;
	}
	return valid;
}