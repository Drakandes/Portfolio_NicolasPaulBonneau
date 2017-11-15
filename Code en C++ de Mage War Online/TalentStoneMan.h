#pragma once
#include "TalentBase.h"
class TalentStoneMan :
	public TalentBase
{
private:
	int language;
	sf::String string_information[2];
	float bonus_initial_value = 3;
	float bonus_increase = 3;
public:
	TalentStoneMan(int current_language);
	~TalentStoneMan();

	virtual int GetNumberStringSkillInformation();
	virtual sf::String GetStringSkillInformation(int number_string);
	virtual float GetTalentBonus(int talent_level);
	virtual int GetTypeTreeTalent() { return 1; }
	virtual int GetMaxLevelTalent() { return 5; }
	virtual int GetTierTalent() { return 1; }
};

