#include "stdafx.h"
#include "A_RobeOfTheCommanderPlus.h"


A_RobeOfTheCommanderPlus::A_RobeOfTheCommanderPlus(int current_language)
{
	name_armor = current_language == English_E ? "Robe of the Commander+" : "Robe du Commandant+";
	armor_level_recommanded = current_language == English_E ? "Level 14 required" : "Niveau 14 requis";
}


A_RobeOfTheCommanderPlus::~A_RobeOfTheCommanderPlus()
{
}

sf::String A_RobeOfTheCommanderPlus::ReturnNameArmor()
{
	return name_armor;
}

sf::String A_RobeOfTheCommanderPlus::ReturnArmorLevelRecommandedString()
{
	return armor_level_recommanded;
}

int A_RobeOfTheCommanderPlus::ReturnArmorPrice()
{
	return armor_price;
}

int A_RobeOfTheCommanderPlus::ReturnAmorNumberGems()
{
	return armor_number_of_gems;
}

int A_RobeOfTheCommanderPlus::ReturnArmorNumberEquipments()
{
	return armor_number_of_equipments;
}

int A_RobeOfTheCommanderPlus::ReturnArmorNumberSkills()
{
	return armor_number_of_skills;
}

sf::String A_RobeOfTheCommanderPlus::ReturnArmorBonusString()
{
	return armor_bonus_string;
}

int A_RobeOfTheCommanderPlus::ReturnArmorBonusType()
{
	return armor_type_bonus;
}

int A_RobeOfTheCommanderPlus::ReturnArmorBonusNumber()
{
	return armor_bonus;
}
