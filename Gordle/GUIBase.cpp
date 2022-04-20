#include <iostream>
#include <vector>
//#include <urlmon.h>
#include "GUIBase.h"
#include "GameLogic.h"
#include "TextureManager.h"



//Redeclare the variable so this file can use it
//std::unordered_map<std::string, sf::Texture> GUIBase::textures;

/* FOR THE ROWS, MAKE ROWS IN PPT AND USE AS BUTTONS. SAME THING WITH GREEN/YELLOW/GRAY BACKGROUNDS. AND MAYBE LETTERS? */

/*void GUIBase::LoadAllTextures()
{
	TextureManager::LoadTexture("easy");
	LoadTexture("hard");
	LoadTexture("wordleGray");
	LoadTexture("wordleYellow");
	LoadTexture("wordleGreen");
}*/

/*void GUIBase::LoadTexture(std::string fileName)
{
	std::string path = "images/";
	path += fileName + ".png";
	textures[fileName].loadFromFile(path);
}*/

std::string GUIBase::LoadHomeBoard(sf::RenderWindow& window, bool &daily)
{
	sf::Font font;
	sf::Text text;
	sf::RectangleShape rect(sf::Vector2f(75, 75));
	rect.setFillColor(sf::Color(0, 33, 165)); // Gator Blue
	rect.setOutlineThickness(2);
	rect.setOutlineColor(sf::Color(250, 70, 22)); // Gator Orange

	// Title vector, and a vector to store positions
	std::vector<char> title = { 'G','O', 'R', 'D', 'L', 'E' };
	std::vector<std::pair<int, int>> pos;

	// Load 'easy', 'hard', and 'daily' mode buttons and create Sprites for each
	/*LoadTexture("easy");
	LoadTexture("hard");*/
	sf::Sprite easyBtn(TextureManager::GetTexture("easy"));
	sf::Sprite hardBtn(TextureManager::GetTexture("hard"));
	sf::Sprite dailyBtn(TextureManager::GetTexture("daily"));
	easyBtn.setScale(0.5, 0.5);
	hardBtn.setScale(0.5, 0.5);
	//dailyBtn.setScale(0.5, 0.5);

	int x = 45;
	for (int i = 0; i < title.size(); i++)
	{
		std::pair<int, int> temp;
		temp = std::make_pair(x, 125);
		pos.push_back(temp);
		x += rect.getSize().x + 10;
	}

	if (!font.loadFromFile("arial.ttf"))
	{
		std::cout << "File not loaded.";
	}

	/* Initialize the GORDLE Board */

	window.clear(sf::Color(255, 255, 255)); // White

	for (int i = 0; i < title.size(); i++)
	{
		// Rectangles
		rect.setPosition(pos[i].first, pos[i].second);
		window.draw(rect);

		// Select font
		text.setFont(font);

		// Set string to print
		text.setString(title[i]);

		// Set the character size
		text.setCharacterSize(48);

		// Set color
		text.setFillColor(sf::Color(250, 70, 22)); // Gator Orange

		// Set text style
		text.setStyle(sf::Text::Bold);

		// Set position
		text.setPosition(pos[i].first + (rect.getSize().x / 4), pos[i].second + (rect.getSize().y / 8));

		window.draw(text);
	}

	// Type the catchphrase "A UF-Styled Wordle Game"
	std::string subtitle = "A UF-STYLED WORDLE GAME";

	// Set string to print
	text.setString(subtitle);

	// Set the character size
	text.setCharacterSize(28);

	// Set color
	text.setFillColor(sf::Color::Black); // Black

	// Set text style
	text.setStyle(sf::Text::Bold);

	// Set position
	text.setPosition(pos[0].first + (rect.getSize().x / 2), pos[0].second + (rect.getSize().y) + 10);

	window.draw(text);

	// Set position of easy and hard buttons, as well as daily button
	easyBtn.setPosition(pos[0].first + (rect.getSize().x / 2), pos[0].second + (rect.getSize().y) + 75);
	window.draw(easyBtn);
	hardBtn.setPosition(pos[3].first + (rect.getSize().x / 2), pos[3].second + (rect.getSize().y) + 75);
	window.draw(hardBtn);
	dailyBtn.setPosition(window.getSize().x / 2 - 150, window.getSize().y / 2 + 100);
	window.draw(dailyBtn);

	// Display window
	window.display();

	while (window.isOpen())
	{
		sf::Event gameplay;
		while (window.pollEvent(gameplay))
		{
			if (gameplay.type == sf::Event::Closed) {
				window.close();
				return "";
			}
				

			if (gameplay.type == sf::Event::MouseButtonPressed)
			{
				//Check to see if left mouse button was pressed
				if (gameplay.mouseButton.button == sf::Mouse::Left)
				{
					std::cout << "Mouse Click";
					//Get Mouse position relative to the window and convert to 2f vector
					sf::Vector2i mousePos = sf::Mouse::getPosition(window);
					// sf::Vector2f mousePos = sf::Vector2f(mousePosition);

					std::cout << mousePos.x << " ";

					// Check easy or hard mode button, or end game button
					sf::Vector2f hardBtnPos = hardBtn.getPosition();
					sf::FloatRect hardBtnGloPos = hardBtn.getGlobalBounds();
					sf::Vector2f easyBtnPos = easyBtn.getPosition();
					sf::FloatRect easyBtnGloPos = easyBtn.getGlobalBounds();
					sf::Vector2f dailyBtnPos = dailyBtn.getPosition();
					sf::FloatRect dailyBtnGloPos = dailyBtn.getGlobalBounds();
					// sf::Vector2f exitBtnPos = exitBtn.getPosition();
					// sf::Vector2f resetBtnPos = resetBtn.getPosition();
					// std::cout << easyBtnPos << " " << easyBtnPos.x + GetWidth().x;

					if (mousePos.x > dailyBtnPos.x && mousePos.x < (dailyBtnPos.x + dailyBtnGloPos.width) && mousePos.y >  dailyBtnPos.y && mousePos.y < (dailyBtnPos.y + dailyBtnGloPos.height)) // Daily
					{
						// Daily mode
						daily = true;
					}
					else {
						//daily = false;
					}
					if (mousePos.x > easyBtnPos.x && mousePos.x < (easyBtnPos.x + easyBtnGloPos.width) && mousePos.y > easyBtnPos.y && mousePos.y < (easyBtnPos.y + easyBtnGloPos.height))
					{
						// Switch to easy mode
						std::cout << "Easy Button";
						return "easy";
					}
					else if (mousePos.x > hardBtnPos.x && mousePos.x < (hardBtnPos.x + hardBtnGloPos.width) && mousePos.y > hardBtnPos.y && mousePos.y < (hardBtnPos.y + hardBtnGloPos.height))
					{
						// Switch to hard mode
						std::cout << "Hard Button";
						return "hard";
					}
				}
			}
		}
	}
}

