#include "stdafx.h"
#include "TalentNaturalBornKiller.h"


TalentNaturalBornKiller::TalentNaturalBornKiller(int current_language)
{
	language = current_language;
	if (language == English_E)
	{
		string_information[0] = "Natural Born Killer";
		string_information[1] = "Increase your base attack speed by up to 0.21 (0.07 per level). Initially, your base attack speed is 0.6.";
	}
	else
	{
		string_information[0] = "Tueur Né";
		string_information[1] = "Augmente jusqu'à 0.21 (0.07 par niveau) votre vitesse d'attaque de base. Initialement, votre vitesse d'attaque de base est de 0.6.";
	}
}


TalentNaturalBornKiller::~TalentNaturalBornKiller()
{
}

float TalentNaturalBornKiller::GetTalentBonus(int talent_level)
{
	return bonus_initial_value + (talent_level - 1)*bonus_increase;
}

int TalentNaturalBornKiller::GetNumberStringSkillInformation()
{
	return 2;
}

sf::String TalentNaturalBornKiller::GetStringSkillInformation(int number_string)
{
	return string_information[number_string];
}