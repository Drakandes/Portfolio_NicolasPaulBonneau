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

class Circle
{
private:
	sf::Vector2f center_window{ 650,350 };
	//sf::Vector2f window_dimension{250, 250};
	sf::Vector2f window_dimension{ 1300, 700 };
	sf::Vector2f velocity{ 1,1 };
	sf::CircleShape circle;
	float angle;
	float initial_radius = 30;
	float radius = 40;
	float growing_rate = 0.01;
	float increasing_size = 1;
	float pallier = 0;
	bool being_followed = false;
	bool already_checked = false;
	bool do_once_set_color_blue = false;
	sf::Clock clock_lifetime;
	sf::Clock clock_change_x;
	sf::Clock clock_change_y;
public:
	Circle();
	~Circle();

	float speed = 180;
	void Init(float pallier_reached);
	void Draw(sf::RenderWindow &window);
	void Move(float DELTATIME);
	void ChangeColor();
	void ChangeSize();
	void ChangePosition(sf::Vector2f position_received);
	void ChooseAsFollowedCircle();
	sf::String CheckIfRightCircle(sf::Vector2f mouse_position);
	void RestartClockLifetime();
};

