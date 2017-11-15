#include "stdafx.h"
#include "G_GemAvarice.h"


G_GemAvarice::G_GemAvarice(int current_language)
{
	language = current_language;
	string_gem_name = language == English_E ? "Gem of avarice" : "Gemme d'avarice";
	if (language == English_E)
	{
		string_bonus_tier[0] = "Tier 1: +20% gold";
		string_bonus_tier[1] = "Tier 2: +40% gold";
	}
	else
	{
		string_bonus_tier[0] = "Tier 1: +20% pièces d'or";
		string_bonus_tier[1] = "Tier 2: +40% pièces d'or";
	}
}


G_GemAvarice::~G_GemAvarice()
{
}
sf::String G_GemAvarice::GetStringGemName()
{
	return string_gem_name;
}

int G_GemAvarice::GetGemTypeBonus()
{
	return type_of_bonus;
}

int G_GemAvarice::GetGemNumberTiers()
{
	return number_of_tiers;
}

sf::String G_GemAvarice::GetStringGemBonusForTier(int gem_tier)
{
	return string_bonus_tier[gem_tier];
}

float G_GemAvarice::GetGemBonusForTier(int gem_tier)
{
	return bonus_tier[gem_tier];
}

float G_GemAvarice::GetGemPriceForTier(int gem_tier)
{
	return price_gem_tier[gem_tier];
}
