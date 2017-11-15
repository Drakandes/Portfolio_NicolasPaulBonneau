#include "stdafx.h"
#include "TalentHardyMan.h"

TalentHardyMan::TalentHardyMan(int current_language)
{
	language = current_language;
	if (language == English_E)
	{
		string_information[0] = "Hardy Man";
		string_information[1] = "Reduce the time you are stunned by up to 0.5 seconds (0.1 second per level). Stun time cannot be reduce under 0.3 second.";
	}
	else
	{
		string_information[0] = "Homme Robuste";
		string_information[1] = "Réduit jusqu'à 0.5 seconde (0.1 seconde par niveau) le temps des effets d'étourdissements. Le temps ne peut être réduit en-dessous de 0.3 seconde.";
	}
}

TalentHardyMan::~TalentHardyMan()
{
}

float TalentHardyMan::GetTalentBonus(int talent_level)
{
	return bonus_initial_value + (talent_level - 1)*bonus_increase;
}

int TalentHardyMan::GetNumberStringSkillInformation()
{
	return 2;
}

sf::String TalentHardyMan::GetStringSkillInformation(int number_string)
{
	return string_information[number_string];
}