#include "stdafx.h"
#include "TalentIronTip.h"


TalentIronTip::TalentIronTip(int current_language)
{
	language = current_language;
	if (language == English_E)
	{
		string_information[0] = "Iron Tip";
		string_information[1] = "Increase your armor penetration by up to 15% (3% per level). Armor penetration reduces the efficiency of ennemies' armor.";
	}
	else
	{
		string_information[0] = "Pointe d'Acier";
		string_information[1] = "Augmente jusqu'à 15% (3% par niveau) votre pénétration d'armure. La pénétration d'armure réduit l'efficacité de l'armure de la cible.";
	}
}


TalentIronTip::~TalentIronTip()
{
}

float TalentIronTip::GetTalentBonus(int talent_level)
{
	return bonus_initial_value + (talent_level - 1)*bonus_increase;
}

int TalentIronTip::GetNumberStringSkillInformation()
{
	return 2;
}

sf::String TalentIronTip::GetStringSkillInformation(int number_string)
{
	return string_information[number_string];
}