#pragma once
#include "TalentBase.h"
class TalentAfterEffect :
	public TalentBase
{
private:
	int language;
	sf::String string_information[2];
	float bonus_initial_value = 2;
	float bonus_increase = 2;
public:
	TalentAfterEffect(int current_language);
	~TalentAfterEffect();

	virtual int GetNumberStringSkillInformation();
	virtual sf::String GetStringSkillInformation(int number_string);
	virtual float GetTalentBonus(int talent_level);
	virtual int GetTypeTreeTalent() { return 1; }
	virtual int GetMaxLevelTalent() { return 5; }
	virtual int GetTierTalent() { return 3; }
};

