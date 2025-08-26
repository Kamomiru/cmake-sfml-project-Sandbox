#pragma once
#include <SFML/Graphics.hpp>
#include "customVertexArrays.h"
#include <string>
#include <vector>
#include <any>

//Init Font
inline sf::Font font("Roboto-Medium.ttf");

class promptWindowTwo {
private:
	std::any sfText;

public: 
	promptWindowTwo(std::string str) {
		sfText = sf::Text(font);
		std::any_cast<sf::Text&>(sfText).setString(str);
	}

	void draw(sf::Vector2f pos, sf::RenderWindow& window) {
		std::any_cast<sf::Text&>(sfText).setPosition(pos);
		std::any_cast<sf::Text&>(sfText).setCharacterSize(16);
		std::any_cast<sf::Text&>(sfText).setFillColor(sf::Color::White);
		std::any_cast<sf::Text&>(sfText).setFont(font);
		window.draw(std::any_cast<sf::Text&>(sfText));
	}
};