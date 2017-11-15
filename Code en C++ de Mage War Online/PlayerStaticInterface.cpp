#include "stdafx.h"
#include "PlayerStaticInterface.h"
#include "GlobalFunction.h"

PlayerStaticInterface::PlayerStaticInterface()
{
	if (!font.loadFromFile("Constantine.ttf"))
	{
		std::cout << "Error" << std::endl;
	}
}

PlayerStaticInterface::~PlayerStaticInterface()
{
}

void PlayerStaticInterface::InitAllPlayerStaticInterface(float player_health, int player_level, float player_experience, sf::Vector2f position_view_player)
{
	InitPlayerHealthInterface(player_health);
	InitPlayerExperienceInterface(player_level, player_experience);
	InitPlayerSkillSlots(position_view_player);
}

void PlayerStaticInterface::InitPlayerHealthInterface(float player_health)
{
	string_text_player_health = GlobalFunction::InsertNumberToString(string_text_player_health, player_health, string_text_player_health.getSize());
	text_player_health = GlobalFunction::CreateText(position_text_player_health, string_text_player_health, font, character_size_text_player_health);
	sf::Vector2f text_position = text_player_health.getPosition();
	rect_player_health = GlobalFunction::CreateRectangleWithOrigin(size_rect_player_health, text_position, sf::Color::Red);
}

void PlayerStaticInterface::InitPlayerExperienceInterface(int player_level, float player_experience)
{
	rect_player_experience = GlobalFunction::CreateRectangleWithOrigin(size_rect_player_experience, position_text_player_experience, sf::Color::Green);
	string_text_player_experience = GlobalFunction::InsertNumberToString(string_text_player_experience, player_level, string_text_player_experience.getSize());
	string_text_player_experience.insert(string_text_player_experience.getSize(), ":   ");
	string_text_player_experience = GlobalFunction::InsertNumberToString(string_text_player_experience, player_experience, string_text_player_experience.getSize());
	string_text_player_experience.insert(string_text_player_experience.getSize(), " / ");
	string_text_player_experience = GlobalFunction::InsertNumberToString(string_text_player_experience, GlobalFunction::GetPlayerExperienceNeeded(player_level), string_text_player_experience.getSize());
	text_player_experience = GlobalFunction::CreateText(rect_player_experience.getPosition(), string_text_player_experience, font, rect_player_experience.getSize().y - 2);
}

void PlayerStaticInterface::InitPlayerSkillSlots(sf::Vector2f position_view_player)
{
	rect_skill_slot[2] = GlobalFunction::CreateRectangleWithOrigin(size_rect_skill_slot, position_rect_skill_slot_3, sf::Color::Black);
	rect_skill_slot[1] = GlobalFunction::CreateRectangleWithOrigin(size_rect_skill_slot, position_rect_skill_slot_2, sf::Color::Black);
	rect_skill_slot[3] = GlobalFunction::CreateRectangleWithOrigin(size_rect_skill_slot, position_rect_skill_slot_4, sf::Color::Black);
	rect_skill_slot[0] = GlobalFunction::CreateRectangleWithOrigin(size_rect_skill_slot, position_rect_skill_slot_1, sf::Color::Black);
	rect_skill_slot[4] = GlobalFunction::CreateRectangleWithOrigin(size_rect_skill_slot, position_rect_skill_slot_5, sf::Color::Black);
	rect_skill_slot[5] = GlobalFunction::CreateRectangleWithOrigin(size_rect_skill_slot, position_rect_skill_slot_6, sf::Color::Black);
}

/*void PlayerStaticInterface::InitPayerSkillArray()
{
	array_player_skill_id[skill_slot] = skill_id;
	if (!(array_player_skill_id[skill_holder] == -1))
	{
		texture_player_skill_icone[skill_holder] = skill_manager.listAllSkill[skill_slot]->ReturnSkillIconeTexture();
		array_skill_cooldown[skill_holder] = skill_manager.listAllSkill[skill_slot]->GetSkillCooldown();
		sprite_skill_icone[skill_holder] = GlobalFunction::CreateSprite(array_position_sprite_skill_icone[skill_holder], size_icone, texture_player_skill_icone[skill_holder]);
	}
	skill_cooldown_rectangle[skill_holder] = GlobalFunction::CreateRectangleWithOrigin(size_skill_cooldown_rectangle_max, array_position_skill_cooldown_rectangle[skill_holder], sf::Color::Black);
	skill_cooldown_rectangle[skill_holder].setFillColor(sf::Color::Color(0, 0, 0, 100));

	skill_holder++;
	if (skill_holder == 6)
	{
		skill_holder = 0;
	}
}*/

