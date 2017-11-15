#include "stdafx.h"
#include "G_GemExperience.h"


G_GemExperience::G_GemExperience(int current_language)
{
	language = current_language;
	string_gem_name = language == English_E ? "Gem of experience" : "Gemme d'expérience";
	if (language == English_E)
	{
		string_bonus_tier[0] = "Tier 1: +20% experience";
		string_bonus_tier[1] = "Tier 2: +40% experience";
	}
	else
	{
		string_bonus_tier[0] = "Tier 1: +20% expérience";
		string_bonus_tier[1] = "Tier 2: +40% expérience";
	}
}


G_GemExperience::~G_GemExperience()
{
}
sf::String G_GemExperience::GetStringGemName()
{
	return string_gem_name;
}

int G_GemExperience::GetGemTypeBonus()
{
	return type_of_bonus;
}

int G_GemExperience::GetGemNumberTiers()
{
	return number_of_tiers;
}

sf::String G_GemExperience::GetStringGemBonusForTier(int gem_tier)
{
	return string_bonus_tier[gem_tier];
}

float G_GemExperience::GetGemBonusForTier(int gem_tier)
{
	return bonus_tier[gem_tier];
}

float G_GemExperience::GetGemPriceForTier(int gem_tier)
{
	return price_gem_tier[gem_tier];
}
