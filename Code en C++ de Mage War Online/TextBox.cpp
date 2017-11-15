#include "stdafx.h"
#include "TextBox.h"
#include "ListObjectsSingleton.h"

TextBox::TextBox()
{
	if (!font.loadFromFile("Constantine.ttf"))
	{
		std::cout << "Error font player" << std::endl;
	}
}

TextBox::~TextBox()
{
}

void TextBox::CreateTextBox(std::vector<sf::String> listString, std::vector<bool> listIfCentered, std::vector<int> listLetterSize, sf::Vector2f mouse_position,int number_character_line)
{
	sf::Vector2f size_rectangle_information;

	sf::Vector2f mouse_position_modified = sf::Vector2f(mouse_position.x, mouse_position.y + 15);
	float distance_from_first_text = 0;

	sf::Vector2f position_rectangle_information_modified = position_rectangle_information;

	for (int number = 0; number < listString.size(); number++)
	{
		if (listIfCentered[number])
		{
			sf::Text text;
			text.setCharacterSize(listLetterSize[number]);
			text.setFont(font);

			if (listString[number].getSize() > number_character_line+1)
			{
				int position = number_character_line;
				while (listString[number].substring(position, 1) == " ")
				{
					position--;
				}
				sf::String splitted_string = listString[number].substring(position+1, listString[number].getSize() - position);
				listString[number].erase(position + 1, listString[number].getSize() - position);
				listString.insert(listString.begin() + number + 1, splitted_string);
				listIfCentered.insert(listIfCentered.begin() + number + 1, listIfCentered[number]);
				listLetterSize.insert(listLetterSize.begin() + number + 1, listLetterSize[number]);
			}

			text.setString(listString[number]);
			sf::FloatRect text_bounds = text.getGlobalBounds();
			text.setOrigin(sf::Vector2f(text_bounds.width / 2,0));
			text.setPosition(mouse_position_modified.x, mouse_position_modified.y + distance_from_first_text);
			distance_from_first_text += 6;
			distance_from_first_text += text.getGlobalBounds().height;
			height_box += listLetterSize[number]+2;
			if (size_biggest_text < text_bounds.width)
			{
				size_biggest_text = text_bounds.width;
			}
			listText.push_back(text);
		}
		else
		{
			sf::Text text;
			text.setCharacterSize(listLetterSize[number]);
			text.setFont(font);

			if (listString[number].getSize() > number_character_line+1)
			{
				int position = number_character_line;
				while (listString[number].substring(position, 1) != " ")
				{
					position--;
				}
				sf::String splitted_string = listString[number].substring(position + 1, listString[number].getSize() - position);
				listString[number].erase(position + 1, listString[number].getSize() - position);
				listString.insert(listString.begin() + number + 1, splitted_string);
				listIfCentered.insert(listIfCentered.begin() + number + 1, listIfCentered[number]);
				listLetterSize.insert(listLetterSize.begin() + number + 1, listLetterSize[number]);
			}

			text.setString(listString[number]);
			sf::FloatRect text_bounds = text.getGlobalBounds();
			text.setPosition(mouse_position_modified.x, mouse_position_modified.y + distance_from_first_text);
			distance_from_first_text += 3;
			distance_from_first_text += text.getGlobalBounds().height;
			height_box += listLetterSize[number];
			if (size_biggest_text < text_bounds.width)
			{
				size_biggest_text = text_bounds.width;
			}
			listText.push_back(text);
		}
	}

	for (int holder = 0; holder < listString.size(); holder++)
	{
		if (listIfCentered[holder])
		{
			listText[holder].setPosition(listText[holder].getPosition() + sf::Vector2f(size_biggest_text/ 2, 0));
		}
	}

	if (listText.size() == 1)
	{
		height_box += 5;
	}
	else if (listText.size() == 2)
	{
		height_box += 3;
	}

	height_box += listString.size();

	box = GlobalFunction::CreateRectangle(sf::Vector2f(size_biggest_text, height_box) + sf::Vector2f(4,4), mouse_position_modified);
	box.setFillColor(sf::Color::Color(70, 130, 180,215));
	box.setOutlineColor(sf::Color::Color(70, 130, 180));
	box.setOutlineThickness(4);
}

void TextBox::AdjustPositionTextBox(sf::Vector2f position_view_player)
{
	sf::Vector2f windowe_size = ListObjectsSingleton::instance()->GetSizeWindow();
	sf::Vector2f position_box = box.getPosition();
	sf::Vector2f position_box_modified = position_box - position_view_player;
	if (position_box_modified.x + box.getSize().x > windowe_size.x)
	{
		for (size_t i = 0; i < listText.size(); i++)
		{
			listText[i].setPosition(listText[i].getPosition() - sf::Vector2f(position_box_modified.x + box.getSize().x - windowe_size.x + 50,0));
		}
		box.setPosition(box.getPosition() - sf::Vector2f(position_box_modified.x + box.getSize().x - windowe_size .x+50, 0));
	}
	if (position_box_modified.y + box.getSize().y > windowe_size.y)
	{
		for (size_t i = 0; i < listText.size(); i++)
		{
			listText[i].setPosition(listText[i].getPosition() - sf::Vector2f(0, position_box_modified.y + box.getSize().y - windowe_size.y + 50));
		}
		box.setPosition(box.getPosition() - sf::Vector2f(0, position_box_modified.y + box.getSize().y - windowe_size.y + 50));
	}
}

void TextBox::DrawTextBox(sf::RenderWindow &window)
{
	window.draw(box);
	for (size_t i = 0; i < listText.size(); i++)
	{
		window.draw(listText[i]);
	}
}

void TextBox::ChangeColorTextBox(sf::Color color_around_dark, sf::Color color_middle_transparent)
{
	box.setFillColor(color_middle_transparent);
	box.setOutlineColor(color_around_dark);
}