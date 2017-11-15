#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GlobalEnum.h"
#include "A_ArmorBase.h"

class A_BrokenArmor : public A_ArmorBase
{
private:
	int language;
	sf::String name_armor;
	sf::String armor_level_recommanded;
	int level = 1;
	int armor_price = 0;
	int armor_number_of_gems = 1;
	int armor_number_of_equipments = 0;
	int armor_number_of_skills = 3;
	sf::String armor_bonus_string = "+8 Hp/s";
	int armor_type_bonus = A_HealthPerSecond;
	int armor_bonus = 8;
public:
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

	A_BrokenArmor(int current_language);
	~A_BrokenArmor();
};

