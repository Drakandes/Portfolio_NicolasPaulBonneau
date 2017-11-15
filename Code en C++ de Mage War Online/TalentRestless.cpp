#include "stdafx.h"
#include "TalentRestless.h"


TalentRestless::TalentRestless(int current_language)
{
	language = current_language;
	if (language == English_E)
	{
		string_information[0] = "Restless";
		string_information[1] = "Decrease your cooldown by up to 2 seconds (0.4 second per level). Cooldown cannot be reduce under 0.5 second.";
	}
	else
	{
		string_information[0] = "Inépuisable";
		string_information[1] = "Réduit jusqu'à 2 secondes (0.4 seconde par niveau) les temps d'attente pour utiliser vos sorts. Le temps ne peut être réduit en-dessous de 0.5 seconde.";
	}
}


TalentRestless::~TalentRestless()
{
}

float TalentRestless::GetTalentBonus(int talent_level)
{
	return bonus_initial_value + (talent_level - 1)*bonus_increase;
}

int TalentRestless::GetNumberStringSkillInformation()
{
	return 2;
}

sf::String TalentRestless::GetStringSkillInformation(int number_string)
{
	return string_information[number_string];
}