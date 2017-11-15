#include "stdafx.h"
#include "TalentSwifty.h"


TalentSwifty::TalentSwifty(int current_language)
{
	language = current_language;
	if (language == English_E)
	{
		string_information[0] = "Swifty";
		string_information[1] = "Increase your movement speed by up to 10% (2% per level).";
	}
	else
	{
		string_information[0] = "Rapide";
		string_information[1] = "Augmente jusqu'à 10% (2% par niveau) votre vitesse de déplacement.";
	}
}


TalentSwifty::~TalentSwifty()
{
}

float TalentSwifty::GetTalentBonus(int talent_level)
{
	return bonus_initial_value + (talent_level - 1)*bonus_increase;
}

int TalentSwifty::GetNumberStringSkillInformation()
{
	return 2;
}

sf::String TalentSwifty::GetStringSkillInformation(int number_string)
{
	return string_information[number_string];
}