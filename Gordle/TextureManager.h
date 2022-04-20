#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>

class TextureManager
{
	//Can only be accessed through static functions
	static std::unordered_map<std::string, sf::Texture> textures;
	static void LoadTexture(std::string textureName);


public:
	static sf::Texture& GetTexture(std::string textureName);
	static void Clear(); //Called at end of main()
	static void downloadFont();
};

