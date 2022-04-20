#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>

class GUIBase {
	//Can only be accessed through static functions
	//static std::unordered_map<std::string, sf::Texture> textures;
	//static void LoadTexture(std::string textureName);

public:
	//void LoadAllTextures();
	//static sf::Texture& GetTexture(std::string textureName);
	std::string LoadHomeBoard(sf::RenderWindow& window, bool& daily);
	void LoadGameBoard(sf::RenderWindow& window);
	void UpdateBoard(sf::RenderWindow& window, std::vector<std::string> prevGuesses, std::vector<std::string> prevColors, std::string mode, bool validGuess, bool validHardGuess);
	bool KeyboardInput(sf::RenderWindow& window, std::string& guess);
	//static void Clear(); //Called at end of main()
};


