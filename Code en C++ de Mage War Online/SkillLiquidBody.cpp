#include "stdafx.h"
#include "SkillLiquidBody.h"

SkillLiquidBody::SkillLiquidBody(int current_language)
{
	language = current_language;
	if (!texture_icone.loadFromFile("SkillLiquidBody.png"))
	{
		std::cout << "Error while loading SkillLiquidBody icone texture" << std::endl;
	}
}

SkillLiquidBody::~SkillLiquidBody()
{
}

void SkillLiquidBody::GenerateSkillProjectile(sf::Vector2f &position_player, float player_damage, sf::Vector2f mouse_position, std::shared_ptr<Player> player, int player_id, int skill_level_received, int current_rune)
{

}

sf::Texture SkillLiquidBody::ReturnSkillIconeTexture()
{
	return texture_icone;
}

float SkillLiquidBody::GetSkillCooldown(int skill_level, int class_player)
{
	return 0;
}

int SkillLiquidBody::GetNumberStringSkillInformation()
{
	return number_string_skill_information;
}

sf::String SkillLiquidBody::GetStringSkillInformation(int number_string)
{
	return string_skill_information[number_string];
}

void SkillLiquidBody::ChangeSkillLevel(int skill_level_received, float player_damage, int class_player, int current_rune)
{
	skill_level = skill_level_received;

	if (class_attribution == class_player)
	{
		skill_level++;
	}

	passive_value = 10 + 2.5 * (skill_level - 1);
	passive_type = 3;

	if (current_rune == FirstRune_E)
	{
		passive_value += 6;
	}
	else if (current_rune == SecondRune_E)
	{
		passive_type = 2;
	}

	if (language == English_E)
	{
		string_skill_information[0] = "Liquid Body (Passive skill)";
		string_skill_information[1] = "You regain 10% (+2.5% per level) of the damage received over 3 seconds.";
	}
	else
	{
		string_skill_information[0] = "Corps Liquide (Sort passif)";
		string_skill_information[1] = "Vous regagnez 10% (+2.5% par niveau) des dégâts reçus sur 3 secondes.";
	}
}

int SkillLiquidBody::GetPassiveBonusType()
{
	return passive_type;
}

float SkillLiquidBody::GetPassiveBonusValue(int player_level, int class_player, int current_rune)
{
	ChangeSkillLevel(player_level, 0, class_player, current_rune);
	return passive_value;
}

sf::String SkillLiquidBody::GetStringRuneBonus(int rune_number)
{
	if (language == English_E)
	{
		switch (rune_number)
		{
		case FirstRune_E:
			return sf::String("Add +6% to the regain bonus.");

		case SecondRune_E:
			return sf::String("It now only takes 2 seconds to recover.");

		case ThirdRune_E:
			return sf::String("Half of the heal is also applied to the shield.");
		}
	}
	else
	{
		switch (rune_number)
		{
		case FirstRune_E:
			return sf::String("Ajoute +6% au bonus de récupération.");

		case SecondRune_E:
			return sf::String("Il faut seulement 2 secondes pour récupérer.");

		case ThirdRune_E:
			return sf::String("La moitié des soins est aussi appliquée sur le bouclier.");
		}
	}
}
