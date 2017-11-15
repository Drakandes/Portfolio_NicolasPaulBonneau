#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GlobalEnum.h"
#include "G_GemBase.h"

class G_GemAttack : public G_GemBase
{
private:
	int language;
	sf::String string_gem_name;
	int type_of_bonus = DamageAddition;
	const static int number_of_tiers = 5;
	sf::String string_bonus_tier[number_of_tiers];
	float bonus_tier[number_of_tiers]{ 20,30,40,50,60 };
	float price_gem_tier[number_of_tiers]{ 10000,35000,250000,450000,750000 };
public:
	G_GemAttack(int current_language);
	~G_GemAttack();

	virtual sf::String GetStringGemName();
	virtual int GetGemTypeBonus();
	virtual int GetGemNumberTiers();
	virtual sf::String GetStringGemBonusForTier(int gem_tier);
	virtual float GetGemBonusForTier(int gem_tier);
	virtual float GetGemPriceForTier(int gem_tier);
};

