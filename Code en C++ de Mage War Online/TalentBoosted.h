#pragma once
#include "TalentBase.h"

class TalentBoosted :
	public TalentBase
{
private:
	int language;
	sf::String string_information[2];
	float bonus_initial_value = 7;
	float bonus_increase = 7;
public:
	TalentBoosted(int current_language);
	~TalentBoosted();

	virtual int GetNumberStringSkillInformation();
	virtual sf::String GetStringSkillInformation(int number_string);
	virtual float GetTalentBonus(int talent_level);
	virtual int GetTypeTreeTalent() { return 0; }
	virtual int GetMaxLevelTalent() { return 5; }
	virtual int GetTierTalent() { return 1; }
};

