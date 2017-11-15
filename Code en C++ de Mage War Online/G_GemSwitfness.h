#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GlobalEnum.h"
#include "G_GemBase.h"

class G_GemSwitfness : public G_GemBase
{
private:
	int language;
	sf::String string_gem_name;
	int type_of_bonus = MovementSpeedPercent;
	const static int number_of_tiers = 2;
	sf::String string_bonus_tier[number_of_tiers];
	float bonus_tier[number_of_tiers]{ 5,10};
	float price_gem_tier[number_of_tiers]{ 65000, 600000 };
public:
	G_GemSwitfness(int current_language);
	~G_GemSwitfness();

	virtual sf::String GetStringGemName();
	virtual int GetGemTypeBonus();
	virtual int GetGemNumberTiers();
	virtual sf::String GetStringGemBonusForTier(int gem_tier);
	virtual float GetGemBonusForTier(int gem_tier);
	virtual float GetGemPriceForTier(int gem_tier);
};
