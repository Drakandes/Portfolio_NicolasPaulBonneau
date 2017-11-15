#pragma once
#include "TalentBase.h"
class TalentUnstoppable :
	public TalentBase
{
private:
	int language;
	sf::String string_information[2];
	float bonus_initial_value = 8;
	float bonus_increase = 8;
public:
	TalentUnstoppable(int current_language);
	~TalentUnstoppable();

	virtual int GetNumberStringSkillInformation();
	virtual sf::String GetStringSkillInformation(int number_string);
	virtual float GetTalentBonus(int talent_level);
	virtual int GetTypeTreeTalent() { return 2; }
	virtual int GetMaxLevelTalent() { return 5; }
	virtual int GetTierTalent() { return 5; }
};

