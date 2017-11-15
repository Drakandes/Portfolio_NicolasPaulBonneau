#include "stdafx.h"
#include "G_GemBase.h"

G_GemBase::G_GemBase()
{
}

G_GemBase::~G_GemBase()
{
}

sf::String G_GemBase::GetStringGemName()
{
	return string_gem_name;
}

int G_GemBase::GetGemTypeBonus()
{
	return type_of_bonus;
}

int G_GemBase::GetGemNumberTiers()
{
	return number_of_tiers;
}

sf::String G_GemBase::GetStringGemBonusForTier(int gem_tier)
{
	return string_bonus_tier[gem_tier];
}

float G_GemBase::GetGemBonusForTier(int gem_tier)
{
	return bonus_tier[gem_tier];
}

float G_GemBase::GetGemPriceForTier(int gem_tier)
{
	return price_gem_tier[gem_tier];
}