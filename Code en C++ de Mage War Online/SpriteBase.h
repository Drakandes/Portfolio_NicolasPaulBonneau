#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class SpriteBase
{
public:
	SpriteBase();
	~SpriteBase();

	virtual bool DrawOnTheFloor() { return false; }
	virtual sf::Vector2f GetCurrentPosition();
	virtual void Draw(sf::RenderWindow &window);
	virtual void DrawShadow(sf::RenderWindow &window);
	virtual bool SpriteHasShadow() { return false; }
	virtual sf::Vector2f GetCurrentPositionShadow() { return sf::Vector2f(-100, -100); }
};
