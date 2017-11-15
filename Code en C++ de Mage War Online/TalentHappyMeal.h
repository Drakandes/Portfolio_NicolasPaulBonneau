#pragma once
#include "TalentBase.h"
class TalentHappyMeal :
	public TalentBase
{
private:
	int language;
	sf::String string_information[2];
	float bonus_initial_value = 2.4;
	float bonus_increase = 2.4;
public:
	TalentHappyMeal(int current_language);
	~TalentHappyMeal();

	virtual int GetNumberStringSkillInformation();
	virtual sf::String GetStringSkillInformation(int number_string);
	virtual float GetTalentBonus(int talent_level);
	virtual int GetTypeTreeTalent() { return 0; }
	virtual int GetMaxLevelTalent() { return 5; }
	virtual int GetTierTalent() { return 3; }
};

