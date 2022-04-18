#include "WordManager.h"
//#include "words.h"
#include "RandomNumber.h"
#include <iostream>
#include <string>
#include <urlmon.h>
#include <fstream>
#include <algorithm>

#define MAX_SIZE 676

#pragma comment(lib, "urlmon.lib")

WordManager::WordManager()
{
	validCount = 0;
	solutionCount = 0;
	initalizeMap();
}

WordManager::~WordManager()
{

}

void WordManager::initalizeMap()
{
	//Get File and start inserting valid words
	getFile(valids);
	//Repeat for solution words
	getFile(solutions);
	
}

void WordManager::getFile(int fileType)
{
	std::string fileName, url;
	HashTable* wordMap;
	//const std::vector<std::string>* words;
	unsigned int* count;

	if (fileType == valids) {
		url = "https://raw.githubusercontent.com/BraniganMatthew/Gordle/master/WordLists/valid.txt";
		//words = &WORDLIST;
		wordMap = &validList;
		fileName = "validWords.txt";
		count = &validCount;
	} else {
		//words = &SOLLIST;
		url = "https://raw.githubusercontent.com/BraniganMatthew/Gordle/master/WordLists/solutions.txt";
		wordMap = &solutionList;
		fileName = "solutions.txt";
		count = &solutionCount;
	}
	getFileOnline(*wordMap, url, fileName, *count);
	
}

/*void WordManager::getFileOffline(HashTable& wordMap, const std::vector<std::string>& words)
{
	std::string temp;
	bool hasFailed = false;

	for (unsigned int i = 0; i < words.size(); i++) {
		temp = words.at(i);
		hasFailed = false;
		if (temp.size() != 5)
			continue;
		for (int j = 0; j < 5; j++) {
			if (!(std::isalpha(temp.at(j)))) {
				hasFailed = true;
				break;
			}
		}
		if (hasFailed)
			continue;
		if (temp == "")
			break;
		wordMap[temp.substr(0, 2)].insert(temp);
	}
}*/

void WordManager::getFileOnline(HashTable& wordMap, std::string url, std::string fileName, unsigned int& count)
{
	std::string temp;
	bool hasFailed = false;
	URLDownloadToFile(NULL, url.c_str(), fileName.c_str(), NULL, NULL);
	std::ifstream inFile;
	inFile.open(fileName);

	while (inFile.peek() != EOF) {
		std::getline(inFile, temp);
		hasFailed = false;
		if (temp.size() != 5)
			continue;
		for (int j = 0; j < 5; j++) {
			if (temp.at(j) < 0 || temp.at(j) > 255 || !(std::isalpha(temp.at(j)))) {
				hasFailed = true;
				break;
			}
		}
		if (hasFailed)
			continue;
		if (temp == "")
			break;
		std::transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
		wordMap.insert(temp);
		count++;
	}
	inFile.close();
	std::remove(fileName.c_str());
}

void WordManager::testFunction()
{
	std::cout << "Hello Nick!\n";
}

std::string WordManager::getRandomWord()
{
	int temp = RandomNumber::Number(0, solutionCount);
	return solutionList.randomWord(temp);
}

std::string WordManager::getDailyWord()
{
	int temp = RandomNumber::DailyNumber(0, solutionCount);
	return solutionList.randomWord(temp);
}

bool WordManager::isValid(std::string word)
{
	if (word.size() != 5)
		return false;
	std::transform(word.begin(), word.end(), word.begin(), ::tolower);
	return validList.find(word);
}
