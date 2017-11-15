#include "stdafx.h"
#include "PlayerInformationInterface.h"
#include "GlobalFunction.h"

PlayerInformationInterface::PlayerInformationInterface()
{
	if (!font.loadFromFile("Constantine.ttf"))
	{
		std::cout << "Error" << std::endl;
	}
}

PlayerInformationInterface::~PlayerInformationInterface()
{
}

void PlayerInformationInterface::CreateSkillInterfaceRectangle(int player_health, int player_maximum_health)
{
	player_interface_rectangle = GlobalFunction::CreateRectangle(player_interface_size, player_interface_position);
	sf::Vector2f text_position{ 0,0 };
	player_interface_name_text = GlobalFunction::CreateText(text_position, "Player Overview", font, player_interface_name_text_size);
	sf::String player_health_string = "Hp: ";
	player_health_string = GlobalFunction::InsertNumberToString(player_health_string, player_health, player_health_string.getSize());
	player_health_string.insert(player_health_string.getSize(), "/");
	player_health_string = GlobalFunction::InsertNumberToString(player_health_string, player_maximum_health, player_health_string.getSize());
	player_interface_health_text = GlobalFunction::CreateText(text_position, player_health_string, font, player_interface_information_text_size);
}

void PlayerInformationInterface::UptadePlayerInformations(int player_health, int player_maximum_health)
{
	sf::String player_health_string = "Hp: ";
	player_health_string = GlobalFunction::InsertNumberToString(player_health_string, player_health, player_health_string.getSize());
	player_health_string.insert(player_health_string.getSize(), "/");
	player_health_string = GlobalFunction::InsertNumberToString(player_health_string, player_maximum_health, player_health_string.getSize());
	player_interface_health_text.setString(player_health_string);
}

void PlayerInformationInterface::DrawToScreen(sf::RenderWindow &window, sf::Vector2f position_view_player)
{
	player_interface_rectangle.setPosition(player_interface_position.x + position_view_player.x, player_interface_position.y + position_view_player.y);
	player_interface_name_text.setPosition(player_interface_rectangle.getPosition().x + player_interface_rectangle.getSize().x / 2, player_interface_rectangle.getPosition().y + player_interface_name_text.getGlobalBounds().height * 2);
	player_interface_health_text.setPosition(player_interface_rectangle.getPosition().x + 20 + player_interface_health_text.getGlobalBounds().width/2, player_interface_rectangle.getPosition().y + 100);
	window.draw(player_interface_rectangle);
	window.draw(player_interface_name_text);
	window.draw(player_interface_health_text);
}

