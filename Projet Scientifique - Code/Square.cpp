#include "stdafx.h"
#include "Square.h"

Square::Square()
{
}

Square::~Square()
{
}

void Square::Init()
{
	sf::Vector2f position_circle = sf::Vector2f(GlobalFunction::getRandomRange(0 + rect_size.x + 5, window_dimension.x - rect_size.x - 5), GlobalFunction::getRandomRange(0 + rect_size.x + 5, window_dimension.y - rect_size.x - 5));
	rect = GlobalFunction::CreateRectangleWithOrigin(rect_size, position_circle, sf::Color::White);
}

void Square::Draw(sf::RenderWindow &window)
{
	if (clock_lifetime.getElapsedTime().asSeconds() >= lifetime)
	{
		is_to_delete = true;
	}
	window.draw(rect);
}

bool Square::CheckIfToDelete()
{
	return is_to_delete;
}

