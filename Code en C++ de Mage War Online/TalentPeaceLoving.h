#pragma once
#include "TalentBase.h"
class TalentPeaceLoving :
	public TalentBase
{
private:
	int language;
	sf::String string_information[2];
	float bonus_initial_value = 0.4;
	float bonus_increase = 0.4;
public:
	TalentPeaceLoving(int current_language);
	~TalentPeaceLoving();

	virtual int GetNumberStringSkillInformation();
	virtual sf::String GetStringSkillInformation(int number_string);
	virtual float GetTalentBonus(int talent_level);
	virtual int GetTypeTreeTalent() { return 2; }
	virtual int GetMaxLevelTalent() { return 5; }
	virtual int GetTierTalent() { return 3; }
};

