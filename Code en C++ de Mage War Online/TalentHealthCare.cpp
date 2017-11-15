#include "stdafx.h"
#include "TalentHealthCare.h"

TalentHealthCare::TalentHealthCare(int current_language)
{
	language = current_language;
	if (language == English_E)
	{
		string_information[0] = "Health Care";
		string_information[1] = "Increase your recovery by up to 20% (4% per level).";
	}
	else
	{
		string_information[0] = "Soins de Sant�";
		string_information[1] = "Augmente jusqu'� 20% (4% par niveau) tous les soins re�us.";
	}
}

TalentHealthCare::~TalentHealthCare()
{
}

float TalentHealthCare::GetTalentBonus(int talent_level)
{
	return bonus_initial_value + (talent_level - 1)*bonus_increase;
}

int TalentHealthCare::GetNumberStringSkillInformation()
{
	return 2;
}

sf::String TalentHealthCare::GetStringSkillInformation(int number_string)
{
	return string_information[number_string];
}