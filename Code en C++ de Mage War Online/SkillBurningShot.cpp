#include "stdafx.h"
#include "SkillBurningShot.h"

SkillBurningShot::SkillBurningShot(int current_language)
{
	language = current_language;
	if (!texture_.loadFromFile("SkillBurningShot.png"))
	{
		std::cout << "Error while loading skill burning shot texture";
	}

	string_skill_information[0] = "Burning Shot (Passive skill)";
	string_skill_information[1] = "Ignite the target hit for ";
	string_skill_information[1] = GlobalFunction::InsertNumberToStringIfFloat(string_skill_information[1], ignition_duration, string_skill_information[1].getSize());
	string_skill_information[1].insert(string_skill_information[1].getSize(), " seconds, causing it to take ");
	string_skill_information[1] = GlobalFunction::InsertNumberToStringIfFloat(string_skill_information[1], ignition_damage, string_skill_information[1].getSize());
	string_skill_information[1].insert(string_skill_information[1].getSize(), " damage per second.");
}

SkillBurningShot::~SkillBurningShot()
{
}

void SkillBurningShot::GenerateSkillProjectile(sf::Vector2f &position_player, float player_damage, sf::Vector2f mouse_position, std::shared_ptr<Player> player, int player_id, int skill_level_received, int current_rune)
{
}

sf::Texture SkillBurningShot::ReturnSkillIconeTexture()
{
	return texture_;
}

float SkillBurningShot::GetSkillCooldown(int skill_level, int class_player)
{
	return 0;
}

int SkillBurningShot::GetNumberStringSkillInformation()
{
	return number_string_skill_information;
}

sf::String SkillBurningShot::GetStringSkillInformation(int number_string)
{
	return string_skill_information[number_string];
}

void SkillBurningShot::ChangeSkillLevel(int skill_level_received, float player_damage, int class_player, int current_rune)
{
	skill_level = skill_level_received;

	if (class_attribution == class_player)
	{
		skill_level++;
	}

	ignition_damage = 10 + 8 * (skill_level - 1);
	ignition_duration = 3.001 + 0.5 * (skill_level - 1);

	if (current_rune == FirstRune_E)
	{
		ignition_damage += 4 * (skill_level - 1);
	}
	else if (current_rune == SecondRune_E)
	{
		ignition_duration + 1.5;
	}
	else if(current_rune == ThirdRune_E)
	{
		ignition_damage += 20;
	}

	if (language == English_E)
	{
		string_skill_information[0] = "Burning Shot (Passive skill)";
		string_skill_information[1] = "Ignite targets hit by a basic attack for 3 (+0.5 per level) seconds, causing them to burn and take 10 (+8 per level) damage per second.";
	}
	else
	{
		string_skill_information[0] = "Coup Ardent (Sort passif)";
		string_skill_information[1] = "Embrase les cibles touchées par les attaques de base pendant 3 (+0.5 par niveau) secondes, leur causant 10 (+8 par niveau) dégats par seconde.";
	}
}

int SkillBurningShot::GetPassiveBonusType()
{
	return ignition_type;
}

float SkillBurningShot::GetPassiveBonusValue(int player_level, int class_player, int current_rune)
{
	ChangeSkillLevel(player_level, 0, class_player, current_rune);
	return ignition_damage;
}

float SkillBurningShot::GetPassiveBonusDuration(int player_level, int class_player, int current_rune)
{
	ChangeSkillLevel(player_level, 0, class_player, current_rune);
	return ignition_duration;
}

sf::String SkillBurningShot::GetStringRuneBonus(int rune_number)
{
	if (language == English_E)
	{
		switch (rune_number)
		{
		case FirstRune_E:
			return sf::String("Add +4 damage per skill level to the burning effect.");

		case SecondRune_E:
			return sf::String("Increase the duration of the burning effect by 1.5 second.");

		case ThirdRune_E:
			return sf::String("Add +20% to the damage percent of the skill. ");
		}
	}
	else
	{
		switch (rune_number)
		{
		case FirstRune_E:
			return sf::String("Ajoute +4 dégâts par niveau du sort à l'effet d'embrasement.");

		case SecondRune_E:
			return sf::String("Augmente la durée de l'effet d'embrasement de 1.5 seconde.");

		case ThirdRune_E:
			return sf::String("Ajoute +20% au pourcentage de dégâts du sort.");
		}
	}
}