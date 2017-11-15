#pragma once
#include "GlobalEnum.h"
#include "GlobalFunction.h"
#include "SFML\Graphics.hpp"
#include <vector>
#include <list>
#include <memory>
#include "ListObjectsSingleton.h"
#include "TextBoxGenerator.h"

class ModeSelectionInterface
{
private:
	int language = ListObjectsSingleton::instance()->GetCurrentLanguage();
	const static int number_gamemodes = 4;
	sf::Font font;
	sf::Text interface_name;
	sf::Vector2f position_interface_name{ 800,125 };
	sf::Text text_gamemode[number_gamemodes];
	sf::String string_gamemode[number_gamemodes]{ "Childish","Beginner","Intermediate","Expert" };
	sf::Vector2f position_first_gamemode{ 800,300 };

	void DisplayTextInformation(sf::Vector2f mouse_position, int mode_displaying);
public:
	ModeSelectionInterface();
	~ModeSelectionInterface();

	bool ChooseGameMode(sf::RenderWindow &window);
};

