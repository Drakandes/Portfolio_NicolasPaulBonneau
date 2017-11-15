#include "stdafx.h"
#include "G_GemLife.h"

G_GemLife::G_GemLife(int current_language)
{
	language = current_language;
	string_gem_name = language == English_E ? "Gem of life" : "Gemme de vie";
	if (language == English_E)
	{
		string_bonus_tier[0] = "Tier 1: +350 health";
		string_bonus_tier[1] = "Tier 2: +500 health";
		string_bonus_tier[2] = "Tier 3: +650 health";
		string_bonus_tier[3] = "Tier 4: +800 health";
		string_bonus_tier[4] = "Tier 5: +950 health";
	}
	else
	{
		string_bonus_tier[0] = "Tier 1: +350 points de vie";
		string_bonus_tier[1] = "Tier 2: +500 points de vie";
		string_bonus_tier[2] = "Tier 3: +650 points de vie";
		string_bonus_tier[3] = "Tier 4: +800 points de vie";
		string_bonus_tier[4] = "Tier 5: +950 points de vie";
	}
}

G_GemLife::~G_GemLife()
{
}

sf::String G_GemLife::GetStringGemName()
{
	return string_gem_name;
}

int G_GemLife::GetGemTypeBonus()
{
	return type_of_bonus;
}

int G_GemLife::GetGemNumberTiers()
{
	return number_of_tiers;
}

sf::String G_GemLife::GetStringGemBonusForTier(int gem_tier)
{
	return string_bonus_tier[gem_tier];
}

float G_GemLife::GetGemBonusForTier(int gem_tier)
{
	return bonus_tier[gem_tier];
}

float G_GemLife::GetGemPriceForTier(int gem_tier)
{
	return price_gem_tier[gem_tier];
}