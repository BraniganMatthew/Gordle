#include "WordManager.h"
//#include "words.h"
#include "RandomNumber.h"
#include <iostream>
#include <string>
#include <urlmon.h>
#include <fstream>
#include <algorithm>
#include <chrono>

#define MAX_SIZE 676

#pragma comment(lib, "urlmon.lib")

//Default Constructor for WordManager
WordManager::WordManager()
{
	isMap = false;
	validCount = 0;
	solutionCount = 0;
	initalizeMap();
}

//Boolean Constructor to switch data structure on startup
WordManager::WordManager(bool map)
{
	isMap = map;
	validCount = 0;
	solutionCount = 0;
	initalizeMap();
}

//Destructor for WordManager
WordManager::~WordManager()
{

}

//Initializes both maps for the solution List and valid list
void WordManager::initalizeMap()
{
	//Get File and start inserting valid words
	getFile(valids);
	//Repeat for solution words
	getFile(solutions);
	
}

//Determines which type to download and sends it to the insertion function
void WordManager::getFile(int fileType)
{
	std::string fileName, url;
	HashTable* wordMap;
	RedBlack* wordAlt;
	//const std::vector<std::string>* words;
	unsigned int* count;

	//Sets variables to the correct maps
	if (fileType == valids) {
		url = "https://raw.githubusercontent.com/BraniganMatthew/Gordle/master/WordLists/valid.txt";
		wordMap = &validList;
		fileName = "validWords.txt";
		count = &validCount;
		wordAlt = &validMap;
	} else {
		url = "https://raw.githubusercontent.com/BraniganMatthew/Gordle/master/WordLists/solutions.txt";
		wordMap = &solutionList;
		fileName = "solutions.txt";
		count = &solutionCount;
		wordAlt = &solutionMap;
	}
	getFileOnline(*wordMap, *wordAlt, url, fileName, *count);
	
}

//Gets nessesary file from internet and inserts correct words
void WordManager::getFileOnline(HashTable& wordMap, RedBlack& wordAlt, std::string url, std::string fileName, unsigned int& count)
{
	std::string temp;
	bool hasFailed = false;
	//Uses URLMON from Windows to download the file unto the person's computer
	URLDownloadToFile(NULL, url.c_str(), fileName.c_str(), NULL, NULL);
	std::ifstream inFile;
	inFile.open(fileName);

	//Starts timer to measure effencey
	auto startTimer = std::chrono::high_resolution_clock::now();

	//Goes through whole file
	while (inFile.peek() != EOF) {
		std::getline(inFile, temp);
		hasFailed = false;
		//Checks if word is 5 letters
		if (temp.size() != 5)
			continue;
		//Determines if it only has valid letters
		for (int j = 0; j < 5; j++) {
			if (temp.at(j) < 0 || temp.at(j) > 255 || !(std::isalpha(temp.at(j)))) {
				hasFailed = true;
				break;
			}
		}
		if (hasFailed)
			continue;
		//Edge-Case if temp doesn't equal anything
		if (temp == "")
			break;
		//Makes all letters lower-case for compatability
		std::transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
		//If isMap is true, then it will use the Red/Black Tree, otherwise it will use the HashTable
		if (isMap)
			wordAlt.insert(temp);
		else
			wordMap.insert(temp);
		count++;
	}

	//Stops the timer and displays the required time
	auto stopTimer = std::chrono::high_resolution_clock::now();
	auto timeDiff = std::chrono::duration_cast<std::chrono::microseconds>(stopTimer - startTimer);

	std::string type = (isMap) ? "Red/Black Tree" : "HashTable";
	std::cout << "Inserted " << count << " items in a " << type << " within: " << timeDiff.count() << "us\n";

	//Closes and deletes file from user's system
	inFile.close();
	std::remove(fileName.c_str());
}

//Get's a random number and uses that to find a random word either in the map or hash
std::string WordManager::getRandomWord()
{
	int temp = RandomNumber::Number(0, solutionCount);
	if (isMap)
		return solutionMap.randomWord(temp);
	else
		return solutionList.randomWord(temp);
}

//Get's a determined number and uses that to find a word either in the map or hash
std::string WordManager::getDailyWord()
{
	int temp = RandomNumber::DailyNumber(0, solutionCount);
	if (isMap)
		return solutionMap.randomWord(temp);
	else
		return solutionList.randomWord(temp);
}

//Checks to make sure the given guess is valid either in map or hash
bool WordManager::isValid(std::string word)
{
	if (word.size() != 5)
		return false;
	std::transform(word.begin(), word.end(), word.begin(), ::tolower);
	if (isMap)
		return validMap.find(word);
	else
		return validList.find(word);
}
