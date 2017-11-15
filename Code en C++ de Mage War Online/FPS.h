#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GlobalEnum.h"
#include "GlobalFunction.h"

class FPS
{
private:
	sf::Font font;
	float last_FPS = 0;
	float current_FPS = 0;
	sf::Clock clock_FPS;
	sf::String string_FPS;
	sf::Text text_FPS;
	sf::Vector2f position_FPS{ 1500, 20 };
public:
	FPS();
	~FPS();

	void UpdateFPS(sf::Vector2f position_view_player);
	void DrawFPS(sf::RenderWindow &window);
};

