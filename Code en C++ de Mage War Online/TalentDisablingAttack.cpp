#include "stdafx.h"
#include "TalentDisablingAttack.h"

TalentDisablingAttack::TalentDisablingAttack(int current_language)
{
	language = current_language;
	if (language == English_E)
	{
		string_information[0] = "Disabling Attack";
		string_information[1] = "Any ennemy hit by your basic attacks will be stunned for up to 0.3 second (1 second per level).";
	}
	else
	{
		string_information[0] = "Attaque Paralysante";
		string_information[1] = "Étourdit jusqu'à 0.3 seconde (1 seconde par niveau) tous les ennemies touchés par vos attaques de base.";
	}
}

TalentDisablingAttack::~TalentDisablingAttack()
{
}

float TalentDisablingAttack::GetTalentBonus(int talent_level)
{
	return bonus_initial_value + (talent_level - 1)*bonus_increase;
}

int TalentDisablingAttack::GetNumberStringSkillInformation()
{
	return 2;
}

sf::String TalentDisablingAttack::GetStringSkillInformation(int number_string)
{
	return string_information[number_string];
}