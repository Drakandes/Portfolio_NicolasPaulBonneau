#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GlobalEnum.h"
#include "Text.h"
#include <iostream>
#include <list>
#include "GlobalFunction.h"
#include "IncludaAllGems.h"
#include "TextBoxGenerator.h"

class GemInterface
{
private:
	int language;
	std::vector<std::shared_ptr<G_GemBase>> ListAllGems;
	std::vector<int> ListAllAtiveGems;
	const static int number_of_gems = 8;
	const static int number_max_gem_tiers = 5;
	const static int number_max_rectangle_information = 1 + number_max_gem_tiers;
	const static int number_max_gem_in_bag = 200;

	std::vector<sf::Texture> ListTextureInterface;

	std::vector<sf::Vector2f> player_gem_array;
	float player_money;

	sf::Texture texture_all_gems;
	sf::Texture texture_interface;

	sf::Font font;
	sf::String string_gem_interface_name;
	sf::String string_rectangle_information[number_max_rectangle_information];
	sf::String string_buy_gem;
	sf::String sintrg_buy_gem_of_tier[number_max_gem_tiers]{ "1","2","3","4","5" };
	sf::String string_player_money;
	sf::String string_number_gems_using; 
	sf::Text text_number_gems_using;
	sf::Text text_gem_interface_name;
	sf::Text text_buy_gem[number_of_gems];
	sf::Text text_rectangle_information[number_max_rectangle_information];
	sf::Text text_buy_gem_of_tier[number_of_gems][number_max_gem_tiers];
	sf::Text text_player_money;
	sf::Vector2f size_gem_sprite_icone{ 50,50 };
	sf::Vector2f size_gem_sprite_icone_for_cutting{54, 54};
	sf::Vector2f size_gem_interface{ 1325,750 };
	sf::Vector2f size_buy_gem{ 40,20 };
	sf::Vector2f size_buy_gem_of_tier{ 20,20 };
	sf::Sprite rectangle_gem_icone[number_of_gems];
	sf::Sprite rectangle_gem_interface;
	sf::RectangleShape rectangle_information;
	sf::RectangleShape rectangle_buy_gem[number_of_gems];
	sf::RectangleShape rectangle_buy_gem_of_tier[number_of_gems][number_max_gem_tiers];
	sf::Sprite rectangle_player_gem_icone[number_max_gem_in_bag];
	sf::Vector2f position_gem_sprite_icone[number_of_gems];
	sf::Vector2f position_initial_gem_sprite_icone{ 250,150 };
	sf::Vector2f position_gem_interface{ 175,15 };
	sf::Vector2f position_gem_interface_name{ 804,70 };
	sf::Vector2f position_rectangle_information;
	sf::Vector2f position_rectangle_buy_gem[number_of_gems];
	sf::Vector2f position_text_buy_gem[number_of_gems];
	sf::Vector2f position_initial_rectangle_buy_gem_of_tier[number_of_gems];
	sf::Vector2f position_rectangle_buy_gem_of_tier[number_of_gems][number_max_gem_tiers];
	sf::Vector2f position_text_player_money{ 1300,100 };
	sf::Vector2f position_initial_player_gem_icone{ 450,175 };
	sf::Vector2f position_player_gem_icone[number_max_gem_in_bag];
	sf::Vector2f position_text_number_gems_using{ 435,700 };
	int character_size_gem_interface_name = 48;
	int character_size_buy_gem = 16;
	int character_size_buy_gem_of_tier = 12;
	int character_size_player_money = 26;
	sf::Vector2i holder_gem_sprite_icone_width;
	sf::Vector2f holder_buy_gem_of_tier[number_of_gems];
	sf::Vector2f holder_player_gem_icone;
	int max_player_gem_icone_width = 20;
	int max_gem_sprite_icone_width = 2;
	int max_buy_gem_of_tier_width = 2;
	int distance_between_player_gem_icone = 2;
	bool can_create_rectangle_information;
	bool can_draw_buy_gem_of_tier[number_of_gems]{ false,false,false,false,false,false,false,false};
	sf::Clock clock_between_buying_gem;

public:
	GemInterface();
	~GemInterface();

	void InitGemInterface(int current_language);
	void UpdateGemInterfacePosition(sf::Vector2f position_view_player, std::shared_ptr<Player> player);
	void DrawGemInterface(sf::RenderWindow &window);
	void GestionRectangleInformation(sf::Vector2f mouse_position, sf::Vector2f position_view_player);
	void InteractionGemInterface(sf::Vector2f mouse_position, sf::Vector2f position_view_player, std::shared_ptr<Player> player);
	void NewPlayerMoney(std::shared_ptr<Player> player);
	void NewPlayerGemArray(std::shared_ptr<Player> player);
	void GiveBackPlayerInformation(std::shared_ptr<Player> player);
	void UpdateStyleInterface(int style);
};

