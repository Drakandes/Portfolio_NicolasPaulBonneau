#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GlobalFunction.h"
#include <vector>
#include "Ball.h"
#include <list>
#include "Deltatime.h"

class TestJugement
{
private:
	sf::Vector2f window_dimension{ 1300, 700 };
	std::vector<Ball*> listCircle;
	float maixmum_circle = 60;
	float starting_circle = 20;
	bool starting = true;
	bool in_game = true;
	int number_of_circle_being_followed = 1;
	sf::Text text;
	sf::String string = "Test de la balle rebondissante";
	sf::RectangleShape rect;
	sf::Font font;
	sf::Vector2f size_rect;
	Deltatime deltatime_gestion;
	float DELTATIME;
	bool pratice_mode = true;
	int number_try = 1;
public:
	TestJugement();
	~TestJugement();

	void MainLoop(sf::RenderWindow &window, bool pratice_mode);
	void MoveCircle(float DELTATIME);
	void DrawCircle(sf::RenderWindow &window);
	void StartingGame(sf::RenderWindow &window);
	void Win(sf::RenderWindow &window);
	void GameOver(sf::RenderWindow &window);
	bool WhileInMenu(sf::RenderWindow &window);
};