void GUIBase::LoadGameBoard(sf::RenderWindow& window)
{
	/* Initialize the GORDLE Gameplay Board */
	window.clear(sf::Color(0, 0, 0)); // Black

	/* TITLE INFORMATION */
	float xPos = window.getSize().x / 4 + 5;
	float yPos = 15;
	std::vector<char> title = {'G','O','R','D','L','E'};
	sf::Font font;
	sf::Text text;

	// Get font
	if (!font.loadFromFile("arial.ttf"))
	{
		std::cout << "File not loaded.";
	}

	// Print title letters
	for (int i = 0; i < title.size(); i++)
	{
		// Select font
		text.setFont(font);

		// Set string to print
		text.setString(title[i]);

		// Set the character size
		text.setCharacterSize(40);

		// Set color
		text.setFillColor(sf::Color(255,255,255)); // White
		text.setOutlineColor(sf::Color(0, 33, 165)); // Gator Blue
		text.setOutlineThickness(2);

		// Set text style
		text.setStyle(sf::Text::Bold);

		// Set position
		text.setPosition(xPos, yPos);

		window.draw(text);

		xPos += 50;
	}

	/* BASE GAMEBOARD */
	xPos = window.getSize().x / 8;
	yPos = 75;
	for (int i = 0; i < 6; i++) // Print 6 rows
	{
		for (int j = 0; j < 5; j++) // Print 5 columns
		{
			// Print gray backgrounds
			sf::Sprite grayBackground(TextureManager::GetTexture("wordleGray"));
			grayBackground.setScale(0.35, 0.35);
			grayBackground.setPosition(xPos, yPos);
			grayBackground.setColor(sf::Color::White);
			window.draw(grayBackground);

			// Update xPos
			sf::FloatRect grayBackgroundGloPos = grayBackground.getGlobalBounds();
			xPos += grayBackgroundGloPos.width + 25;
		}

		// Reset xPos, increment yPos
		xPos = window.getSize().x / 8;
		yPos += 85;
	}

	window.display();
}

