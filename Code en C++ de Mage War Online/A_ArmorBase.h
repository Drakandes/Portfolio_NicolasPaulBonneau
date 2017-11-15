#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GlobalEnum.h"

class A_ArmorBase
{
protected:
	int ArmorCost(int level_required);
public:
	sf::String name_armor = "Unknown";
	sf::String armor_level_recommanded = "Unknow";
	int armor_price = 0;
	int armor_number_of_gems = 0;
	int armor_number_of_equipments = 0;
	int armor_number_of_skills = 0;
	sf::String armor_bonus_string = "Nothing";
	int armor_type_bonus = Nothing;
	int armor_bonus = 0;

	virtual sf::String ReturnNameArmor();
	virtual sf::String ReturnArmorLevelRecommandedString();
	virtual int ReturnArmorLevelRequired() { return 22; }
	virtual int ReturnArmorPrice();
	virtual int ReturnAmorNumberGems();
	virtual int ReturnArmorNumberEquipments();
	virtual int ReturnArmorNumberSkills();
	virtual sf::String ReturnArmorBonusString();
	virtual int ReturnArmorBonusType();
	virtual int ReturnArmorBonusNumber();

	A_ArmorBase();
	~A_ArmorBase();
};

