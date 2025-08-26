#pragma once
#include <SFML/Graphics.hpp>
#include "customVertexArrays.h"
#include <string>
#include <vector>
#include <any>


//Init Font
inline sf::Font font("Roboto-Medium.ttf");

class promptWindow {

private:
	//Spacing Variables
	sf::Vector2f promptPosition;
	float borderLength;
	float borderHeigth;
	float maxBorderLength;
	float padding = 10.0f;
	float lineDistance = 2.5f;

	//Text Variables
	std::string promptText;
	std::any sfPromptText;
	float charSize = 14;
	uint16_t lineNumber = 0;

	//Text Line Container
	std::vector<sf::Text> textLines;

	//Border Object
	sf::VertexArray border;

	//Text Bounds
	sf::FloatRect textBounds;
	

public:

	

	//Constructor
	promptWindow(std::string txt, sf::Vector2f PromptPosition, float MaxBorderLength) {
		
		promptPosition = PromptPosition;
		sf::Vector2f textStartPos = promptPosition + sf::Vector2f{ padding, padding };

		//Handle Text Objects
		promptText = txt;
		sfPromptText = sf::Text(font);
		std::any_cast<sf::Text&>(sfPromptText).setString(txt);
		std::any_cast<sf::Text&>(sfPromptText).setCharacterSize(charSize);
		std::any_cast<sf::Text&>(sfPromptText).setPosition(textStartPos);

		
		maxBorderLength = MaxBorderLength;

		
		//set borderLength so that text is inside border
		textBounds = std::any_cast<sf::Text&>(sfPromptText).getGlobalBounds();
		
		//"for now" set borderLength/Heigth to be as long as the text + the padding on each side //will be overwritten later if text is too long for a single line
		borderLength = 2 * padding + textBounds.size.x;

		

		//Split String in mutliple strings across Lines when too long
		if (textBounds.size.x > maxBorderLength) {
			borderLength = maxBorderLength;

			while (!promptText.empty()) {
				std::string text; //holds all chars we want to add to the line
				sf::Text textLine(font); //actual sf Object, needed to get Bounds of sf::Text Object
				textLine.setCharacterSize(charSize);

				while (textLine.getGlobalBounds().size.x < (maxBorderLength - 2 * padding - 4.0f) && !promptText.empty()) { //while under max text borderLength
					char chr = promptText.front(); //get first char
					promptText.erase(promptText.begin()); //erase first char from promptText
					text.insert(text.end(), chr); //insert first char into new text object
					textLine.setString(text); //set string to text
					//repeat as long as textLine is not longer than maximum allowed borderLength	
				}

			textLine.setPosition(textStartPos + sf::Vector2f({ 0.0f, (charSize + lineDistance) * lineNumber }));
			textLines.insert(textLines.begin(), textLine); //append textLine to our textLines vector
			
			lineNumber++; //increment lineNumber by 1
			std::cout << static_cast<std::string>(textLine.getString()) << '\n';
			}
		}
		else {
			lineNumber = 1;
			textLines.insert(textLines.begin(), std::any_cast<sf::Text&>(sfPromptText));
		}

		borderHeigth = 2 * padding + lineNumber * (charSize + lineDistance);
		border = createRoundedRectangleBorder(promptPosition, 8, borderLength, borderHeigth, 2.0f, sf::Color::White, 32); //TODO: connect values
		
	}

	//Draw prompt window
	void draw(sf::RenderWindow& window) {
		window.draw(border);

		for (std::any element : textLines) {
			window.draw(std::any_cast<sf::Text&>(element));
		}
		
		
	}
};