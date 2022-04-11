#include "WordManager.h"

#include <iostream>
#include <fstream>

WordManager::WordManager()
{
	initalizeMap();
}

WordManager::~WordManager()
{
	
}

void WordManager::initalizeMap()
{
	//If File in appData exists
	getFileOffline();
	//Else download full list from github
	getFileOnline();
	//Get File and start inserting valid words
	
	//Repeat for easy words
}

void WordManager::getFileOnline()
{

}

void WordManager::getFileOffline()
{

}

void WordManager::testFunction()
{
	std::cout << "Hello Nick!\n";
}