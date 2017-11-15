#include "stdafx.h"
#include "TalentReinforcedShield.h"


TalentReinforcedShield::TalentReinforcedShield(int current_language)
{
	language = current_language;
	if (language == English_E)
	{
		string_information[0] = "Reinforced Shield";
		string_information[1] = "Apply up to 75% (25% per level) of your armor's effectiveness on your shield.";
	}
	else
	{
		string_information[0] = "Bouclier Renforc�";
		string_information[1] = "Applique jusqu'� 75% (25% par niveau) de l'efficacit� de votre armure � vos boucliers.";
	}
}


TalentReinforcedShield::~TalentReinforcedShield()
{
}

float TalentReinforcedShield::GetTalentBonus(int talent_level)
{
	return bonus_initial_value + (talent_level - 1)*bonus_increase;
}

int TalentReinforcedShield::GetNumberStringSkillInformation()
{
	return 2;
}

sf::String TalentReinforcedShield::GetStringSkillInformation(int number_string)
{
	return string_information[number_string];
}