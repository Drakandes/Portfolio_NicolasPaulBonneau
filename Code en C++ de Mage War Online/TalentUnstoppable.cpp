#include "stdafx.h"
#include "TalentUnstoppable.h"


TalentUnstoppable::TalentUnstoppable(int current_language)
{
	language = current_language;
	if (language == English_E)
	{
		string_information[0] = "Unstoppable";
		string_information[1] = "Decrease slow effect by up to 40% (8% per level).";
	} 
	else
	{
		string_information[0] = "Inarrêtable";
		string_information[1] = "Réduit jusqu'à 40% (8% par niveau) les effets de ralentissement.";
	}
}


TalentUnstoppable::~TalentUnstoppable()
{
}

float TalentUnstoppable::GetTalentBonus(int talent_level)
{
	return bonus_initial_value + (talent_level - 1)*bonus_increase;
}

int TalentUnstoppable::GetNumberStringSkillInformation()
{
	return 2;
}

sf::String TalentUnstoppable::GetStringSkillInformation(int number_string)
{
	return string_information[number_string];
}