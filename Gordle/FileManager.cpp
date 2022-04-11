#include "FileManager.h"
#include <stdlib.h>
#include <sys/stat.h>

std::string FileManager::getIOFileLocation(std::string fileName)
{
	std::string fileLocation;
	fileLocation.append(std::getenv("appdata"));
	fileLocation.append("\\JustMattNick\\Gordle\\");
	fileLocation.append(fileName);
	return fileLocation;
}

bool FileManager::doesFileExist(std::string fileName)
{

	return false;
}