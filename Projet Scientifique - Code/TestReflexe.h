#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GlobalFunction.h"
#include <vector>
#include "Square.h"
#include <list>
#include "Deltatime.h"

class TestReflexe
{
private:
	sf::CircleShape white_spot; 
	std::list<Square*> listRect;
	sf::Vector2f window_dimension{ 1300, 700 };
	bool starting = true;
	bool in_game = true;
	sf::Text text;
	sf::String string = "Test des reflexes";
	sf::RectangleShape rect;
	sf::Font font;
	sf::Vector2f size_rect;
	Deltatime deltatime_gestion;
	sf::Clock clock_game;
	float time_reset = GlobalFunction::getRandomRange(500,3000)/1000;
	float DELTATIME;
	int number_spawned_rect = 0;
	int number_rect_max = 30;
	float reaction_time_total = 0;
	float best_reaction = 1;
	float worst_reaction = 0;
	bool pratice_mode = true;
	int number_try = 1;
	int number_penalties = 0;
public:
	TestReflexe();
	~TestReflexe();

	void MainLoop(sf::RenderWindow &window, bool pratice_mode);
	void StartingGame(sf::RenderWindow &window);
	void Win(sf::RenderWindow &window);
	void GameOver(sf::RenderWindow &window);
	bool WhileInMenu(sf::RenderWindow &window);
	void SpawnRectangle(sf::RenderWindow &window);
};
