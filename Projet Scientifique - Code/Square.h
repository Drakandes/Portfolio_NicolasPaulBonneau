#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GlobalFunction.h"
#include <vector>
#include <sstream>
#include <iomanip>
#include <iostream>

class Square
{
private:
	sf::Vector2f window_dimension{ 1300, 700 };
	sf::RectangleShape rect;
	sf::Vector2f rect_size{ 25,25 };
	sf::Clock clock_lifetime;
	float lifetime = 0.05;
	bool is_to_delete = false;
public:
	Square();
	~Square();

	void Init();
	void Draw(sf::RenderWindow &window);
	bool CheckIfToDelete();
};

