#include "stdafx.h"
#include "TalentQuickAttack.h"


TalentQuickAttack::TalentQuickAttack(int current_language)
{
	language = current_language;
	if (language == English_E)
	{
		string_information[0] = "Quick Attack";
		string_information[1] = "Increase the speed of your basic attacks and your skills by up to 25% (5% per level).";
	}
	else
	{
		string_information[0] = "Attaque Rapide";
		string_information[1] = "Augmente jusqu'à 25% (5% par niveau) la vitesse de vos projectiles.";
	}
}


TalentQuickAttack::~TalentQuickAttack()
{
}

float TalentQuickAttack::GetTalentBonus(int talent_level)
{
	return bonus_initial_value + (talent_level - 1)*bonus_increase;
}

int TalentQuickAttack::GetNumberStringSkillInformation()
{
	return 2;
}

sf::String TalentQuickAttack::GetStringSkillInformation(int number_string)
{
	return string_information[number_string];
}