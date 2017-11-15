#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GlobalEnum.h"
#include "G_GemBase.h"

class G_GemAvarice : public G_GemBase
{
private:
	int language;
	sf::String string_gem_name;
	int type_of_bonus = MoneyPercent;
	const static int number_of_tiers = 2;
	sf::String string_bonus_tier[number_of_tiers]{ "Tier 1: +20% gold", "Tier 2: +40% gold" };
	float bonus_tier[number_of_tiers]{ 20,40 };
	float price_gem_tier[number_of_tiers]{ 65000,600000 };
public:
	G_GemAvarice(int current_language);
	~G_GemAvarice();

	virtual sf::String GetStringGemName();
	virtual int GetGemTypeBonus();
	virtual int GetGemNumberTiers();
	virtual sf::String GetStringGemBonusForTier(int gem_tier);
	virtual float GetGemBonusForTier(int gem_tier);
	virtual float GetGemPriceForTier(int gem_tier);
};

