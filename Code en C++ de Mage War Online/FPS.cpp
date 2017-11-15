#include "stdafx.h"
#include "FPS.h"

FPS::FPS()
{
	font.loadFromFile("Constantine.ttf");
}

FPS::~FPS()
{
}

void FPS::UpdateFPS(sf::Vector2f position_view_player)
{
	current_FPS++;
	if (clock_FPS.getElapsedTime().asMilliseconds() >= 1000)
	{
		last_FPS = current_FPS;
		current_FPS = 0;
		clock_FPS.restart();

		string_FPS.clear();
		string_FPS = "FPS: ";
		string_FPS = GlobalFunction::InsertNumberToString(string_FPS, last_FPS, string_FPS.getSize());

		text_FPS = GlobalFunction::CreateTextWithNoOrigin(position_FPS, string_FPS, font, 20);
	}
	text_FPS.setPosition(position_FPS + position_view_player);
}

void FPS::DrawFPS(sf::RenderWindow &window)
{
	window.draw(text_FPS);
}