/*sf::Texture& GUIBase::GetTexture(std::string textureName)
{
	//Check if the texture exists
	if (textures.find(textureName) == textures.end())
	{
		LoadTexture(textureName);
	}

	return textures[textureName];
}*/

/* MAKE SURE JUSTIN PASSES IN PREV GUESSES WITH THE MOST RECENT GUESS IN IT AS WELL */
void GUIBase::UpdateBoard(sf::RenderWindow& window, std::vector<std::string> prevGuesses, std::vector<std::string> prevColors, std::string mode, bool validGuess, bool validHardGuess)
{
	// Draw base board
	LoadGameBoard(window);

	/* TEXT AND FONT INFORMATION */
	sf::Font font;
	sf::Text text;

	// Get font
	if (!font.loadFromFile("arial.ttf"))
	{
		std::cout << "File not loaded.";
	}

	// Select font
	text.setFont(font);

	/* GAME MODE INFORMATION */
	std::string errorMsg = "";

	// Set the character size
	text.setCharacterSize(16);

	// Set color
	text.setFillColor(sf::Color::White); // Black

	// Set text style
	text.setStyle(sf::Text::Bold);

	// Set position
	text.setPosition(0,0);

	sf::RectangleShape rect(sf::Vector2f(window.getSize().x, 25));
	rect.setFillColor(sf::Color(0, 0, 0)); // Black
	rect.setPosition(0, 0);
	window.draw(rect);

	if (mode == "easy")
	{
		// Easy mode

		// Invalid word guess, display message
		if (!validGuess)
		{
			// Your guess: ... is invalid
			errorMsg = "Invalid Guess. Please retype a new word!";
			// Set string to print
			text.setString(errorMsg);

			window.draw(text);
		}
		else
		{
			window.display();
		}
	}
	else
	{
		// Hard mode
		window.display();
		
		if (!validHardGuess) // Invalid hard guess, display message
		{
			// "Your guess: ... is invalid.
			errorMsg = "Guess must include clues from previous guess. Please retype a new word!";
			// Set string to print
			text.setString(errorMsg);
			// while()
			// return
		}
		else
		{
			window.display();
		}

		// Invalid word guess, display message
		if (!validGuess)
		{
			// Your guess: ... is invalid
			errorMsg = "Invalid Guess. Please retype a new word!";
			// Set string to print
			text.setString(errorMsg);
			// while()
			// return
		}
		else
		{
			window.display();
		}

		if (!validGuess || !validHardGuess)
		{
			window.draw(text);
		}
		else
		{
			window.display();
		}
	}

	/* GAMEPLAY LOGIC */

	// Set the character size
	text.setCharacterSize(48);

	// Set color
	text.setFillColor(sf::Color(255, 255, 255)); // White
	text.setOutlineColor(sf::Color(0, 33, 165)); // Gator Blue
	text.setOutlineThickness(2);

	// Set text style
	text.setStyle(sf::Text::Bold);

	// Positional info 
	std::vector<sf::Sprite> sprites;
	float xPos = window.getSize().x / 8;
	float yPos = 75;

	// Continue with gameplay board
	for (int i = 0; i < prevGuesses.size(); i++) // 5 rows: will print all gray boxes once past number of guesses, which is okay
	{
		// Get string of colors and string for the current guess
		std::string currColor = prevColors[i];
		std::string currGuess = prevGuesses[i];

		// Iterate over string of colors for current guess
		for (int j = 0; j < currColor.size(); j++)
		{
			// Get current color and letter
			char color = currColor[j];
			char guess = currGuess[j];

			// Display proper color first, then letter on top

			// Load background textures
			sf::Sprite greenBackground(TextureManager::GetTexture("wordleGreen"));
			sf::Sprite yellowBackground(TextureManager::GetTexture("wordleYellow"));
			sf::Sprite grayBackground(TextureManager::GetTexture("wordleGray"));
			greenBackground.setScale(0.35, 0.35);
			yellowBackground.setScale(0.35, 0.35);
			grayBackground.setScale(0.35, 0.35);

			// Set position of backgrounds
			greenBackground.setPosition(xPos, yPos);
			yellowBackground.setPosition(xPos, yPos);
			grayBackground.setPosition(xPos, yPos);

			// Change gray background to black (will represent misses)
			grayBackground.setColor(sf::Color(169, 169, 169));

			// Check if color is green (G), yellow (Y), or gray (E)
			if (color == 'G')
			{
				window.draw(greenBackground);
			}
			else if (color == 'Y')
			{
				window.draw(yellowBackground);
			}
			else
			{
				window.draw(grayBackground);
			}

			//window.draw(greenBackground);

			/*yellowBackground.setPosition(XPos, YPos);
			window.draw(yellowBackground);
			grayBackground.setPosition(XPos, YPos);
			window.draw(grayBackground); */

			// Create sprite for letter
			/*sf::Sprite letter(GetTexture(std::to_string(currLetter)));
			letter.setScale(0.5, 0.5);
			letter.setPosition(pos[3].first + (rect.getSize().x / 2), pos[3].second + (rect.getSize().y) + 75);
			window.draw(letter);*/

			// Set string to print
			text.setString(guess);

			// Set position (modify position for L, since its positioning is slightly different)
			if (guess == 'l')
			{
				text.setPosition(xPos + 25, yPos);
			}
			else
			{
				text.setPosition(xPos + 15, yPos);
			}

			window.draw(text);

			// Display window
			//window.display();

			sf::Vector2f greenBackgroundPos = greenBackground.getPosition();
			sf::FloatRect greenBackgroundGloPos = greenBackground.getGlobalBounds();
			xPos += greenBackgroundGloPos.width + 25;
		}

		// window.display();

		// Reset xPos and vector of sprites, increment yPos
		xPos = window.getSize().x / 8;
		yPos += 85;
		sprites.clear();
	}

	window.display();

	/*while (window.isOpen())
	{
		sf::Event gameplay;
		while (window.pollEvent(gameplay))
		{
			if (gameplay.type == sf::Event::Closed)
				window.close();
			
			if (gameplay.type == sf::Event::KeyPressed)
				return;
		}
	}*/
}

