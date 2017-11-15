#include "stdafx.h"
#include "TalentBoosted.h"

TalentBoosted::TalentBoosted(int current_language)
{
	language = current_language;
	if (language == English_E)
	{
		string_information[0] = "Boosted";
		string_information[1] = "Increase your attack speed by up to 35% (7% per level).";
	}
	else
	{
		string_information[0] = "Stimulé";
		string_information[1] = "Augmente jusqu'à 35% (7% par niveau) votre vitesse d'attaque.";
	}
}

TalentBoosted::~TalentBoosted()
{
}

float TalentBoosted::GetTalentBonus(int talent_level)
{
	return bonus_initial_value + (talent_level - 1)*bonus_increase;
}

int TalentBoosted::GetNumberStringSkillInformation()
{
	return 2;
}

sf::String TalentBoosted::GetStringSkillInformation(int number_string)
{
	return string_information[number_string];
}