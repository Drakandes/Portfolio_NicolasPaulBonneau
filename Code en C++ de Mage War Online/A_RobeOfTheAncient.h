#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GlobalEnum.h"
#include "A_ArmorBase.h"

class A_RobeOfTheAncient : public A_ArmorBase
{
public:
	int language;
	sf::String name_armor;
	sf::String armor_level_recommanded;
	int level = 19;
	int armor_price = ArmorCost(level);
	int armor_number_of_gems = 8;
	int armor_number_of_equipments = 7;
	int armor_number_of_skills = 8;
	sf::String armor_bonus_string = "+15% Damage";
	int armor_type_bonus = A_Damage;
	float armor_bonus = 15;

	virtual sf::String ReturnNameArmor();
	virtual int ReturnArmorLevelRequired() { return level; }
	 virtual sf::String ReturnArmorLevelRecommandedString();
	 virtual int ReturnArmorPrice();
	 virtual int ReturnAmorNumberGems();
	 virtual int ReturnArmorNumberEquipments();
	 virtual int ReturnArmorNumberSkills();
	 virtual sf::String ReturnArmorBonusString();
	 virtual int ReturnArmorBonusType();
	virtual  int ReturnArmorBonusNumber();

	A_RobeOfTheAncient(int current_language);
	~A_RobeOfTheAncient();
};

