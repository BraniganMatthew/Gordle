#pragma once
#include <unordered_map>
#include <unordered_set>


class WordManager
{
private:
	enum fileType {valids,solutions};
	std::unordered_map<std::string, std::unordered_set<std::string>> validList, solutionList;
	unsigned int validCount, solutionCount;
	void getFileOffline(std::unordered_map<std::string, std::unordered_set<std::string>>& wordMap, const std::vector<std::string>& words);
	void getFileOnline(std::unordered_map<std::string, std::unordered_set<std::string>>& wordMap, std::string url, std::string fileName, unsigned int& count);
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

