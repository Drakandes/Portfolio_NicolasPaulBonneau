#include "stdafx.h"
#include "TalentEnlightened.h"

TalentEnlightened::TalentEnlightened(int current_language)
{
	language = current_language;
	if (language == English_E)
	{
		string_information[0] = "Enlightened";
		string_information[1] = "Increase your maximum cooldown reduction up to 65% (6% per level). Initially, your maximum cooldown reduction is 35%.";
	}
	else
	{ 
		string_information[0] = "Éclairé";
		string_information[1] = "Augmente jusqu'à 65% (6% par niveau) la limite de votre temps de latence. Initialement, la limite du temps de latence est de 35%.";
	}
}

TalentEnlightened::~TalentEnlightened()
{
}

float TalentEnlightened::GetTalentBonus(int talent_level)
{
	return bonus_initial_value + (talent_level - 1)*bonus_increase;
}

int TalentEnlightened::GetNumberStringSkillInformation()
{
	return 2;
}

sf::String TalentEnlightened::GetStringSkillInformation(int number_string)
{
	return string_information[number_string];
}