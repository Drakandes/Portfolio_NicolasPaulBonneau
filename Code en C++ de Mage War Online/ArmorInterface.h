#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GlobalEnum.h"
#include "GlobalFunction.h"
#include <iostream>
#include <list>
#include "IncludeAllArmors.h"
#include "ListObjectsSingleton.h"
#include "TextBoxGenerator.h"

class ArmorInterface
{
private:
	const static int number_rectangle_information = 6;
	const static int number_of_armors = 33;
	std::vector<std::shared_ptr<A_ArmorBase>> listAllArmors;
	std::vector<int> player_armor_array;
	int language = ListObjectsSingleton::instance()->GetCurrentLanguage();

	std::vector<sf::Texture> ListTextureInterface;

	sf::Texture texture_interface;
	sf::Texture texture_armors;
	sf::Font font;
	sf::Text text_armor_interface_name;
	sf::Text text_player_money;
	sf::Text text_buy_armor[number_of_armors];
	sf::Text text_information_buy_armor;
	sf::Text text_rectangle_information[number_rectangle_information];
	sf::Text text_equip_armor[number_of_armors];
	sf::String string_armor_interface_name = "Armor interface";
	sf::String string_buy_armor = "Buy";
	sf::String string_rectangle_information[number_rectangle_information];
	sf::String string_player_money;
	sf::String string_equip_armor[number_of_armors];
	sf::Vector2f size_armor_interface { 1200,575 };
	sf::Vector2f size_armor_icone{ 50,50 };
	sf::Vector2f size_armor_icone_for_cutting{ 54,54 };
	sf::Vector2f size_buy_armor{ 40,20 };
	sf::Vector2f size_rectangle_information_buy_armor;
	sf::Vector2f size_equip_armor{ 60,20 };
	sf::Sprite rectangle_interface;
	sf::Sprite rectangle_armor_icone[number_of_armors];
	sf::RectangleShape rectangle_buy_armor[number_of_armors];
	sf::RectangleShape rectangle_information_buy_armor;
	sf::RectangleShape rectangle_information;
	sf::Sprite rectangle_current_armor_icone;
	sf::RectangleShape rectangle_equip_armor[number_of_armors];
	sf::Vector2f position_rectangle_buy_armor[number_of_armors];
	sf::Vector2f position_text_buy_armor[number_of_armors];
	sf::Vector2f position_rectangle_interface{ 200,100 };
	sf::Vector2f position_initial_rectangle_armor_icone{ position_rectangle_interface.x + 51,position_rectangle_interface.y + 175 };
	sf::Vector2f position_armor_interface_name{ size_armor_interface.x / 2 + position_rectangle_interface.x, 157 };
	sf::Vector2f position_rectangle_armor_icone[number_of_armors];
	sf::Vector2f position_rectangle_information;
	sf::Vector2f position_current_armor_icone{ 1341,369 };
	sf::Vector2f position_text_player_money{ 1225,165 };
	sf::Vector2f position_rectangle_equip_armor[number_of_armors];
	sf::Vector2f position_text_equip_armor[number_of_armors];
	int character_size_armor_interface_name = 48;
	int character_size_buy_armor = 17;
	int character_size_player_money = 25;
	int number_current_armor;
	sf::Vector2i holder_armor_icone{ 0,0 };
	sf::Vector2i armor_disposition_width_height{ 11,3 };
	bool can_create_rectangle_information_buy_armor = false;
	float player_money;
	sf::Clock clock_between_buying_armors;
public:
	ArmorInterface();
	~ArmorInterface();

	void GenerateTextBox(int armor_displaying, sf::Vector2f mouse_position);
	void InitArmorInterface(std::shared_ptr<Player> player);
	void UpdateArmorInterface(sf::Vector2f mouse_position, sf::Vector2f position_view_player);
	void DrawArmorInterface(sf::RenderWindow &window);
	void GestionRectangleInformation(sf::Vector2f mouse_position, sf::Vector2f position_view_player, int player_level);
	void NewPlayerArmorArray(std::shared_ptr<Player> player);
	void NewPlayerCurrentArmor(std::shared_ptr<Player> player);
	void NewPlayerMoney(std::shared_ptr<Player> player);
	void InteractionArmorInterface(sf::Vector2f mouse_position, sf::Vector2f position_view_player, std::shared_ptr<Player> player);
	void GiveBackPlayerInformation(std::shared_ptr<Player> player);
	void UpdateStyleInterface(int style);
};

