#include "stdafx.h"
#include "Circle.h"

Circle::Circle()
{
}

Circle::~Circle()
{
}

void Circle::Init(float pallier_reached)
{
	//sf::Vector2f position_circle = sf::Vector2f(GlobalFunction::getRandomRange(center_window.x - window_dimension.x, center_window.x + window_dimension.x), GlobalFunction::getRandomRange(center_window.y - window_dimension.y, center_window.y + window_dimension.y));
	sf::Vector2f position_circle = sf::Vector2f(GlobalFunction::getRandomRange(0 +radius + 5,window_dimension.x - radius - 5), GlobalFunction::getRandomRange(0 + radius + 5, window_dimension.y - radius - 5));
	//sf::Color color = GlobalFunction::GetRandomColor();
	circle = GlobalFunction::CreateCircle(position_circle, radius, sf::Color::Blue);
	angle = GlobalFunction::getRandomRange(1, 360);
	pallier = pallier_reached;
}

void Circle::Draw(sf::RenderWindow &window)
{
	window.draw(circle);
}

void Circle::Move(float DELTATIME)
{
	sf::Vector2f current_position = circle.getPosition();
	/*if (current_position.x  < center_window.x - window_dimension.x || current_position.x  > center_window.x + window_dimension.x)
	{
		velocity.x *= -1;
	}
	if (current_position.y  < center_window.y - window_dimension.y || current_position.y  > center_window.y + window_dimension.y)
	{
		velocity.y *= -1;
	}*/
	if (clock_change_x.getElapsedTime().asSeconds() >= 0.2)
	{
		if (current_position.x - radius  < 0 || current_position.x + radius  > window_dimension.x)
		{
			velocity.x *= -1;
			clock_change_x.restart();
		}
	}
	if (clock_change_y.getElapsedTime().asSeconds() >= 0.2)
	{
		if (current_position.y - radius  < 0 || current_position.y + radius  > window_dimension.y)
		{
			velocity.y *= -1;
			clock_change_y.restart();
		}
	}
	float angle_modified = angle * PI * 180;
	circle.move(cos(angle_modified)*speed*velocity.x*DELTATIME, sin(angle_modified)*speed*velocity.y*DELTATIME);
	if (clock_lifetime.getElapsedTime().asSeconds() >= 4)
	{
		float number = GlobalFunction::getRandomRange(1, 10000);
		/*if (number <= 5)
		{
			angle = GlobalFunction::getRandomRange(1, 360);
		}*/
		/*if (number <= 10)
		{
			ChangeColor();
		}*/
	}
	if (!do_once_set_color_blue)
	{
		if (clock_lifetime.getElapsedTime().asSeconds() >= 2)
		{
			circle.setFillColor(sf::Color::Blue);
			do_once_set_color_blue = true;
		}
	}
}

void Circle::ChangeColor()
{
	circle.setFillColor(GlobalFunction::GetRandomColor());
}

void Circle::ChangeSize()
{
	/*if (increasing_size == 1)
	{
		if (radius < initial_radius+initial_radius/2)
		{
			circle.setRadius(radius + growing_rate);
			radius += growing_rate;
		}
	}
	else
	{
		if (radius > initial_radius/2)
		{
			circle.setRadius(radius - growing_rate);
			radius -= growing_rate;
		}
	}*/
}

void Circle::ChangePosition(sf::Vector2f position_received)
{
	circle.setPosition(position_received);
}

void Circle::ChooseAsFollowedCircle()
{
	being_followed = true;
	circle.setFillColor(sf::Color::Red);
}

sf::String Circle::CheckIfRightCircle(sf::Vector2f mouse_position)
{
	if (being_followed)
	{
		if (!already_checked)
		{
			if (GlobalFunction::GetDistanceBetweenTwoPositions(mouse_position, circle.getPosition()) <= radius)
			{
				return "Right";
			}
		}
		else
		{
			return "Checked";
		}
	}
	return "Wrong";
}

void Circle::RestartClockLifetime()
{
	clock_lifetime.restart();
}
