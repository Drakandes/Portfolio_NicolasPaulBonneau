#pragma once
#include "TalentBase.h"
class TalentRampage :
	public TalentBase
{
private:
	int language;
	sf::String string_information[2];
	float bonus_initial_value = 2;
	float bonus_increase = 2;
public:
	TalentRampage(int current_language);
	~TalentRampage();

	virtual int GetNumberStringSkillInformation();
	virtual sf::String GetStringSkillInformation(int number_string);
	virtual float GetTalentBonus(int talent_level);
	virtual int GetTypeTreeTalent() { return 0; }
	virtual int GetMaxLevelTalent() { return 3; }
	virtual int GetTierTalent() { return 6; }
};

