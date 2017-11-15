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
		string_information[1] = "R�duit jusqu'� 10% (3.3% par niveau) les d�g�ts que vous subissez. La r�duction des d�g�ts re�us est appliqu�e avant l'armure.";
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