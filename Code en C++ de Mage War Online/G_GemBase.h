#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GlobalEnum.h"
#include "G_GemBase.h"

class G_GemBase
{
private:
	sf::String string_gem_name = "Unknown";
	int type_of_bonus = Nothing;
	const static int number_of_tiers = 1;
	sf::String string_bonus_tier[number_of_tiers]{ "Unknown" };
	float bonus_tier[number_of_tiers]{ 1};
	float price_gem_tier[number_of_tiers]{ 1};
public:
	G_GemBase();
	~G_GemBase();

	virtual sf::String GetStringGemName();
	virtual int GetGemTypeBonus();
	virtual int GetGemNumberTiers();
	virtual sf::String GetStringGemBonusForTier(int gem_tier);
	virtual float GetGemBonusForTier(int gem_tier);
	virtual float GetGemPriceForTier(int gem_tier);
};

