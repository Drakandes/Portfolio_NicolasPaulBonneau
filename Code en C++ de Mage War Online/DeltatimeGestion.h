#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class DeltatimeGestion
{
private:
	sf::Clock clock_deltatime;
	float last_time = 0;
	float current_time = 0;
public:
	DeltatimeGestion();
	~DeltatimeGestion();

	float GetDeltaTime();
};

