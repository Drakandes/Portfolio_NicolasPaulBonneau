#include "stdafx.h"
#include "TalentBeastly.h"

TalentBeastly::TalentBeastly(int current_language)
{
	language = current_language;
	if (language == English_E)
	{
		string_information[0] = "Beastly";
		string_information[1] = "Increase your maximum health by up to 20% (4% per level).";
	}
	else
	{
		string_information[0] = "Bestiale";
		string_information[1] = "Augmente jusqu'à 20% (4% par niveau) votre vie totale.";
	}
}

TalentBeastly::~TalentBeastly()
{
}

float TalentBeastly::GetTalentBonus(int talent_level)
{
	return bonus_initial_value + (talent_level - 1)*bonus_increase;
}

int TalentBeastly::GetNumberStringSkillInformation()
{
	return 2;
}

sf::String TalentBeastly::GetStringSkillInformation(int number_string)
{
	return string_information[number_string];
}
