#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GlobalEnum.h"
#include "G_GemBase.h"

class G_GemTime : public G_GemBase
{
private:
	int language;
	sf::String string_gem_name;
	int type_of_bonus = CooldownReduction;
	const static int number_of_tiers = 3;
	sf::String string_bonus_tier[number_of_tiers];
	float bonus_tier[number_of_tiers]{ 5,10,15};
	float price_gem_tier[number_of_tiers]{ 35000,250000,750000};
public:
	G_GemTime(int current_language);
	~G_GemTime();

	virtual sf::String GetStringGemName();
	virtual int GetGemTypeBonus();
	virtual int GetGemNumberTiers();
	virtual sf::String GetStringGemBonusForTier(int gem_tier);
	virtual float GetGemBonusForTier(int gem_tier);
	virtual float GetGemPriceForTier(int gem_tier);
};

