#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GlobalFunction.h"
#include <vector>
#include <math.h>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <list>

class Ball
{
private:
	sf::String string_last_distance;
	sf::String string_pallier;
	sf::Text text_last_distance;
	sf::Text text_pallier;
	sf::Font font;
	sf::Vector2f window_dimension{ 1300, 700 };
	float speed = 500;
	float speed_initial = 500;
	sf::Vector2f velocity{ 1,1 };
	sf::Clock clock_changing_direction;
	sf::Clock clock_changing_color;
	sf::CircleShape circle;
	sf::RectangleShape paddle[2];
	sf::Vector2f size_paddle{ 15,100 };
	float radius = 20;
	float percent_speed = 0.025;
	int number_step_reached = 0;
	float total_distances = 0;
	float last_distance = 0;
	float radius_and_paddle_size = size_paddle.x / 2 + radius;
	float reset_time = 1;
	float penalty = 100;
	bool pratice_mode = true;
public:
	Ball();
	~Ball();

	int number_penalities = 0;

	void Init(bool pratice_mode);
	void Draw(sf::RenderWindow &window);
	void Move(float DELTATIME);
	void PositionCenter();
	void CheckCollision();
	void CalculateDistanceFromPaddle();
	int GetNumberStep();
	float GetAverageDistance();
};
