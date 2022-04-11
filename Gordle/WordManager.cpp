#include "WordManager.h"
#include "FileManager.h"
#include <iostream>
#include <fstream>
#include <urlmon.h>

WordManager::WordManager()
{
	initalizeMap();
}

WordManager::~WordManager()
{
	
}

void WordManager::initalizeMap()
{
	//Get File and start inserting valid words
	getFile(valids);
	getFile(solutions);
	//Repeat for easy words
}

void WordManager::getFile(int fileType)
{
	std::string fileName, url;
	struct stat buf;
	if (fileType == valids) {
		fileName = "ValWords.wrdstg";
		url = "https://raw.githubusercontent.com/meetDeveloper/freeDictionaryAPI/master/meta/wordList/english.txt";
	} else {
		fileName = "SolWords.wrdstg";
		url = "TBA";
	}
	fileName = FileManager::getIOFileLocation(fileName);
	//If File in appData exists
	if (FileManager::doesFileExist(fileName)) {
		getFileOffline(fileName);
	} else { //Else download full list from github
		getFileOnline(url, fileName);
	}
	
	
}

void WordManager::getFileOnline(std::string url, std::string fileName)
{

}

void WordManager::getFileOffline(std::string url)
{

}

void WordManager::testFunction()
{
	std::cout << "Hello Nick!\n";
}