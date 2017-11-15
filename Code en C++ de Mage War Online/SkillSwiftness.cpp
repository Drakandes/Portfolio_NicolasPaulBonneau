#include "stdafx.h"
#include "SkillSwiftness.h"

SkillSwiftness::SkillSwiftness(int current_language)
{
	language = current_language;
	if (!texture_icone.loadFromFile("SkillSwiftness.png"))
	{
		std::cout << "Error while loading skill switfness icone texture" << std::endl;
	}
	string_skill_information[0] = "Swiftness (Passive skill)";
	string_skill_information[1] = "Increase the player movement speed out of battle by ";
	string_skill_information[1] = GlobalFunction::InsertNumberToStringIfFloat(string_skill_information[1], passive_value, string_skill_information[1].getSize());
	string_skill_information[1].insert(string_skill_information[1].getSize(), "%.");
}

SkillSwiftness::~SkillSwiftness()
{
}

void SkillSwiftness::GenerateSkillProjectile(sf::Vector2f &position_player, float player_damage, sf::Vector2f mouse_position, std::shared_ptr<Player> player, int player_id, int skill_level_received, int current_rune)
{

}

sf::Texture SkillSwiftness::ReturnSkillIconeTexture()
{
	return texture_icone;
}

float SkillSwiftness::GetSkillCooldown(int skill_level, int class_player)
{
	return 0;
}

int SkillSwiftness::GetNumberStringSkillInformation()
{
	return number_string_skill_information;
}

sf::String SkillSwiftness::GetStringSkillInformation(int number_string)
{
	return string_skill_information[number_string];
}

void SkillSwiftness::ChangeSkillLevel(int skill_level_received, float player_damage, int class_player, int current_rune)
{
	skill_level = skill_level_received;

	if (class_attribution == class_player)
	{
		skill_level++;
	}

	passive_value = 14 + 3 * (skill_level - 1);

	if (current_rune == FirstRune_E)
	{
		passive_value += 5;
	}

	if (language == English_E)
	{
		string_skill_information[0] = "Swiftness (Passive skill)";
		string_skill_information[1] = "Increase the player movement speed when out of battle by 14% (+3% per level).";
	}
	else
	{
		string_skill_information[0] = "Célérité (Sort passif)";
		string_skill_information[1] = "Augemente la vitesse de déplacement du joueur lorsqu'il est hors-combat de 14% (+3% par niveau).";
	}
}

int SkillSwiftness::GetPassiveBonusType()
{
	return passive_type;
}

float SkillSwiftness::GetPassiveBonusValue(int player_level, int class_player, int current_rune)
{
	ChangeSkillLevel(player_level, 0,class_player,current_rune);
	return passive_value;
}

sf::String SkillSwiftness::GetStringRuneBonus(int rune_number)
{
	if (language == English_E)
	{
		switch (rune_number)
		{
		case FirstRune_E:
			return sf::String("Add +5% to the movement speed bonus.");

		case SecondRune_E:
			return sf::String("A third of the bonus is applied when in combat.");

		case ThirdRune_E:
			return sf::String("Also increasing the attack speed by 8%.");
		}
	}
	else
	{
		switch (rune_number)
		{
		case FirstRune_E:
			return sf::String("Ajoute +5% au bonus de vitesse de déplacement.");

		case SecondRune_E:
			return sf::String("Le tier du bonus est appliquée en combat.");

		case ThirdRune_E:
			return sf::String("Augmente aussi la vitesse d'attaque de 8%.");
		}
	}
}
