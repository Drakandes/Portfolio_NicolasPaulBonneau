#include "stdafx.h"
#include "TalentDenseShield.h"

TalentDenseShield::TalentDenseShield(int current_language)
{
	language = current_language;
	if (language == English_E)
	{
		string_information[0] = "Dense Shield";
		string_information[1] = "Increase the capacity of your shield up to 75% (9% per level) of your maximum health. Initially, the capacity of your shield is equal to 30% of your maximum health.";
	}
	else
	{
		string_information[0] = "Bouclier Dense";
		string_information[1] = "Augmente jusqu'à 75% (9% par niveau) de votre vite totale la capacité de votre bouclier. Initialement, la capacité de votre bouclier est égale à 30% de votre vie totale.";
	}
}

TalentDenseShield::~TalentDenseShield()
{
}

float TalentDenseShield::GetTalentBonus(int talent_level)
{
	return bonus_initial_value + (talent_level - 1)*bonus_increase;
}

int TalentDenseShield::GetNumberStringSkillInformation()
{
	return 2;
}

sf::String TalentDenseShield::GetStringSkillInformation(int number_string)
{
	return string_information[number_string];
}