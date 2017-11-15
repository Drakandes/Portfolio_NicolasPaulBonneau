#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GlobalEnum.h"
#include "GlobalFunction.h"
#include <iostream>
#include "CollisionalObject.h"

class RectTest : public CollisionalObject
{
private:
	sf::Vector2f size{ 20,20 };
	sf::RectangleShape rect;
public:
	virtual int GetTypeCollisionalObject() { return Projectile_E; }
	virtual sf::FloatRect GetCollisionRect() { return rect.getGlobalBounds(); }
	virtual sf::Vector2f GetCurrentPosition();
	virtual sf::Vector2f GetSize();
	virtual void Draw(sf::RenderWindow &window);
	RectTest(sf::Vector2f position);
	~RectTest();
};

