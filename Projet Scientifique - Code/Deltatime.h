#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Deltatime
{
private:
	sf::Clock clock_deltatime;
	float last_time = 0;
	float current_time = 0;
public:
	Deltatime();
	~Deltatime();

	float GetDeltaTime();
};