#include "stdafx.h"
#include "TextBoxGenerator.h"

TextBoxGenerator::TextBoxGenerator()
{
}

TextBoxGenerator::~TextBoxGenerator()
{
}

void TextBoxGenerator::GenerateOneTextBox(std::vector<sf::String> listString, std::vector<bool> listIfCentered, std::vector<int> listLetterSize, sf::Vector2f mouse_position)
{
	std::shared_ptr<TextBox> textbox = std::shared_ptr<TextBox>(new TextBox);
	textbox->CreateTextBox(listString, listIfCentered, listLetterSize, mouse_position,50);
	listTextBox.push_back(textbox);
	textbox.reset();
}

void TextBoxGenerator::GenerateOneTextBoxWithSize(std::vector<sf::String> listString, std::vector<bool> listIfCentered, std::vector<int> listLetterSize, sf::Vector2f mouse_position, int number_character_line)
{
	std::shared_ptr<TextBox> textbox = std::shared_ptr<TextBox>(new TextBox);
	textbox->CreateTextBox(listString, listIfCentered, listLetterSize, mouse_position, number_character_line);
	listTextBox.push_back(textbox);
	textbox.reset();
}

void TextBoxGenerator::AdjustPositionTextBox(sf::Vector2f position_view_player)
{
	std::list<std::shared_ptr<TextBox>>::iterator i = listTextBox.begin();
	while (i != listTextBox.end())
	{
		(*i)->AdjustPositionTextBox(position_view_player);
		i++;
	}
}

void TextBoxGenerator::ClearList()
{
	listTextBox.clear();
}

void TextBoxGenerator::DrawAllTextbox(sf::RenderWindow &window)
{
	std::list<std::shared_ptr<TextBox>>::iterator i = listTextBox.begin();
	while (i != listTextBox.end())
	{
		(*i)->DrawTextBox(window);
		listTextBox.erase(i++);
	}
}

void TextBoxGenerator::GenerateOneTextBoxWithColor(std::vector<sf::String> listString, std::vector<bool> listIfCentered, std::vector<int> listLetterSize, sf::Vector2f mouse_position, sf::Color color_middle, sf::Color color_around)
{
	std::shared_ptr<TextBox> textbox = std::shared_ptr<TextBox>(new TextBox);
	textbox->CreateTextBox(listString, listIfCentered, listLetterSize, mouse_position, 50);
	textbox->ChangeColorTextBox(color_around, color_middle);
	listTextBox.push_back(textbox);
	textbox.reset();
}

TextBoxGenerator* TextBoxGenerator::s_instance = 0;
