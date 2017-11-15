#include "stdafx.h"
#include "TalentEnraged.h"

TalentEnraged::TalentEnraged(int current_language)
{
	language = current_language;
	if (language == English_E)
	{
		string_information[0] = "Enraged";
		string_information[1] = "Increase your damage by up to 15% (3% per level).";
	}
	else
	{
		string_information[0] = "Enragé";
		string_information[1] = "Augmente jusqu'à 15% (3% par niveau) vos dégâts.";
	}
}

TalentEnraged::~TalentEnraged()
{
}

float TalentEnraged::GetTalentBonus(int talent_level)
{
	return bonus_initial_value + (talent_level - 1)*bonus_increase;
}

int TalentEnraged::GetNumberStringSkillInformation()
{
	return 2;
}

sf::String TalentEnraged::GetStringSkillInformation(int number_string)
{
	return string_information[number_string];
}