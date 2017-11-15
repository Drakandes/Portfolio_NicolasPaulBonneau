#include "stdafx.h"
#include "SkillAccurateShot.h"

SkillAccurateShot::SkillAccurateShot(int current_language)
{
	language = current_language;
	if (!texture_.loadFromFile("SkillAccurateShot_icone.png"))
	{
		std::cout << "Error while loading skill accurate shot texture";
	}

	string_skill_information[0] = "Accurate Shot (Passive skill)";
	string_skill_information[1] = "Add ";
	string_skill_information[1] = GlobalFunction::InsertNumberToStringIfFloat(string_skill_information[0], damage_bonus_percent, string_skill_information[0].getSize());
	string_skill_information[1].insert(string_skill_information[0].getSize(), "% damage for every consecutive basic attack on the same target.");
}

SkillAccurateShot::~SkillAccurateShot()
{
}

void SkillAccurateShot::GenerateSkillProjectile(sf::Vector2f &position_player, float player_damage, sf::Vector2f mouse_position, std::shared_ptr<Player> player, int player_id, int skill_level_received, int current_rune)
{

}

sf::Texture SkillAccurateShot::ReturnSkillIconeTexture()
{
	return texture_;
}

float SkillAccurateShot::GetSkillCooldown(int skill_level, int class_player)
{
	return 0;
}

int SkillAccurateShot::GetNumberStringSkillInformation()
{
	return number_string_skill_information;
}

sf::String SkillAccurateShot::GetStringSkillInformation(int number_string)
{
	return string_skill_information[number_string];
}

void SkillAccurateShot::ChangeSkillLevel(int skill_level_received, float player_damage, int class_player, int current_rune)
{
	skill_level = skill_level_received;

	if (class_attribution == class_player)
	{
		skill_level++;
	}

	damage_bonus_percent = 2 + 0.5 * (skill_level - 1);

	if (current_rune == FirstRune_E)
	{
		damage_bonus_percent += 1.2;
	}
	else if (current_rune == SecondRune_E)
	{
		damage_bonus_percent += 0.3 * (skill_level - 1);
	}
	else if (current_rune == ThirdRune_E)
	{
		damage_bonus_percent += damage_bonus_percent*0.5;
	}

	if (language == English_E)
	{
		string_skill_information[0] = "Accurate Shot (Passive skill)";
		string_skill_information[1] = "Add 2% (+0.5% per level) damage to basic attack for every consecutive basic attack on the same target.";
	}
	else
	{
		string_skill_information[0] = "Tir précis (Sort passif)";
		string_skill_information[1] = "Ajoute 2% (+0.5% par niveau) de dégâts aux attaques de base pour chaque attaque de base consécutive sur la même cible.";
	}
}

float SkillAccurateShot::GetPassiveBonusValue(int player_level, int class_player, int current_rune)
{
	ChangeSkillLevel(player_level,0, class_player, current_rune);
	return damage_bonus_percent;
}

sf::String SkillAccurateShot::GetStringRuneBonus(int rune_number)
{
	if (language == English_E)
	{
		switch (rune_number)
		{
		case FirstRune_E:
			return sf::String("Add +1.2% to the damage bonus with each hit. ");

		case SecondRune_E:
			return sf::String("Add +0.3% per skill level to the damage bonus with each hit.");

		case ThirdRune_E:
			return sf::String("Increase the overall bonus damage by 50%.");
		}
	}
	else
	{
		switch (rune_number)
		{
		case FirstRune_E:
			return sf::String("Ajoute +1.2% au bonus de dégâts à chaque coup.");

		case SecondRune_E:
			return sf::String("Add +0.3% par niveau au bonus de dégâts à chaque coup.");

		case ThirdRune_E:
			return sf::String("Augmente le bonus total de dégâts de 50%.");
		}
	}
}
