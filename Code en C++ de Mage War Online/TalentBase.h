#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "GlobalEnum.h"

class TalentBase
{
public:
	TalentBase();
	~TalentBase();

	virtual int GetNumberStringSkillInformation();
	virtual sf::String GetStringSkillInformation(int number_string);
	virtual float GetTalentBonus(int talent_level) { return 0; }
	virtual int GetTypeTreeTalent() { return 0; }
	virtual int GetMaxLevelTalent() { return 0; }
	virtual int GetTierTalent() { return 0; std::cout << "Error" << std::endl; }
};

