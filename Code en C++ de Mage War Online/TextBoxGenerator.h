#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "TextBox.h"
#include <iostream>
#include <list>

class TextBoxGenerator
{
private:
	std::list<std::shared_ptr<TextBox>> listTextBox;
	static TextBoxGenerator *s_instance;
public:
	TextBoxGenerator();
	~TextBoxGenerator();

	static void Initialize()
	{
		s_instance = new TextBoxGenerator();
	}
	static TextBoxGenerator *instance()
	{
		if (!s_instance)
			s_instance = new TextBoxGenerator;
		return s_instance;
	}

	void GenerateOneTextBox(std::vector<sf::String> listString, std::vector<bool> listIfCentered, std::vector<int> listLetterSize, sf::Vector2f mouse_position);
	void GenerateOneTextBoxWithColor(std::vector<sf::String> listString, std::vector<bool> listIfCentered, std::vector<int> listLetterSize, sf::Vector2f mouse_position,sf::Color color_middle,sf::Color color_around);
	void GenerateOneTextBoxWithSize(std::vector<sf::String> listString, std::vector<bool> listIfCentered, std::vector<int> listLetterSize, sf::Vector2f mouse_position, int number_character_line);
	void AdjustPositionTextBox(sf::Vector2f position_view_player);
	void DrawAllTextbox(sf::RenderWindow &window);
	void ClearList();
};