std::string GUIBase::KeyboardInput(sf::RenderWindow& window)
{
	sf::Event getGuess;
	std::string guess = "";
	// window.setKeyRepeatEnabled(false);

	while (window.isOpen())
	{
		while (window.pollEvent(getGuess))
		{
			if(getGuess.type == sf::Event::EventType::Closed)
				window.close();

			if (getGuess.type == sf::Event::EventType::KeyPressed)
			{
				if (getGuess.key.code == sf::Keyboard::Enter)
				{
					/* EASTER EGGS */
					if (guess == "FSU")
						return "SUCKS";

					if (guess == "GO")
						return "GATOR";

					if (guess == "UF")
						return "GREAT";

					if (guess.size() == 5)
					{
						return guess; // Only allow enter if guess is 5 letters
					}
				}
				else if (getGuess.key.code == sf::Keyboard::BackSpace)
				{
					if (guess.size() > 0)
					{
						guess.pop_back(); // Execute backspace on the guess
					}
				}
				else if (guess.size() >= 5) {
					continue;
				}
				else
				{
					char temp = static_cast<char>(getGuess.key.code - sf::Keyboard::A + 'A');
					if (temp >= 'A' && temp <= 'Z')
						guess += temp; // Add proper character to guess
				}
			}		
		}
	}
}

/*void  GUIBase::Clear()
{
	textures.clear();
}*/

