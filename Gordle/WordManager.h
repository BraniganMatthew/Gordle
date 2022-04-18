#pragma once
#include <unordered_map>
#include <unordered_set>
#include "HashTable.h"

//typedef std::unordered_set<std::string>* HashTable;

class WordManager
{
private:
	enum fileType {valids,solutions};
	HashTable validList, solutionList;
	//std::unordered_map<std::string, std::unordered_set<std::string>> validList, solutionList;
	unsigned int validCount, solutionCount;
	void getFileOffline(HashTable& wordMap, const std::vector<std::string>& words);
	void getFileOnline(HashTable& wordMap, std::string url, std::string fileName, unsigned int& count);
	void getFile(int fileType);
	void initalizeMap();


public:
	WordManager();
	~WordManager();
	void testFunction();
	std::string getDailyWord();
	std::string getRandomWord();
	bool isValid(std::string word);
};

