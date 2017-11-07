#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GlobalFunction.h"
#include <vector>
#include <list>
#include "Circle.h"
#include "Deltatime.h"

class TestCercle
{
private:
	sf::CircleShape white_spot;
	sf::Vector2f window_dimension{ 1300, 700 };
	std::vector<Circle*> listCircle;
	sf::Clock clock_adding_circle;
	sf::Clock clock_game;
	sf::Color background_color;
	sf::Clock clock_background_color;
	sf::Clock clock_mouse_click_timer;
	int background_color_increasing[3];
	int background_color_number[3];
	int background_color_increasing_color_rate[3];
	float initial_starting_circle = 2;
	float initial_maximum_circle = 15;
	float initial_speed = 220;
	float speed = 220;
	float maximum_circle = 15;
	float starting_circle = 2;
	bool starting = true;
	bool skipped_pallier = false;
	bool in_game = true;
	float skipping_pallier = 0;
	float pallier = 1;
	sf::Text text;
	sf::String string = "Test des cercles en mouvement";
	sf::RectangleShape rect;
	sf::Font font;
	sf::Vector2f size_rect;
	Deltatime deltatime_gestion;
	float DELTATIME;
	sf::Text text_pallier;
	sf::String string_pallier;
	bool pratice_mode = true;
	int number_try = 1;
public:
	TestCercle();
	~TestCercle();

	void SkipPallier();
	void MainLoop(sf::RenderWindow &window, bool pratice_mode);
	void AddCircleToList();
	void MoveCircle(float DELTATIME);
	void DrawCircle(sf::RenderWindow &window);
	void CircleAddingGestion(sf::RenderWindow &window);
	void BackgroundColorGestion(sf::RenderWindow &window);
	void CheckIfFollowingRightCircle(sf::RenderWindow &window);
	void StartingGame(sf::RenderWindow &window);
	void Win(sf::RenderWindow &window);
	void GameOver(sf::RenderWindow &window);
	bool WhileInMenu(sf::RenderWindow &window);
	void UpgradePallier();
	void PallierOnScreen(sf::RenderWindow &window);
};

