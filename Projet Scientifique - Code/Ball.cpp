#include "stdafx.h"
#include "Ball.h"

Ball::Ball()
{
	if (!font.loadFromFile("Constantine.ttf"))
	{
		std::cout << "Error with green flame in skillinterface" << std::endl;
	}
}

Ball::~Ball()
{
}

void Ball::Init(bool pratice_mode)
{
	this->pratice_mode = pratice_mode;
	sf::Vector2f position_circle = sf::Vector2f(window_dimension.x / 2, window_dimension.y / 2);
	circle = GlobalFunction::CreateCircle(position_circle, radius, sf::Color::White);
	paddle[0] = GlobalFunction::CreateRectangleWithOrigin(size_paddle, sf::Vector2f(50, window_dimension.y / 2), sf::Color::White);
	paddle[1] = GlobalFunction::CreateRectangleWithOrigin(size_paddle, sf::Vector2f(window_dimension.x - 50, window_dimension.y / 2), sf::Color::White);
	text_last_distance = GlobalFunction::CreateText(sf::Vector2f(window_dimension.x - 200, 50), "Missing string", font, 24);
	text_pallier = GlobalFunction::CreateText(sf::Vector2f(window_dimension.x - 200, 100), "Missing string", font, 24);
}

void Ball::Draw(sf::RenderWindow &window)
{
	string_last_distance.clear();
	string_last_distance = "Dernière distance: ";
	string_last_distance = GlobalFunction::InsertNumberToString(string_last_distance, last_distance, string_last_distance.getSize());
	string_pallier.clear();
	string_pallier = "Palliers: ";
	string_pallier = GlobalFunction::InsertNumberToString(string_pallier,number_step_reached, string_pallier.getSize());
	text_last_distance.setString(string_last_distance);
	text_pallier.setString(string_pallier);
	window.draw(circle);
	window.draw(text_last_distance);
	window.draw(text_pallier);
	window.draw(paddle[0]);
	window.draw(paddle[1]);
	if (clock_changing_color.getElapsedTime().asSeconds() >= 0.1)
	{
		circle.setFillColor(sf::Color::White);
	}
}

void Ball::Move(float DELTATIME)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		if (clock_changing_direction.getElapsedTime().asSeconds() >= reset_time)
		{
			CalculateDistanceFromPaddle();
			velocity.x *= -1;
			number_step_reached++;
			clock_changing_direction.restart();
			speed += speed_initial*percent_speed;
		}
	}
	if (DELTATIME <= 0.5)
	{
		circle.move(speed*velocity.x*DELTATIME, 0);
	}
	CheckCollision();
}

void Ball::PositionCenter()
{
	circle.setPosition(sf::Vector2f(sf::Vector2f(window_dimension.x / 2, window_dimension.y / 2)));
}

void Ball::CheckCollision()
{
	sf::Vector2f position_circle = circle.getPosition();
	sf::Vector2f position_paddle0 = paddle[0].getPosition();
	sf::Vector2f position_paddle1 = paddle[1].getPosition();
	if (position_circle.x - radius < position_paddle0.x + size_paddle.x/2 || position_circle.x + radius > position_paddle1.x - size_paddle.x/2)
	{
		circle.setFillColor(sf::Color::Red);
		clock_changing_color.restart();
		number_step_reached++;
		clock_changing_direction.restart();
		velocity.x *= -1;
		speed += speed_initial*percent_speed;
		last_distance = penalty;
		total_distances += penalty;
		number_penalities++;
		if (position_circle.x >= window_dimension.x / 2)
		{
			circle.setPosition(position_circle - sf::Vector2f(2, 0));
		}
		else
		{
			circle.setPosition(position_circle + sf::Vector2f(2, 0));
		}
		if (!pratice_mode)
		{
			std::string string_to_file;
			std::string holder = "-";
			string_to_file = GlobalFunction::InsertStringToString(string_to_file, holder);
			string_to_file = GlobalFunction::InsertNumberToSTDString(string_to_file, penalty);
			holder = "-";
			string_to_file = GlobalFunction::InsertStringToString(string_to_file, holder);
			DataTextManager::instance()->WriteInTestBall(string_to_file);
		}
	}
}

int Ball::GetNumberStep()
{
	return number_step_reached;
}

float Ball::GetAverageDistance()
{
	return total_distances / number_step_reached;
}

void Ball::CalculateDistanceFromPaddle()
{
	float distance_from_paddle = 0;
	if (velocity.x == 1)
	{
		distance_from_paddle = GlobalFunction::GetDistanceBetweenTwoPositions(circle.getPosition(), paddle[1].getPosition()) - radius_and_paddle_size;
	}
	else
	{
		distance_from_paddle = GlobalFunction::GetDistanceBetweenTwoPositions(circle.getPosition(), paddle[0].getPosition()) - radius_and_paddle_size;
	}
	if (!pratice_mode)
	{
		std::string string_to_file;
		std::string holder = "-";
		string_to_file = GlobalFunction::InsertStringToString(string_to_file, holder);
		string_to_file = GlobalFunction::InsertNumberToSTDString(string_to_file, distance_from_paddle);
		holder = "-";
		string_to_file = GlobalFunction::InsertStringToString(string_to_file, holder);
		DataTextManager::instance()->WriteInTestBall(string_to_file);
	}
	last_distance = distance_from_paddle;
	total_distances += distance_from_paddle;
}