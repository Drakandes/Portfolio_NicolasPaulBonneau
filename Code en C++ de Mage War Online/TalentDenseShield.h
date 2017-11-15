#pragma once
#include "TalentBase.h"
class TalentDenseShield :
	public TalentBase
{
private:
	int language;
	sf::String string_information[2];
	float bonus_initial_value = 9;
	float bonus_increase = 9;
public:
	TalentDenseShield(int current_language);
	~TalentDenseShield();

	virtual int GetNumberStringSkillInformation();
	virtual sf::String GetStringSkillInformation(int number_string);
	virtual float GetTalentBonus(int talent_level);
	virtual int GetTypeTreeTalent() { return 1; }
	virtual int GetMaxLevelTalent() { return 5; }
	virtual int GetTierTalent() { return 5; }
};

