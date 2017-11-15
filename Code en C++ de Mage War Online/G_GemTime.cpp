#include "stdafx.h"
#include "G_GemTime.h"


G_GemTime::G_GemTime(int current_language)
{
	language = current_language;
	string_gem_name = language == English_E ? "Gem of time" : "Gemme du temps";
	if (language == English_E)
	{
		string_bonus_tier[0] = "Tier 1: +10% cooldown reduction";
		string_bonus_tier[1] = "Tier 2: +15% cooldown reduction";
		string_bonus_tier[2] = "Tier 3: +20% cooldown reduction";
	}
	else
	{
		string_bonus_tier[0] = "Tier 1: +10% au temps de latence";
		string_bonus_tier[1] = "Tier 2: +15% au temps de latence";
		string_bonus_tier[2] = "Tier 3: +20% au temps de latence";
	}
}


G_GemTime::~G_GemTime()
{
}

sf::String G_GemTime::GetStringGemName()
{
	return string_gem_name;
}

int G_GemTime::GetGemTypeBonus()
{
	return type_of_bonus;
}

int G_GemTime::GetGemNumberTiers()
{
	return number_of_tiers;
}

sf::String G_GemTime::GetStringGemBonusForTier(int gem_tier)
{
	return string_bonus_tier[gem_tier];
}

float G_GemTime::GetGemBonusForTier(int gem_tier)
{
	return bonus_tier[gem_tier];
}

float G_GemTime::GetGemPriceForTier(int gem_tier)
{
	return price_gem_tier[gem_tier];
}
