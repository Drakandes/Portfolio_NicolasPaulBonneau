#include "stdafx.h"
#include "TalentBlockade.h"

TalentBlockade::TalentBlockade(int current_language)
{
	language = current_language;
	if (language == English_E)
	{
		string_information[0] = "Blockade";
		string_information[1] = "Reduce your damage taken by up to 10% (3.3% per level). Damage reduction is applied before armor.";
	}
	else
	{
		string_information[0] = "Blocus";
		string_information[1] = "Réduit jusqu'à 10% (3.3% par niveau) les dégâts que vous subissez. La réduction des dégâts reçus est appliquée avant l'armure.";
	}
}

TalentBlockade::~TalentBlockade()
{
}

float TalentBlockade::GetTalentBonus(int talent_level)
{
	return bonus_initial_value + (talent_level - 1)*bonus_increase;
}

int TalentBlockade::GetNumberStringSkillInformation()
{
	return 2;
}

sf::String TalentBlockade::GetStringSkillInformation(int number_string)
{
	return string_information[number_string];
}