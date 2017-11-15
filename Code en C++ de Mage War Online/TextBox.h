#pragma once
#include "GlobalFunction.h"
#include "GlobalEnum.h"
#include "SFML\Graphics.hpp"
#include <vector>

class TextBox
{
private:
	sf::Vector2f position_rectangle_information{ 0,0 };
	std::vector<sf::Text> listText;
	sf::RectangleShape box;
	sf::Font font;
	float size_biggest_text = 0;
	float height_box = 0;
public:
	TextBox();
	~TextBox();

	void CreateTextBox(std::vector<sf::String> listString, std::vector<bool> listIfCentered, std::vector<int> listLetterSize, sf::Vector2f mouse_position, int number_character_line);
	void ChangeColorTextBox(sf::Color color_around_dark,sf::Color color_middle_transparent);
	void AdjustPositionTextBox(sf::Vector2f position_view_player);
	void DrawTextBox(sf::RenderWindow &window);
};

