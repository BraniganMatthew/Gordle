#pragma once
#include <unordered_map>
class WordManager
{
private:
	enum fileType {valids,solutions};
	std::unordered_map<std::string, std::string> validList, solutionList;
	void getFileOnline(std::string url, std::string fileName);
	void getFileOffline(std::string fileName);
	void getFile(int fileType);
	void initalizeMap();

public:
	WordManager();
	~WordManager();
	void testFunction();
	std::string getDailyWord();
	std::string getRandomWord();
};

