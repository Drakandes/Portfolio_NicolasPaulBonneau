#include "stdafx.h"
#include "TalentHasty.h"


TalentHasty::TalentHasty(int current_language)
{
	language = current_language;
	if (language == English_E)
	{
		string_information[0] = "Hasty";
		string_information[1] = "Whenever you hit an ennemy with your basic attack, your movement speed is increased by up to 9% (3% per level) for 2 seconds. The bonus doesn't stack.";
	}
	else
	{
		string_information[0] = "Hâtif";
		string_information[1] = "Lorsque vous touchez un ennemi avec vos attaques de base, augmente jusqu'à 9% (3% par niveau) votre vitesse déplacement pendant 2 secondes. Cet effet ne se cumule pas.";
	}
}


TalentHasty::~TalentHasty()
{
}

float TalentHasty::GetTalentBonus(int talent_level)
{
	return bonus_initial_value + (talent_level - 1)*bonus_increase;
}

int TalentHasty::GetNumberStringSkillInformation()
{
	return 2;
}

sf::String TalentHasty::GetStringSkillInformation(int number_string)
{
	return string_information[number_string];
}