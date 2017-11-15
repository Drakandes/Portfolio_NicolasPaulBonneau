#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GlobalEnum.h"
#include <string>
#include <cstring>
#include <iostream>
#include "SkillManagement.h"

class SkillManagement;

class PlayerStaticInterface
{
private:
	sf::Text text_player_health;
	sf::Text text_player_experience;
	sf::Font font;

	sf::Vector2f size_rect_player_experience{ 500, 20 };
	sf::Vector2f size_rect_player_health{ 125,28 };
	sf::Vector2f size_rect_skill_slot{ 50,50 };
	sf::Vector2f position_text_player_health{ 75,40 };
	sf::Vector2f position_text_player_experience{ 800, 800 - (size_rect_player_experience.y) };
	sf::Vector2f position_rect_skill_slot_3{800 - size_rect_skill_slot.x, position_text_player_experience.y - size_rect_skill_slot.y*2};
	sf::Vector2f position_rect_skill_slot_2{ position_rect_skill_slot_3.x - size_rect_skill_slot.x * 2, position_rect_skill_slot_3.y };
	sf::Vector2f position_rect_skill_slot_4{ position_rect_skill_slot_3.x + size_rect_skill_slot.x * 2, position_rect_skill_slot_3.y };
	sf::Vector2f position_rect_skill_slot_1{ position_rect_skill_slot_2.x - size_rect_skill_slot.x * 2, position_rect_skill_slot_3.y };
	sf::Vector2f position_rect_skill_slot_5{ position_rect_skill_slot_4.x + size_rect_skill_slot.x * 2, position_rect_skill_slot_3.y };
	sf::Vector2f position_rect_skill_slot_6{ position_rect_skill_slot_5.x + size_rect_skill_slot.x * 2, position_rect_skill_slot_3.y };
	int character_size_text_player_health = 24;
	sf::String string_text_player_health = "Hp: ";
	sf::String string_text_player_experience = "Level ";
	sf::RectangleShape rect_player_health;
	sf::RectangleShape rect_player_experience;
	sf::RectangleShape rect_skill_slot[6];
	sf::Texture texture_player_skill_icone[6];
	int array_player_skill_id[6];
	float array_skill_cooldown[6];
	sf::Sprite sprite_skill_icone[6];
	sf::Vector2f array_position_sprite_skill_icone[6]{ position_rect_skill_slot_1, position_rect_skill_slot_2, position_rect_skill_slot_3, position_rect_skill_slot_4, position_rect_skill_slot_5, position_rect_skill_slot_6 };
	sf::Vector2f size_icone{ 50,50 };
	sf::Vector2f size_skill_cooldown_rectangle_max{ 50,50 };
	int skill_holder = 0;
	bool skill_cooldown_rectangle_created[6]{ false, false, false, false, false, false };
	sf::Vector2f array_position_skill_cooldown_rectangle[6]{ sf::Vector2f(position_rect_skill_slot_1.x ,position_rect_skill_slot_1.y),sf::Vector2f(position_rect_skill_slot_2.x ,position_rect_skill_slot_2.y), sf::Vector2f(position_rect_skill_slot_3.x,position_rect_skill_slot_3.y - size_skill_cooldown_rectangle_max.y), sf::Vector2f(position_rect_skill_slot_4.x,position_rect_skill_slot_4.y - size_skill_cooldown_rectangle_max.y), sf::Vector2f(position_rect_skill_slot_5.x ,position_rect_skill_slot_5.y- size_skill_cooldown_rectangle_max.y), sf::Vector2f(position_rect_skill_slot_6.x,position_rect_skill_slot_6.y - size_skill_cooldown_rectangle_max.y)};
	sf::RectangleShape skill_cooldown_rectangle[6];
	sf::Clock skill_cooldown_clock[6];
public:
	PlayerStaticInterface();
	~PlayerStaticInterface();

	void InitAllPlayerStaticInterface(float player_health, int player_level, float player_experience, sf::Vector2f position_view_player);
	void InitPlayerHealthInterface(float player_health);
	void InitPlayerSkillSlots(sf::Vector2f position_view_player);
	void DrawToScreenAllPlayerStaticInterface(sf::RenderWindow &window);
	void UpdateAllPlayerStaticInterface(sf::Vector2f position_view_player, float player_health, int player_level, float player_experience);
	void UpdatePlayerHealthInterface(sf::Vector2f position_view_player, float player_health);
	void InitPlayerExperienceInterface(int player_level, float player_experience);
	void UpdatePlayerExperienceInterface(sf::Vector2f position_view_player, int player_level, float player_experience);
	void UpdatePlayerSkillSlots(sf::Vector2f position_view_player);
};