void PlayerStaticInterface::UpdateAllPlayerStaticInterface(sf::Vector2f position_view_player, float player_health, int player_level, float player_experience)
{
	UpdatePlayerHealthInterface(position_view_player, player_health);
	UpdatePlayerExperienceInterface(position_view_player, player_level, player_experience);
	UpdatePlayerSkillSlots(position_view_player);
	//UpdatePlayerSkillArray(position_view_player);
	//UpdatePlayerSkillCooldownRectangle();
}

void PlayerStaticInterface::UpdatePlayerHealthInterface(sf::Vector2f position_view_player, float player_health)
{
	string_text_player_health = "Hp: ";
	string_text_player_health = GlobalFunction::InsertNumberToString(string_text_player_health, player_health, string_text_player_health.getSize());
	text_player_health = GlobalFunction::CreateText(position_text_player_health, string_text_player_health, font, character_size_text_player_health);
	text_player_health.setPosition(sf::Vector2f(position_text_player_health.x + position_view_player.x, position_text_player_health.y + position_view_player.y));
	rect_player_health.setPosition(sf::Vector2f(position_text_player_health.x + position_view_player.x, position_text_player_health.y + position_view_player.y));
}

void PlayerStaticInterface::UpdatePlayerExperienceInterface(sf::Vector2f position_view_player, int player_level, float player_experience)
{
	string_text_player_experience = "Level ";
	string_text_player_experience = GlobalFunction::InsertNumberToString(string_text_player_experience, player_level, string_text_player_experience.getSize());
	string_text_player_experience.insert(string_text_player_experience.getSize(), ":   ");
	string_text_player_experience = GlobalFunction::InsertNumberToString(string_text_player_experience, player_experience, string_text_player_experience.getSize());
	string_text_player_experience.insert(string_text_player_experience.getSize(), " / ");
	string_text_player_experience = GlobalFunction::InsertNumberToString(string_text_player_experience, GlobalFunction::GetPlayerExperienceNeeded(player_level), string_text_player_experience.getSize());
	text_player_experience = GlobalFunction::CreateText(rect_player_experience.getPosition(), string_text_player_experience, font, rect_player_experience.getSize().y - 2);
	rect_player_experience.setPosition(sf::Vector2f(position_text_player_experience.x + position_view_player.x, position_text_player_experience.y + position_view_player.y));
	text_player_experience.setPosition(sf::Vector2f(rect_player_experience.getPosition()));
}

void PlayerStaticInterface::UpdatePlayerSkillSlots(sf::Vector2f position_view_player)
{
	rect_skill_slot[2].setPosition(sf::Vector2f(position_rect_skill_slot_3.x + position_view_player.x, position_rect_skill_slot_3.y + position_view_player.y));
	rect_skill_slot[1].setPosition(sf::Vector2f(position_rect_skill_slot_2.x + position_view_player.x, position_rect_skill_slot_2.y + position_view_player.y));
	rect_skill_slot[3].setPosition(sf::Vector2f(position_rect_skill_slot_4.x + position_view_player.x, position_rect_skill_slot_4.y + position_view_player.y));
	rect_skill_slot[0].setPosition(sf::Vector2f(position_rect_skill_slot_1.x + position_view_player.x, position_rect_skill_slot_1.y + position_view_player.y));
	rect_skill_slot[4].setPosition(sf::Vector2f(position_rect_skill_slot_5.x + position_view_player.x, position_rect_skill_slot_5.y + position_view_player.y));
	rect_skill_slot[5].setPosition(sf::Vector2f(position_rect_skill_slot_6.x + position_view_player.x, position_rect_skill_slot_6.y + position_view_player.y));
}

