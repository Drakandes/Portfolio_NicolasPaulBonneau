#include "stdafx.h"
#include "SkillReinforcement.h"

SkillReinforcement::SkillReinforcement(int current_language)
{
	language = current_language;
	if (!texture_icone.loadFromFile("SkillReinforcement.png"))
	{
		std::cout << "Error while loading SkillReinforcement icone texture" << std::endl;
	}
}

SkillReinforcement::~SkillReinforcement()
{
}

void SkillReinforcement::GenerateSkillProjectile(sf::Vector2f &position_player, float player_damage, sf::Vector2f mouse_position, std::shared_ptr<Player> player, int player_id, int skill_level_received, int current_rune)
{
	
}

sf::Texture SkillReinforcement::ReturnSkillIconeTexture()
{
	return texture_icone;
}

float SkillReinforcement::GetSkillCooldown(int skill_level, int class_player)
{
	return 0;
}

int SkillReinforcement::GetNumberStringSkillInformation()
{
	return number_string_skill_information;
}

sf::String SkillReinforcement::GetStringSkillInformation(int number_string)
{
	return string_skill_information[number_string];
}

void SkillReinforcement::ChangeSkillLevel(int skill_level_received, float player_damage, int class_player, int current_rune)
{
	skill_level = skill_level_received;

	if (class_attribution == class_player)
	{
		skill_level++;
	}

	percent_shield = 2 + 1 * (skill_level - 1);

	if (language == English_E)
	{
		string_skill_information[0] = "Reinforcement (passive skill)";
		string_skill_information[1] = "Everytime a basic attack hits a target, the player is shielded equal to 2% (+1% per level) of his maximum health.";
	}
	else
	{
		string_skill_information[0] = "Renforcement (sort passif)";
		string_skill_information[1] = "À chaque fois qu'une attaque de base touche une cible, le joueur reçoit du bouclier égal à 2% (+1% par niveau) de sa vie totale.";
	}
}

void SkillReinforcement::DrawSkillHitBox(sf::Vector2f mouse_position, int skill_level, sf::Vector2f position_caster, int class_player, float range_modifier, int current_rune)
{
}

sf::String SkillReinforcement::GetStringRuneBonus(int rune_number)
{
	if (language == English_E)
	{
		switch (rune_number)
		{
		case FirstRune_E:
			return sf::String("Also increase the player's shield capacity by +25%.");

		case SecondRune_E:
			return sf::String("15% of your armor apply on shield.");

		case ThirdRune_E:
			return sf::String("Also give +2 (+1 per skill level) armor on hit for 3 seconds.");
		}
	}
	else
	{
		switch (rune_number)
		{
		case FirstRune_E:
			return sf::String("Augmente aussi la capacité de bouclier du joueur de +25%.");

		case SecondRune_E:
			return sf::String("15% de votre armure s'applique aussi aux boucliers.");

		case ThirdRune_E:
			return sf::String("Donne aussi +2 (+1 par niveau de sort) d'armure à chaque touchée pendant 3 secondes.");
		}
	}
}

int SkillReinforcement::GetPassiveBonusType()
{
	return 0;
}

float SkillReinforcement::GetPassiveBonusValue(int player_level, int class_player, int current_rune)
{
	ChangeSkillLevel(player_level, 0, class_player, current_rune);
	return percent_shield;
}

float SkillReinforcement::GetPassiveBonusDuration(int player_level, int class_player, int current_rune)
{
	return 0;
}