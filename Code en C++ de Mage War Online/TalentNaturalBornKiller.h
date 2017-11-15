#pragma once
#include "TalentBase.h"
class TalentNaturalBornKiller :
	public TalentBase
{
private:
	int language;
	sf::String string_information[2];
	float bonus_initial_value = 0.07;
	float bonus_increase = 0.07;
public:
	TalentNaturalBornKiller(int current_language);
	~TalentNaturalBornKiller();

	virtual int GetNumberStringSkillInformation();
	virtual sf::String GetStringSkillInformation(int number_string);
	virtual float GetTalentBonus(int talent_level);
	virtual int GetTypeTreeTalent() { return 0; }
	virtual int GetMaxLevelTalent() { return 3; }
	virtual int GetTierTalent() { return 2; }
};