/*void PlayerStaticInterface::UpdatePlayerSkillArray(sf::Vector2f position_view_player)
{
	sprite_skill_icone[2].setPosition(sf::Vector2f(position_rect_skill_slot_3.x + position_view_player.x, position_rect_skill_slot_3.y + position_view_player.y));
	sprite_skill_icone[1].setPosition(sf::Vector2f(position_rect_skill_slot_2.x + position_view_player.x, position_rect_skill_slot_2.y + position_view_player.y));
	sprite_skill_icone[3].setPosition(sf::Vector2f(position_rect_skill_slot_4.x + position_view_player.x, position_rect_skill_slot_4.y + position_view_player.y));
	sprite_skill_icone[0].setPosition(sf::Vector2f(position_rect_skill_slot_1.x + position_view_player.x, position_rect_skill_slot_1.y + position_view_player.y));
	sprite_skill_icone[4].setPosition(sf::Vector2f(position_rect_skill_slot_5.x + position_view_player.x, position_rect_skill_slot_5.y + position_view_player.y));
	sprite_skill_icone[5].setPosition(sf::Vector2f(position_rect_skill_slot_6.x + position_view_player.x, position_rect_skill_slot_6.y + position_view_player.y));

	skill_cooldown_rectangle[2].setPosition(sf::Vector2f(array_position_skill_cooldown_rectangle[2].x + position_view_player.x, array_position_skill_cooldown_rectangle[2].y + position_view_player.y));
	skill_cooldown_rectangle[1].setPosition(sf::Vector2f(array_position_skill_cooldown_rectangle[1].x + position_view_player.x, array_position_skill_cooldown_rectangle[1].y + position_view_player.y));
	skill_cooldown_rectangle[3].setPosition(sf::Vector2f(array_position_skill_cooldown_rectangle[3].x + position_view_player.x, array_position_skill_cooldown_rectangle[3].y + position_view_player.y));
	skill_cooldown_rectangle[0].setPosition(sf::Vector2f(array_position_skill_cooldown_rectangle[0].x + position_view_player.x, array_position_skill_cooldown_rectangle[0].y + position_view_player.y));
	skill_cooldown_rectangle[4].setPosition(sf::Vector2f(array_position_skill_cooldown_rectangle[4].x + position_view_player.x, array_position_skill_cooldown_rectangle[4].y + position_view_player.y));
	skill_cooldown_rectangle[5].setPosition(sf::Vector2f(array_position_skill_cooldown_rectangle[5].x + position_view_player.x, array_position_skill_cooldown_rectangle[5].y + position_view_player.y));
}*/

void PlayerStaticInterface::DrawToScreenAllPlayerStaticInterface(sf::RenderWindow &window)
{
	window.draw(rect_player_health);
	window.draw(text_player_health);
	window.draw(rect_player_experience);
	window.draw(text_player_experience);

	for (size_t i = 0; i < 6; i++)
	{
		window.draw(rect_skill_slot[i]);
	}
}

/*void PlayerStaticInterface::UpdatePlayerSkillCooldownRectangle()
{
	for (size_t number = 0; number < 6; number++)
	{
		if (skill_cooldown_rectangle_created[number])
		{
			if (skill_cooldown_clock[number].getElapsedTime().asSeconds() >= array_skill_cooldown[number])
			{
				skill_cooldown_rectangle_created[number] = false;
				skill_cooldown_rectangle[number].setSize(size_skill_cooldown_rectangle_max);
				skill_cooldown_clock[number].restart();
			}

			skill_cooldown_rectangle[number].setSize(sf::Vector2f(size_skill_cooldown_rectangle_max.x, (1 - (skill_cooldown_clock[number].getElapsedTime().asSeconds() / array_skill_cooldown[number])) * size_skill_cooldown_rectangle_max.y));
			std::cout << (1 - (skill_cooldown_clock[number].getElapsedTime().asSeconds() / array_skill_cooldown[number])) * size_skill_cooldown_rectangle_max.y << std::endl;
		}
	}
}*/

/*void PlayerStaticInterface::SkillUsed(int skill_slot)
{
	skill_cooldown_rectangle_created[skill_slot] = true;
	skill_cooldown_clock[skill_slot].restart();
}*/
