#pragma once
#include "TalentBase.h"
class TalentHasty :
	public TalentBase
{
private:
	int language;
	sf::String string_information[2];
	float bonus_initial_value = 3;
	float bonus_increase = 3;
public:
	TalentHasty(int current_language);
	~TalentHasty();

	virtual int GetNumberStringSkillInformation();
	virtual sf::String GetStringSkillInformation(int number_string);
	virtual float GetTalentBonus(int talent_level);
	virtual int GetTypeTreeTalent() { return 2; }
	virtual int GetMaxLevelTalent() { return 3; }
	virtual int GetTierTalent() { return 2; }
};

