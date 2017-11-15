#pragma once
#include "TalentBase.h"
class TalentReinforcedShield :
	public TalentBase
{
private:
	int language;
	sf::String string_information[2];
	float bonus_initial_value = 25;
	float bonus_increase = 25;
public:
	TalentReinforcedShield(int current_language);
	~TalentReinforcedShield();

	virtual int GetNumberStringSkillInformation();
	virtual sf::String GetStringSkillInformation(int number_string);
	virtual float GetTalentBonus(int talent_level);
	virtual int GetTypeTreeTalent() { return 1; }
	virtual int GetMaxLevelTalent() { return 3; }
	virtual int GetTierTalent() { return 6; }
};

