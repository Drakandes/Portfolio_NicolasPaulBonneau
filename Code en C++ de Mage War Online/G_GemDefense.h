#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GlobalEnum.h"
#include "G_GemBase.h"

class G_GemDefense : public G_GemBase
{
private:
	int language;
	sf::String string_gem_name;
	int type_of_bonus = DefenseAddition;
	const static int number_of_tiers = 5;
	sf::String string_bonus_tier[number_of_tiers];
	float bonus_tier[number_of_tiers]{ 15,20,25,30,35 };
	float price_gem_tier[number_of_tiers]{ 10000,35000,250000,450000,750000 };
public:
	G_GemDefense(int current_language);
	~G_GemDefense();

	virtual sf::String GetStringGemName();
	virtual int GetGemTypeBonus();
	virtual int GetGemNumberTiers();
	virtual sf::String GetStringGemBonusForTier(int gem_tier);
	virtual float GetGemBonusForTier(int gem_tier);
	virtual float GetGemPriceForTier(int gem_tier);
};

