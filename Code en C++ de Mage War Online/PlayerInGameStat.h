#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GlobalEnum.h"
#include <string>
#include <cstring>
#include "GlobalFunction.h"

class PlayerInGameStat
{
private:
	const static int number_of_text = 8;
	int character_stat_size = 16;
	sf::Texture texture;
	sf::Text text[number_of_text];
	sf::Font font;
	sf::String string[number_of_text];
	sf::Sprite sprite_interface;
	sf::Vector2f position_origin{ 25,598 };
	sf::Vector2f size_texture{ 200,270 };
	sf::Vector2f position_first_text{45 + position_origin.x,16+ position_origin .y};
	sf::Vector2f text_position[number_of_text];
	sf::Vector2f distance_between_text{ 0,34 };

public:
	PlayerInGameStat();
	~PlayerInGameStat();

	void Init(sf::Vector2f position_view_player);
	void Update(sf::Vector2f position_view_player, float player_damage, float player_speed, float player_cooldown, float player_defense, float player_maximum_health, float player_attack_speed, sf::Vector2f window_size, float player_lifesteal, float hp_recovery);
	void DrawToScreen(sf::RenderWindow &window);
};

