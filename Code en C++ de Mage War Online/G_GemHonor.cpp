#include "stdafx.h"
#include "G_GemHonor.h"


G_GemHonor::G_GemHonor(int current_language)
{
	language = current_language;
	string_gem_name = language == English_E ? "Gem of honor" : "Gemme d'honneur";
	if (language == English_E)
	{
		string_bonus_tier[0] = "Tier 1: +20% honor";
		string_bonus_tier[1] = "Tier 2: +40% honor";
	}
	else
	{
		string_bonus_tier[0] = "Tier 1: +20% d'honneur";
		string_bonus_tier[1] = "Tier 2: +40% d'honneur";
	}
}


G_GemHonor::~G_GemHonor()
{
}
sf::String G_GemHonor::GetStringGemName()
{
	return string_gem_name;
}

int G_GemHonor::GetGemTypeBonus()
{
	return type_of_bonus;
}

int G_GemHonor::GetGemNumberTiers()
{
	return number_of_tiers;
}

sf::String G_GemHonor::GetStringGemBonusForTier(int gem_tier)
{
	return string_bonus_tier[gem_tier];
}

float G_GemHonor::GetGemBonusForTier(int gem_tier)
{
	return bonus_tier[gem_tier];
}

float G_GemHonor::GetGemPriceForTier(int gem_tier)
{
	return price_gem_tier[gem_tier];
}
