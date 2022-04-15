#include "WordManager.h"
//#include "words.h"
#include "RandomNumber.h"
#include <iostream>
#include <string>
#include <urlmon.h>
#include <fstream>
#include <algorithm>

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
	std::unordered_map<std::string, std::unordered_set<std::string>>* wordMap;
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

void WordManager::getFileOffline(std::unordered_map<std::string, std::unordered_set<std::string>>& wordMap, const std::vector<std::string>& words)
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
}

void WordManager::getFileOnline(std::unordered_map<std::string, std::unordered_set<std::string>>& wordMap, std::string url, std::string fileName, unsigned int& count)
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
		wordMap[temp.substr(0, 2)].insert(temp);
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
	int temp = RandomNumber::Number(0, (int) solutionList.size()), count = 0;
	std::unordered_set<std::string> buff;
	for (auto it : solutionList) {
		buff = it.second;
		if (count >= temp)
			break;
		count++;
	}
	temp = RandomNumber::Number(0, (int) buff.size()-1);
	count = 0;
	for (auto it : buff) {
		if (count >= temp)
			return it;
		count++;
	}
	return "Wrong";
}

bool WordManager::isValid(std::string word)
{
	std::transform(word.begin(), word.end(), word.begin(), ::tolower);
	std::unordered_set<std::string> buff = validList[word.substr(0,2)];
	if (buff.find(word) != buff.end()) {
		return true;
	} else {
		return false;
	}
}
