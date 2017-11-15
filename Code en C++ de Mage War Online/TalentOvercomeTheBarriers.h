#pragma once
#include "TalentBase.h"
class TalentOvercomeTheBarriers :
	public TalentBase
{
private:
	int language;
	sf::String string_information[2];
	float bonus_initial_value = 1;
	float bonus_increase = 1;
public:
	TalentOvercomeTheBarriers(int current_language);
	~TalentOvercomeTheBarriers();

	virtual int GetNumberStringSkillInformation();
	virtual sf::String GetStringSkillInformation(int number_string);
	virtual float GetTalentBonus(int talent_level);
	virtual int GetTypeTreeTalent() { return 1; }
	virtual int GetMaxLevelTalent() { return 3; }
	virtual int GetTierTalent() { return 2; }
};