int main()
{
	GUIBase gui;
	GameLogic logic;
	TextureManager::downloadFont();
	sf::RenderWindow window(sf::VideoMode(600, 600), "GORDLE");

	//gui.LoadAllTextures();

	bool daily = false;

	/* std::vector<std::string> prevGuesses = {"among", "hello", "world"};
	std::vector<std::string> prevColors = {"YYYY", "YGYGY", "YGYYG"};
	bool validGuess = true;
	bool validHardGuess = true;

	gui.UpdateBoard(window, prevGuesses, prevColors, mode, validGuess, validHardGuess);

	validGuess = false;
	validHardGuess = false;
	gui.UpdateBoard(window, prevGuesses, prevColors, mode, validGuess, validHardGuess);

	prevGuesses.push_back("plants");
	prevColors.push_back("GGGGG");
	validGuess = true;
	validHardGuess = true;
	gui.UpdateBoard(window, prevGuesses, prevColors, mode, validGuess, validHardGuess);*/

	std::string mode = gui.LoadHomeBoard(window, daily);

	std::string targetWord = logic.giveTarget(daily); // Get target word

	if (mode == "") // Exit program
	{
		return 0;
	}

	std::vector<std::string> prevGuesses;
	std::vector<std::string> prevColors;
	std::string guess = "";
	bool validGuess = true;
	bool validHardGuess = true;
	int counter = 0;
	bool winner = false;

	/* TEXT AND FONT INFORMATION */
	sf::Font font;
	sf::Text text;

	// Get font
	if (!font.loadFromFile("arial.ttf"))
	{
		std::cout << "File not loaded.";
	}

	// Select font
	text.setFont(font);

	/* GAME MODE INFORMATION */
	std::string errorMsg = "";

	// Set the character size
	text.setCharacterSize(16);

	// Set color
	text.setFillColor(sf::Color::White); // Black

	// Set text style
	text.setStyle(sf::Text::Bold);

	// Set position
	text.setPosition(0, 0);

	/* GAMEPLAY */
	while (window.isOpen())
	{
		sf::Event gameplay;
		while (window.pollEvent(gameplay))
		{
			if (gameplay.type == sf::Event::Closed)
			{
				window.close();
			}	
			
			/* if(gameOver)
				*	return 0;
				* */

			if (counter == 6 || winner) // Check if game won or lost (determined at 6 guesses)
			{
				//window.pollEvent(gameplay);
				prevColors.clear();
				prevGuesses.clear();
				if (winner)
				{
					// Game is won
					text.setString("Congratulations! You got the word: " + targetWord);
					counter = 6;
					
				}
				else
				{
					// Game is lost
					text.setString("You lost :( The word was: " + targetWord);
					
				}

				window.display();
				window.draw(text);
				window.display();

				if (gameplay.type == sf::Event::EventType::KeyPressed)
				{
					if (gameplay.key.code == sf::Keyboard::Enter)
					{
						counter = 0;
						winner = false;
						daily = false;
						targetWord = logic.giveTarget(daily);
						mode = gui.LoadHomeBoard(window, daily);
					}
				}
			}

			if (counter == 0) // Check if prevGuess.size() == 0
			{
				gui.LoadGameBoard(window);
				if (daily)
					targetWord = logic.giveTarget(true);
				else
					targetWord = logic.giveTarget(false);
			}

			if (counter >= 0 && counter < 6) 
			{
				window.pollEvent(gameplay);
				if (!window.isOpen())
					return 0;
				// Get guess and check if it matches the target word
				guess = gui.KeyboardInput(window);
				if (!window.isOpen())
					return 0;

				// Check if current guess is valid
				prevGuesses.push_back(guess);
				validGuess = logic.checkValid(prevGuesses);
				if (validGuess && mode == "easy")
					prevColors.push_back(logic.checkGuess(prevGuesses, targetWord));
				else if (mode == "easy")
					prevColors.push_back("EEEEE");

				validHardGuess = logic.checkHard(prevGuesses, prevColors, mode);
				if (validHardGuess && validGuess && mode == "hard")
					prevColors.push_back(logic.checkGuess(prevGuesses, targetWord));
				else if (mode == "hard")
					prevColors.push_back("EEEEE");

				// Update board visualization
				gui.UpdateBoard(window, prevGuesses, prevColors, mode, validGuess, validHardGuess);
				if ((validGuess && mode == "easy") || (validHardGuess && validGuess && mode == "hard"))
				{
					if (prevColors[prevColors.size() - 1] == "GGGGG") // Correct guess
					{
						winner = true;
					}
					counter++;
				}
				else {
					prevGuesses.pop_back();
					prevColors.pop_back();
				}
			}
		}
	}
}
