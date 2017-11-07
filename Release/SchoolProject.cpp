#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GlobalFunction.h"
#include <vector>
#include "TestCercle.h"
#include <list>
#include "Circle.h"
#include "TestJugement.h"
#include "TestReflexe.h"

#pragma region Variables
sf::Vector2f window_dimension(1300, 700);
std::vector<Circle*> listCircle;
sf::Clock clock_adding_circle;
sf::Clock clock_game;
sf::Color background_color;
sf::Clock clock_background_color;
int background_color_increasing[3];
int background_color_number[3];
int background_color_increasing_color_rate[3] ;
float maixmum_circle = 60;
float starting_circle = 20;
bool starting = true;
int number_of_circle_being_followed = 1;
TestCercle test_cercle;
TestJugement test_jugement;
TestReflexe test_reflexe;
sf::String string[2]{ "Menu","Appuyez sur Escape pour quitter" };
sf::Text text[2];
sf::Font font;
sf::Vector2f position_text_menu[2]{ sf::Vector2f(window_dimension.x / 2, window_dimension.y / 2 - 300) ,sf::Vector2f(window_dimension.x / 2, window_dimension.y / 2 + 200) };
bool pratice_mode = true;
#pragma endregion Variables

#pragma region Calls
void MenuMode();
#pragma endregion Calls

sf::RenderWindow window(sf::VideoMode(1300, 700), "SchoolProject");

int main()
{
	if (!font.loadFromFile("Constantine.ttf"))
	{
		std::cout << "Error with green flame in skillinterface" << std::endl;
	}

	for (int number = 0; number < 2; number++)
	{
		text[number] = GlobalFunction::CreateText(position_text_menu[number], string[number], font, 24);
	}

	window.setPosition(sf::Vector2i(0, 0));
	MenuMode();
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear(background_color);

		for (int number = 0; number < 2; number++)
		{
			window.draw(text[number]);
		}

		if (test_cercle.WhileInMenu(window))
		{
			test_cercle.MainLoop(window,pratice_mode);
		}
		if (test_jugement.WhileInMenu(window))
		{
			test_jugement.MainLoop(window, pratice_mode);
		}
		if (test_reflexe.WhileInMenu(window))
		{
			test_reflexe.MainLoop(window, pratice_mode);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			window.close();
		}
		window.display();
	}

	return 0;
}

void MenuMode()
{
	sf::String string_mode = "Appuyez sur 1 pour le mode pratique.Vos résultas ne seront pas enregistrés!";
	sf::String string_mode_2 = "Appuyez sur 2 pour le mode test. Vos résultats seront enregistrés!";
	sf::Text text_mode;
	sf::Text text_mode2;
	text_mode = GlobalFunction::CreateText(sf::Vector2f(window_dimension.x/2, window_dimension.y / 2 - 75), string_mode, font, 24);
	text_mode2 = GlobalFunction::CreateText(sf::Vector2f(window_dimension.x / 2, window_dimension.y / 2 + 75), string_mode_2, font, 24);
	window.draw(text_mode);
	window.draw(text_mode2);
	window.display();
	bool looping = true;
	while (looping)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
		{
			looping = false;
			pratice_mode = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
		{
			looping = false;
			pratice_mode = false;
		}
	}
}