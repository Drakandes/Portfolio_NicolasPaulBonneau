#include "stdafx.h"
#include "SkillRevive.h"

SkillRevive::SkillRevive(int current_language)
{
	language = current_language;
	if (!texture_icone.loadFromFile("SkillRevive.png"))
	{
		std::cout << "Error while loading SkillRevive icone texture" << std::endl;
	}
}

SkillRevive::~SkillRevive()
{
}

void SkillRevive::GenerateSkillProjectile(sf::Vector2f &position_player, float player_damage, sf::Vector2f mouse_position, std::shared_ptr<Player> player, int player_id, int skill_level_received, int current_rune)
{

}

sf::Texture SkillRevive::ReturnSkillIconeTexture()
{
	return texture_icone;
}

float SkillRevive::GetSkillCooldown(int skill_level, int class_player)
{
	return 0;
}

int SkillRevive::GetNumberStringSkillInformation()
{
	return number_string_skill_information;
}

sf::String SkillRevive::GetStringSkillInformation(int number_string)
{
	return string_skill_information[number_string];
}

void SkillRevive::ChangeSkillLevel(int skill_level_received, float player_damage, int class_player, int current_rune)
{
	skill_level = skill_level_received;

	if (class_attribution == class_player)
	{
		skill_level++;
	}

	cooldown_revive = 300 - 20 * (skill_level - 1);
	percent_shield = 45 + 5 * (skill_level - 1);

	if (current_rune == ThirdRune_E)
	{
		cooldown_revive -= 60;
	}

	if (cooldown_revive < 60)
	{
		cooldown_revive = 60;
	}

	if (language == English_E)
	{
		string_skill_information[0] = "Revive (passive skill)";
		string_skill_information[1] = "Each 300 (-20 per level) seconds, upon death, the player is revived with 45% (+5% per level) of his maximum health in shield. The shield capacity is also increased by +25%.";
	}
	else
	{
		string_skill_information[0] = "Réanimation (sort passif)";
		string_skill_information[1] = "À chaque 300 (-20 par niveau) secondes, à sa mort, le joueur est réssucité avec 45% (+5% par niveau) de sa vie totale en bouclier. La capacité du bouclier est aussi augmentée de +25%.";
	}
}

void SkillRevive::DrawSkillHitBox(sf::Vector2f mouse_position, int skill_level, sf::Vector2f position_caster, int class_player, float range_modifier, int current_rune)
{
}

sf::String SkillRevive::GetStringRuneBonus(int rune_number)
{
	if (language == English_E)
	{
		switch (rune_number)
		{
		case FirstRune_E:
			return sf::String("Upon death, also heals the player for 50% of his maximum health.");

		case SecondRune_E:
			return sf::String("Increase the shield capacity increase to +40%.");

		case ThirdRune_E:
			return sf::String("Reduce the cooldown of revive by 60 seconds. Revive can't go below 60 seconds.");
		}
	}
	else
	{
		switch (rune_number)
		{
		case FirstRune_E:
			return sf::String("À sa mort, soigne aussi le joueur de 50% de sa vie totale.");

		case SecondRune_E:
			return sf::String("Augmente l'augmentation de la capacité du bouclier à +40%.");

		case ThirdRune_E:
			return sf::String("Réduit le temps de latence de réanimation de 60 secondes. Réanimation ne peut descendre en-dessous de 60 secondes.");
		}
	}
}

int SkillRevive::GetPassiveBonusType()
{
	return 0;
}

float SkillRevive::GetPassiveBonusValue(int player_level, int class_player, int current_rune)
{
	ChangeSkillLevel(player_level, 0, class_player, current_rune);
	return percent_shield;
}

float SkillRevive::GetPassiveBonusDuration(int player_level, int class_player, int current_rune)
{
	ChangeSkillLevel(player_level, 0, class_player, current_rune);
	return cooldown_revive;
}
