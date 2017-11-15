#include "stdafx.h"
#include "TalentAfterEffect.h"

TalentAfterEffect::TalentAfterEffect(int current_language)
{
	language = current_language;
	if (language == English_E)
	{
		string_information[0] = "After effect";
		string_information[1] = "Up to 10% (2% per level) of the damage you deal is redirected to you in shield.";
	}
	else
	{
		string_information[0] = "Effet Secondaire";
		string_information[1] = "Jusqu'� 10% (2% par niveau) des d�g�ts que vous effectuez sont transform�s en bouclier.";
	}
}

TalentAfterEffect::~TalentAfterEffect()
{
}

float TalentAfterEffect::GetTalentBonus(int talent_level)
{
	return bonus_initial_value + (talent_level - 1)*bonus_increase;
}

int TalentAfterEffect::GetNumberStringSkillInformation()
{
	return 2;
}

sf::String TalentAfterEffect::GetStringSkillInformation(int number_string)
{
	return string_information[number_string];
}