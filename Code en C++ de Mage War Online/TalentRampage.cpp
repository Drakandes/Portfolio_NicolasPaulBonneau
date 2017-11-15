#include "stdafx.h"
#include "TalentRampage.h"


TalentRampage::TalentRampage(int current_language)
{
	language = current_language;
	if (language == English_E)
	{
		string_information[0] = "Rampage";
		string_information[1] = "Increase your damage by up to 6% (2% per level) for 2 seconds whenever you hit an ennemy with your basic attacks. Can stack up to 4 times.";
	}
	else
	{
		string_information[0] = "Déchaînement";
		string_information[1] = "Augmente jusqu'à 6% (2% par niveau) vos dégâts pendant 2 secondes lorsque vous touchez un ennemi avec vos attaques de base. Peut se cumuler jusqu'à 4 fois.";
	}
}


TalentRampage::~TalentRampage()
{
}

float TalentRampage::GetTalentBonus(int talent_level)
{
	return bonus_initial_value + (talent_level - 1)*bonus_increase;
}

int TalentRampage::GetNumberStringSkillInformation()
{
	return 2;
}

sf::String TalentRampage::GetStringSkillInformation(int number_string)
{
	return string_information[number_string];
}