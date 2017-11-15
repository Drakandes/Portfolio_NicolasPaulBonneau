#include "stdafx.h"
#include "TalentUnleashedPower.h"


TalentUnleashedPower::TalentUnleashedPower(int current_language)
{
	language = current_language;
	if (language == English_E)
	{
		string_information[0] = "Unleashed Power";
		string_information[1] = "Every 3 skills, empower your next damaging or healing skill by up to 33% (11% per level).";
	}
	else
	{
		string_information[0] = "Pouvoir Relâché";
		string_information[1] = "À chaque 3 sorts, augmente jusqu'à 33% (11% par niveau) les dégâts ou les soins de votre prochain sort.";
	}
}


TalentUnleashedPower::~TalentUnleashedPower()
{
}

float TalentUnleashedPower::GetTalentBonus(int talent_level)
{
	return bonus_initial_value + (talent_level - 1)*bonus_increase;
}

int TalentUnleashedPower::GetNumberStringSkillInformation()
{
	return 2;
}

sf::String TalentUnleashedPower::GetStringSkillInformation(int number_string)
{
	return string_information[number_string];
}