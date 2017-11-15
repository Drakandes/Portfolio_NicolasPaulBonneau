#include "stdafx.h"
#include "TalentStoneMan.h"


TalentStoneMan::TalentStoneMan(int current_language)
{
	language = current_language;
	if (language == English_E)
	{
		string_information[0] = "Stone Man";
		string_information[1] = "Increase your armor by up to 15% (3% per level).";
	}
	else
	{
		string_information[0] = "Homme de Pierre";
		string_information[1] = "Augmente jusqu'à 15% (3% par niveau) votre armure.";
	}
}


TalentStoneMan::~TalentStoneMan()
{
}

float TalentStoneMan::GetTalentBonus(int talent_level)
{
	return bonus_initial_value + (talent_level - 1)*bonus_increase;
}

int TalentStoneMan::GetNumberStringSkillInformation()
{
	return 2;
}

sf::String TalentStoneMan::GetStringSkillInformation(int number_string)
{
	return string_information[number_string];
}