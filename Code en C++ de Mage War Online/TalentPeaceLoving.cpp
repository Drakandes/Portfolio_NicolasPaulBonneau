#include "stdafx.h"
#include "TalentPeaceLoving.h"


TalentPeaceLoving::TalentPeaceLoving(int current_language)
{
	language = current_language;
	if (language == English_E)
	{
		string_information[0] = "Peace-lover";
		string_information[1] = "Decrease the time it takes you to become out of combat by up to 2 seconds (0.4 second per level). Initially, it takes 7 seconds to be out of combat.";
	}
	else
	{
		string_information[0] = "Fervent de la Paix";
		string_information[1] = "Réduit jusqu'à 2 secondes (0.4 seconde par niveau) le temps nécessairement afin d'être hors-combat. Initialement, il faut 7 secondes pour devenir hors-combat.";
	}
}


TalentPeaceLoving::~TalentPeaceLoving()
{
}

float TalentPeaceLoving::GetTalentBonus(int talent_level)
{
	return bonus_initial_value + (talent_level - 1)*bonus_increase;
}

int TalentPeaceLoving::GetNumberStringSkillInformation()
{
	return 2;
}

sf::String TalentPeaceLoving::GetStringSkillInformation(int number_string)
{
	return string_information[number_string];
}