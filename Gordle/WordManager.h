#pragma once
#include <unordered_map>
class WordManager
{
private:
	std::unordered_map<std::string, std::string> validList, solutionList;
	void getFileOnline();
	void getFileOffline();
	void initalizeMap();
public:
	WordManager();
	~WordManager();
	void testFunction();
	std::string getDailyWord();
	std::string getRandomWord();
};

