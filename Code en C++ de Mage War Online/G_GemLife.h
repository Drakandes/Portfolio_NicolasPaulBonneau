#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GlobalEnum.h"
#include "G_GemBase.h"

class G_GemLife : public G_GemBase
{
private:
	int language;
	sf::String string_gem_name;
	int type_of_bonus = HealthAddition;
	const static int number_of_tiers = 5;
	sf::String string_bonus_tier[number_of_tiers];
	float bonus_tier[number_of_tiers]{ 350,500,650,800,950 };
	float price_gem_tier[number_of_tiers]{ 10000,35000,250000,450000,750000 };
public:
	G_GemLife(int current_language);
	~G_GemLife();

	virtual sf::String GetStringGemName();
	virtual int GetGemTypeBonus();
	virtual int GetGemNumberTiers();
	virtual sf::String GetStringGemBonusForTier(int gem_tier);
	virtual float GetGemBonusForTier(int gem_tier);
	virtual float GetGemPriceForTier(int gem_tier);
};

