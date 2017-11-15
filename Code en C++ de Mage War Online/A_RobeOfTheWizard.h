#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GlobalEnum.h"
#include "A_ArmorBase.h"

class A_RobeOfTheWizard : public A_ArmorBase
{
public:
	int language;
	sf::String name_armor;
	sf::String armor_level_recommanded;
	int level = 19;
	int armor_price = ArmorCost(level);
	int armor_number_of_gems = 9;
	int armor_number_of_equipments = 6;
	int armor_number_of_skills = 8;
	sf::String armor_bonus_string = "+10% Cooldown (latence)";
	int armor_type_bonus = A_Cooldown;
	float armor_bonus = 10;

	virtual int ReturnArmorLevelRequired() { return level; }
	virtual sf::String ReturnNameArmor();
	 virtual sf::String ReturnArmorLevelRecommandedString();
	 virtual int ReturnArmorPrice();
	 virtual int ReturnAmorNumberGems();
	 virtual int ReturnArmorNumberEquipments();
	 virtual int ReturnArmorNumberSkills();
	 virtual sf::String ReturnArmorBonusString();
	 virtual int ReturnArmorBonusType();
	virtual  int ReturnArmorBonusNumber();

	A_RobeOfTheWizard(int current_language);
	~A_RobeOfTheWizard();
};

