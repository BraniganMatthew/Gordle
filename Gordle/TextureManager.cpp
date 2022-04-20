#include "TextureManager.h"
#include <urlmon.h>
#pragma comment(lib, "urlmon.lib")


std::unordered_map<std::string, sf::Texture> TextureManager::textures;

void TextureManager::LoadTexture(std::string fileName)
{
	std::string path = "";
	path += fileName + ".png";
	std::string url = "https://raw.githubusercontent.com/BraniganMatthew/Gordle/master/images/" + path;
	URLDownloadToFile(NULL, url.c_str(), path.c_str(), NULL, NULL);
	textures[fileName].loadFromFile(path);
	std::remove(path.c_str());
}

void  TextureManager::Clear()
{
	textures.clear();
	std::remove("arial.ttf");
}

sf::Texture& TextureManager::GetTexture(std::string textureName)
{
	//Check if the texture exists
	if (textures.find(textureName) == textures.end())
	{
		LoadTexture(textureName);
	}

	return textures[textureName];
}

void TextureManager::downloadFont()
{
	std::string path = "arial.ttf";
	std::string url = "https://raw.githubusercontent.com/BraniganMatthew/Gordle/master/images/" + path;
	URLDownloadToFile(NULL, url.c_str(), path.c_str(), NULL, NULL);
}