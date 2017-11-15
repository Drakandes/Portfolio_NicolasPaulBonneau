#include "stdafx.h"
#include "TalentOvercomeTheBarriers.h"


TalentOvercomeTheBarriers::TalentOvercomeTheBarriers(int current_language)
{
	language = current_language;
	if (language == English_E)
	{
		string_information[0] = "Overcome The Barriers";
		string_information[1] = "When out of combat, you get shielded by up to 3% (1% per level) of your maximum health per second.";
	}
	else
	{
		string_information[0] = "Dépasser les Limites";
		string_information[1] = "Lorsque vous êtes hors-combat, vous recevez jusqu'à 3% (1% par niveau) de votre vite totale en bouclier par seconde.";
	}
}

TalentOvercomeTheBarriers::~TalentOvercomeTheBarriers()
{
}

float TalentOvercomeTheBarriers::GetTalentBonus(int talent_level)
{
	return bonus_initial_value + (talent_level - 1)*bonus_increase;
}

int TalentOvercomeTheBarriers::GetNumberStringSkillInformation()
{
	return 2;
}

sf::String TalentOvercomeTheBarriers::GetStringSkillInformation(int number_string)
{
	return string_information[number_string];
}