#include "stdafx.h"
#include "TalentSharpShooter.h"


TalentSharpShooter::TalentSharpShooter(int current_language)
{
	language = current_language;
	if (language == English_E)
	{
		string_information[0] = "Sharp Shooter";
		string_information[1] = "Increase the range of your basic attacks and your skills by up to 25% (5% per level).";
	}
	else
	{
		string_information[0] = "Tireur de Pointe";
		string_information[1] = "Augmente jusqu'à 25% (5% par niveau) la portée de vos projectiles.";
	}
}


TalentSharpShooter::~TalentSharpShooter()
{
}

float TalentSharpShooter::GetTalentBonus(int talent_level)
{
	return bonus_initial_value + (talent_level - 1)*bonus_increase;
}

int TalentSharpShooter::GetNumberStringSkillInformation()
{
	return 2;
}

sf::String TalentSharpShooter::GetStringSkillInformation(int number_string)
{
	return string_information[number_string];
}