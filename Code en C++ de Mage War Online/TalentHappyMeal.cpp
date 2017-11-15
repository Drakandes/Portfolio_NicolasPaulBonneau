#include "stdafx.h"
#include "TalentHappyMeal.h"

TalentHappyMeal::TalentHappyMeal(int current_language)
{
	language = current_language;
	if (language == English_E)
	{
		string_information[0] = "Happy Meal";
		string_information[1] = "Increase your lifesteal by up to 12% (2.4% per level).";
	}
	else
	{
		string_information[0] = "Happy Meal";
		string_information[1] = "Augmente jusqu'à 12% (2.4% par niveau) votre vol de vie.";
	}
}

TalentHappyMeal::~TalentHappyMeal()
{
}

float TalentHappyMeal::GetTalentBonus(int talent_level)
{
	return bonus_initial_value + (talent_level - 1)*bonus_increase;
}

int TalentHappyMeal::GetNumberStringSkillInformation()
{
	return 2;
}

sf::String TalentHappyMeal::GetStringSkillInformation(int number_string)
{
	return string_information[number_string];
}