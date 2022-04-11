#pragma once

#include <fstream>

class FileManager
{
public:
	static std::string getIOFileLocation(std::string fileName);
	static bool doesFileExist(std::string fileName);
};

