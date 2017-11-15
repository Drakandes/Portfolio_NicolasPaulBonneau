#include "stdafx.h"
#include "RectTest.h"

RectTest::RectTest(sf::Vector2f position)
{
	rect = GlobalFunction::CreateRectangleWithOrigin(size, position, sf::Color::Blue);
}

RectTest::~RectTest()
{
}

sf::Vector2f RectTest::GetCurrentPosition()
{
	return rect.getPosition();
}

sf::Vector2f RectTest::GetSize()
{
	return size;
}

void RectTest::Draw(sf::RenderWindow &window)
{
	window.draw(rect);
}
