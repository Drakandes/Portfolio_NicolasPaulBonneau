#include "stdafx.h"
#include "G_GemDefense.h"

G_GemDefense::G_GemDefense(int current_language)
{
	language = current_language;
	string_gem_name = language == English_E ? "Gem of defense" : "Gemme de défense";
	if (language == English_E)
	{
		string_bonus_tier[0] = "Tier 1: +15 defense";
		string_bonus_tier[1] = "Tier 2: +20 defense";
		string_bonus_tier[2] = "Tier 3: +25 defense";
		string_bonus_tier[3] = "Tier 4: +30 defense";
		string_bonus_tier[4] = "Tier 5: +35 defense";
	}
	else
	{
		string_bonus_tier[0] = "Tier 1: +15 à l'armure";
		string_bonus_tier[1] = "Tier 2: +20 à l'armure";
		string_bonus_tier[2] = "Tier 3: +25 à l'armure";
		string_bonus_tier[3] = "Tier 4: +30 à l'armure";
		string_bonus_tier[4] = "Tier 5: +35 à l'armure";
	}
}

G_GemDefense::~G_GemDefense()
{
}

sf::String G_GemDefense::GetStringGemName()
{
	return string_gem_name;
}

int G_GemDefense::GetGemTypeBonus()
{
	return type_of_bonus;
}

int G_GemDefense::GetGemNumberTiers()
{
	return number_of_tiers;
}

sf::String G_GemDefense::GetStringGemBonusForTier(int gem_tier)
{
	return string_bonus_tier[gem_tier];
}

float G_GemDefense::GetGemBonusForTier(int gem_tier)
{
	return bonus_tier[gem_tier];
}

float G_GemDefense::GetGemPriceForTier(int gem_tier)
{
	return price_gem_tier[gem_tier];
}