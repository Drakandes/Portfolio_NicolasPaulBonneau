#include "stdafx.h"
#include "G_GemAttack.h"

G_GemAttack::G_GemAttack(int current_language)
{
	language = current_language; 
	string_gem_name = language == English_E ? "Gem of attack" : "Gemme d'attaque";
	if (language == English_E)
	{
		string_bonus_tier[0] = "Tier 1: +20 attack damage";
		string_bonus_tier[1] = "Tier 2: +30 attack damage";
		string_bonus_tier[2] = "Tier 3: +40 attack damage";
		string_bonus_tier[3] = "Tier 4: +50 attack damage";
		string_bonus_tier[4] = "Tier 5: +60 attack damage";
	}
	else
	{
		string_bonus_tier[0] = "Tier 1: +20 de dégâts bonus";
		string_bonus_tier[1] = "Tier 2: +30 de dégâts bonus";
		string_bonus_tier[2] = "Tier 3: +40 de dégâts bonus";
		string_bonus_tier[3] = "Tier 4: +50 de dégâts bonus";
		string_bonus_tier[4] = "Tier 5: +60 de dégâts bonus";
	}
}

G_GemAttack::~G_GemAttack()
{
}

sf::String G_GemAttack::GetStringGemName()
{
	return string_gem_name;
}

int G_GemAttack::GetGemTypeBonus()
{
	return type_of_bonus;
}

int G_GemAttack::GetGemNumberTiers()
{
	return number_of_tiers;
}

sf::String G_GemAttack::GetStringGemBonusForTier(int gem_tier)
{
	return string_bonus_tier[gem_tier];
}

float G_GemAttack::GetGemBonusForTier(int gem_tier)
{
	return bonus_tier[gem_tier];
}

float G_GemAttack::GetGemPriceForTier(int gem_tier)
{
	return price_gem_tier[gem_tier];
}
