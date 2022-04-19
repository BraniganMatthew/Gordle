#pragma once
#include <unordered_map>
#include <unordered_set>
#include "HashTable.h"
#include "RedBlack.h"


class WordManager
{
private:
	enum fileType {valids,solutions};
	HashTable validList, solutionList;
	RedBlack validMap, solutionMap;
	bool isMap;
	unsigned int validCount, solutionCount;
	void getFileOnline(HashTable& wordMap, RedBlack& wordAlt, std::string url, std::string fileName, unsigned int& count);
	void getFile(int fileType);
	void initalizeMap();


public:
	WordManager();
	WordManager(bool map);
	~WordManager();
	std::string getDailyWord();
	std::string getRandomWord();
	bool isValid(std::string word);
};

