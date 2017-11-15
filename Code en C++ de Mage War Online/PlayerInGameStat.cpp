#include "stdafx.h"
#include "PlayerInGameStat.h"

PlayerInGameStat::PlayerInGameStat()
{
	if (texture.loadFromFile("StatInGame_icone.png"))
	{
		std::cout << "Error couldnt load from file in game stat icone" << std::endl;
	}

	if (!font.loadFromFile("Constantine.ttf"))
	{
		std::cout << "Error font in game stat" << std::endl;
	}
}

PlayerInGameStat::~PlayerInGameStat()
{
}

void PlayerInGameStat::Init(sf::Vector2f position_view_player)
{
	sprite_interface = GlobalFunction::CreateSpriteWithoutOrigin(position_origin, size_texture, texture);
	for (int number = 0; number < number_of_text; number++)
	{
		string[number] = "0";
		text_position[number] = sf::Vector2f(position_first_text.x, position_first_text.y + distance_between_text.y*number);
		text[number] = GlobalFunction::CreateTextWithNoOrigin(text_position[number], string[number], font, character_stat_size);
		text[number].setOrigin(0, text[number].getGlobalBounds().height);
    }
}

void PlayerInGameStat::Update(sf::Vector2f position_view_player, float player_damage, float player_speed, float player_cooldown, float player_defense, float player_maximum_health, float player_attack_speed, sf::Vector2f window_size, float player_lifesteal, float hp_recovery)
{
	position_origin.y = window_size.y - 296;
	position_first_text.y = 16 + position_origin.y;
	for (int number = 0; number < number_of_text; number++)
	{
		text_position[number] = sf::Vector2f(position_first_text.x, position_first_text.y + distance_between_text.y*number);
	}

	sprite_interface.setPosition(position_origin + position_view_player);

	string[0].clear();
	string[0] = GlobalFunction::InsertNumberToString(string[0], std::round(player_damage), string[0].getSize());
	text[0].setString(string[0]);
	text[0].setPosition(text_position[0] + position_view_player);

	string[1].clear();
	string[1] = GlobalFunction::InsertNumberToString(string[1], std::round(player_defense), string[1].getSize());
	string[1].insert(string[1].getSize(), " (");
	string[1] = GlobalFunction::InsertNumberToString(string[1], 100 - std::round(GlobalFunction::GetArmorReductionModifier(player_defense)*100), string[1].getSize());
	string[1].insert(string[1].getSize(), "%)");
	text[1].setString(string[1]);
	text[1].setPosition(text_position[1] + position_view_player);

	string[2].clear();
	string[2] = GlobalFunction::InsertNumberToString(string[2], std::round(player_speed), string[2].getSize());
	text[2].setString(string[2]);
	text[2].setPosition(text_position[2] + position_view_player);

	string[3].clear();
	string[3] = GlobalFunction::InsertNumberToString(string[3], std::round(player_maximum_health), string[3].getSize());
	text[3].setString(string[3]);
	text[3].setPosition(text_position[3] + position_view_player);

	string[4].clear();
	string[4] = GlobalFunction::InsertNumberToStringIfFloat(string[4], player_attack_speed, string[4].getSize());
	text[4].setString(string[4]);
	text[4].setPosition(text_position[4] + position_view_player);

	string[5].clear();
	string[5] = GlobalFunction::InsertNumberToStringIfFloat(string[5], player_cooldown, string[5].getSize());
	string[5].insert(string[5].getSize(), "%");
	text[5].setString(string[5]);
	text[5].setPosition(text_position[5] + position_view_player);

	string[6].clear();
	string[6] = GlobalFunction::InsertNumberToStringIfFloat(string[6], player_lifesteal, string[6].getSize());
	string[6].insert(string[6].getSize(), "%");
	text[6].setString(string[6]);
	text[6].setPosition(text_position[6] + position_view_player);

	string[7].clear();
	string[7] = GlobalFunction::InsertNumberToStringIfFloat(string[7], hp_recovery, string[7].getSize());
	text[7].setString(string[7]);
	text[7].setPosition(text_position[7] + position_view_player);
}

void PlayerInGameStat::DrawToScreen(sf::RenderWindow &window)
{
	window.draw(sprite_interface);
	for (int number = 0; number < number_of_text; number++)
	{
		window.draw(text[number]);
	}
}
