#pragma once
#include "TalentBase.h"
class TalentEnraged :
	public TalentBase
{
private:
	int language;
	sf::String string_information[2];
	float bonus_initial_value = 3;
	float bonus_increase = 3;
public:
	TalentEnraged(int current_language);
	~TalentEnraged();

	virtual int GetNumberStringSkillInformation();
	virtual sf::String GetStringSkillInformation(int number_string);
	virtual float GetTalentBonus(int talent_level);
	virtual int GetTypeTreeTalent() { return 0; }
	virtual int GetMaxLevelTalent() { return 5; }
	virtual int GetTierTalent() { return 1; }
};

