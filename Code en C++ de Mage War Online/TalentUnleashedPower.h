#pragma once
#include "TalentBase.h"
class TalentUnleashedPower :
	public TalentBase
{
private:
	int language;
	sf::String string_information[2];
	float bonus_initial_value = 11;
	float bonus_increase = 11;
public:
	TalentUnleashedPower(int current_language);
	~TalentUnleashedPower();

	virtual int GetNumberStringSkillInformation();
	virtual sf::String GetStringSkillInformation(int number_string);
	virtual float GetTalentBonus(int talent_level);
	virtual int GetTypeTreeTalent() { return 0; }
	virtual int GetMaxLevelTalent() { return 3; }
	virtual int GetTierTalent() { return 4; }
};

