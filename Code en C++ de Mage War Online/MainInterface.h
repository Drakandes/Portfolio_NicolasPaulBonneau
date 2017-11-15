#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GlobalEnum.h"
#include "Text.h"
#include <iostream>
#include <list>
#include <string>
#include <cstring>
#include "ListObjectsSingleton.h"

class MainInterface
{
private:
	sf::Font font;
	sf::Text game_name_text;
	sf::Text play_text;
	sf::Text control_text;
	sf::Text exit_text;

	int language;
	
public:
	MainInterface();
	~MainInterface();

	void Init(int current_language);
	void DrawToScreen(sf::RenderWindow &window);
	sf::String Interaction(sf::RenderWindow &window);
};

