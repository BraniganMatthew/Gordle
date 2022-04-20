#include "GameLogic.h"
#include "WordManager.h"
#include <iostream>
#include <algorithm>

//gameLogic constructor that gets wordlist from either data structure
//whichStruc == true uses Red-Black tree
//whichStruc == false uses hash table
GameLogic::GameLogic()
{
	bool whichStruc = false;
	wordList = new WordManager(whichStruc);
	WordManager* temp = new WordManager(true);
	delete temp;
}

//wordlist destructor
GameLogic::~GameLogic()
{
	delete wordList;
}

//retrieves target random word from list if !daily
//retrieves daily word if daily
std::string GameLogic::giveTarget(bool daily) {
	if (daily) {
		return wordList->getDailyWord();
	}
	else {
		return wordList->getRandomWord();
	}
}

//checks guess and returns colors
std::string GameLogic::checkGuess(std::vector<std::string> guesses, std::string target)
{
	std::string guess = guesses[guesses.size() - 1];
	//creates a map for the target word
	std::unordered_map<char, std::pair<std::unordered_set<int>, int>> targetWord;
	std::transform(target.begin(), target.end(), target.begin(), ::toupper);
	std::string checked = "00000";
	//inserts the target word into the map
	for (int i = 0; i < 5; i++) {
		targetWord[target.at(i)].first.insert(i);
		targetWord[target.at(i)].second++;
	}

	//checks if a letter is in the correct position
	for (int i = 0; i < 5; i++) {
		if (targetWord[guess.at(i)].second > 0) {
			if (targetWord[guess.at(i)].first.find(i) != targetWord[guess.at(i)].first.end()) {
				checked[i] = 'G';
				targetWord[guess.at(i)].second--;
			}
		}
	}

	//checks if a letter is in the word but in the wrong position
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

	//returns a string with the colors of each letter
	return checked;
}

//checks the word list to see if the guess is valid
bool GameLogic::checkValid(std::vector<std::string> guesses) {
	std::string guess = guesses[guesses.size() - 1];
	bool valid = wordList->isValid(guess);
	return valid;
}

//hardmode
//checks the new guess to see if it uses the clues from the previous guess
bool GameLogic::checkHard(std::vector<std::string> guesses, std::vector<std::string> colors, std::string hardMode)
{
	std::string guess = "";
	std::string guessCheck = "";
	//getting comparison from vectors
	if (guesses.size() > 0) {
		guess = guesses[guesses.size() - 1];
	}
	std::string oldGuess = "";
	if (colors.size() > 0) {
		guessCheck = colors[colors.size() - 1];
	}

	//checks if hardmode is on and if there is a previous guess to try
	if (guesses.size() > 1 && hardMode == "hard" && colors.size()>0) {
		oldGuess = guesses[guesses.size() - 2];
	}
	else {
		return true;
	}
	bool valid = true;
	std::string toCheck = "";

	//checks if green letters are still in the same place
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

	//checks if yellow letters are still in the word by using the amounts of yellows and count in new guess
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
		if (clues > found) {
			valid = false;
			break;
		}
	}

	return valid;
}