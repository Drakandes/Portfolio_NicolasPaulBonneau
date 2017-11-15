#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GlobalEnum.h"
#include "Text.h"
#include <iostream>
#include <list>

class PlayerInformationInterface
{
private:
	sf::Font font;
	sf::RectangleShape player_interface_rectangle;
	sf::Vector2f player_interface_size{ 400, 600 };
	sf::Vector2f player_interface_position{ 900,100 };
	sf::Text player_interface_name_text;
	sf::Text player_interface_health_text;
	int player_interface_name_text_size = 36;
	int player_interface_information_text_size = 24;
public:
	PlayerInformationInterface();
	~PlayerInformationInterface();

	void CreateSkillInterfaceRectangle(int player_health, int player_maximum_health);
	void DrawToScreen(sf::RenderWindow &window, sf::Vector2f position_view_player);
	void UptadePlayerInformations(int player_health, int player_maximum_health);
};
