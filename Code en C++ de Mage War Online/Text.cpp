#include "stdafx.h"
#include "Text.h"

Text::Text()
{
	text_speed = 50;
	font.loadFromFile("Constantine.ttf");
	angle_going = GlobalFunction::getRandomRange(0, 180);
	if (angle_going > 90)
	{
		position_random = sf::Vector2f(-GlobalFunction::getRandomRange(1, 10), 0);
	}
	else
	{
		position_random = sf::Vector2f(GlobalFunction::getRandomRange(1, 10), 0);
	}
}

Text::~Text()
{
	parent.reset();
}

bool Text::IsNeedToDelete()
{
	if (Time_until_text_disappear.getElapsedTime().asSeconds() >= time_alive)
	{
		return true;
	}
	return false;
}

void Text::Draw_text(sf::RenderWindow &window)
{
	window.draw(text);
}

void Text::MoveText()
{
	sf::Vector2f entity_position = parent->GetCurrentPosition();
	sf::Vector2f entity_size = parent->GetSize();
	if (dps_text)
	{
		text.setPosition(entity_position.x - 10 + position_random.x + (cos(angle_going/180*PI))*(Time_until_text_disappear.getElapsedTime().asSeconds() * text_speed), position_random.y + entity_position.y + 5 + entity_size.y + (sin(angle_going / 180 * PI))*(Time_until_text_disappear.getElapsedTime().asSeconds() * text_speed));
	}
	else
	{
		text.setPosition(entity_position.x - 10 + position_random.x + (cos(angle_going / 180 * PI))*(Time_until_text_disappear.getElapsedTime().asSeconds() * text_speed), entity_position.y + position_random .y - 5 - entity_size.y - (sin(angle_going / 180 * PI))*(Time_until_text_disappear.getElapsedTime().asSeconds() * text_speed));
	}
}

void Text::ChangeTextColor(sf::Color color)
{
	text.setFillColor(color);

	if (color == sf::Color::Green)
	{
		text.setCharacterSize(18);
		angle_going = 90;
		text_speed = text_speed / 3;
		time_alive = 0.5;
		position_random = sf::Vector2f(0, 17);
	}
	else if (color == sf::Color::Blue)
	{
		text.setCharacterSize(18);
		angle_going = 90;
		text_speed = text_speed / 3;
		time_alive = 0.5;
		position_random = sf::Vector2f(0, 17);
	}
	else if (color == sf::Color::Red)
	{
		text.setCharacterSize(20);
		if (angle_going > 90)
		{
			position_random = sf::Vector2f(-GlobalFunction::getRandomRange(1, 10), -GlobalFunction::getRandomRange(0, 10));
		}
		else
		{
			position_random = sf::Vector2f(GlobalFunction::getRandomRange(1, 10), -GlobalFunction::getRandomRange(0,10));
		}
	}
	else if (color == sf::Color::Color(128, 128, 128))
	{
		text.setCharacterSize(20);
		if (angle_going > 90)
		{
			position_random = sf::Vector2f(-GlobalFunction::getRandomRange(5, 30), -GlobalFunction::getRandomRange(0, 10));
		}
		else
		{
			position_random = sf::Vector2f(GlobalFunction::getRandomRange(5, 30), GlobalFunction::getRandomRange(0, 10));
		}
	}

	else if (color == sf::Color::Yellow)
	{
		text.setCharacterSize(18);
		angle_going = 90;
		text_speed = text_speed / 3;
		time_alive = 0.75;
		position_random = sf::Vector2f(0, 0);
	}
}