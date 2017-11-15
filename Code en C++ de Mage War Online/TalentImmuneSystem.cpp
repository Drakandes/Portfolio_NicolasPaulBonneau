#include "stdafx.h"
#include "TalentImmuneSystem.h"


TalentImmuneSystem::TalentImmuneSystem(int current_language)
{
	language = current_language;
	if (language == English_E)
	{
		string_information[0] = "Immune System";
		string_information[1] = "Increase your recovery by up to 1.5% (0.3% per level) of your maximum health. At maximum level, you regenerate 100% of your health in 40 seconds.";
	}
	else
	{
		string_information[0] = "Système Immunitaire";
		string_information[1] = "Vous soigne jusqu'à 1.5% (0.3% par niveau)  de votre vie totale par seconde. Au niveau 5, vous regénérez votre vie en entier en 40 secondes.";
	}
}


TalentImmuneSystem::~TalentImmuneSystem()
{
}

float TalentImmuneSystem::GetTalentBonus(int talent_level)
{
	return bonus_initial_value + (talent_level - 1)*bonus_increase;
}

int TalentImmuneSystem::GetNumberStringSkillInformation()
{
	return 2;
}

sf::String TalentImmuneSystem::GetStringSkillInformation(int number_string)
{
	return string_information[number_string];
}