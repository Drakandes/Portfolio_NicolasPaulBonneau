#include "stdafx.h"
#include "G_GemSwitfness.h"


G_GemSwitfness::G_GemSwitfness(int current_language)
{
	language = current_language;
	string_gem_name = language == English_E ? "Gem of swiftness" : "Gemme de rapidité";
	if (language == English_E)
	{
		string_bonus_tier[0] = "Tier 1: +5% movement speed";
		string_bonus_tier[1] = "Tier 2: +10% movement speed";
	}
	else
	{
		string_bonus_tier[0] = "Tier 1: +5% à la vitesse de déplacement";
		string_bonus_tier[1] = "Tier 2: +10% à la vitesse de déplacement";
	}
}


G_GemSwitfness::~G_GemSwitfness()
{
}

sf::String G_GemSwitfness::GetStringGemName()
{
	return string_gem_name;
}

int G_GemSwitfness::GetGemTypeBonus()
{
	return type_of_bonus;
}

int G_GemSwitfness::GetGemNumberTiers()
{
	return number_of_tiers;
}

sf::String G_GemSwitfness::GetStringGemBonusForTier(int gem_tier)
{
	return string_bonus_tier[gem_tier];
}

float G_GemSwitfness::GetGemBonusForTier(int gem_tier)
{
	return bonus_tier[gem_tier];
}

float G_GemSwitfness::GetGemPriceForTier(int gem_tier)
{
	return price_gem_tier[gem_tier];
}