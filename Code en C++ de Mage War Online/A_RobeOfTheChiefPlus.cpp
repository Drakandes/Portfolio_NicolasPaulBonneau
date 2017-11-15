#include "stdafx.h"
#include "A_RobeOfTheChiefPlus.h"


A_RobeOfTheChiefPlus::A_RobeOfTheChiefPlus(int current_language)
{
	name_armor = current_language == English_E ? "Robe of the chief+" : "Robe du Chef+";
	armor_level_recommanded = current_language == English_E ? "Level 15 required" : "Niveau 15 requis";
}


A_RobeOfTheChiefPlus::~A_RobeOfTheChiefPlus()
{
}

sf::String A_RobeOfTheChiefPlus::ReturnNameArmor()
{
	return name_armor;
}

sf::String A_RobeOfTheChiefPlus::ReturnArmorLevelRecommandedString()
{
	return armor_level_recommanded;
}

int A_RobeOfTheChiefPlus::ReturnArmorPrice()
{
	return armor_price;
}

int A_RobeOfTheChiefPlus::ReturnAmorNumberGems()
{
	return armor_number_of_gems;
}

int A_RobeOfTheChiefPlus::ReturnArmorNumberEquipments()
{
	return armor_number_of_equipments;
}

int A_RobeOfTheChiefPlus::ReturnArmorNumberSkills()
{
	return armor_number_of_skills;
}

sf::String A_RobeOfTheChiefPlus::ReturnArmorBonusString()
{
	return armor_bonus_string;
}

int A_RobeOfTheChiefPlus::ReturnArmorBonusType()
{
	return armor_type_bonus;
}

int A_RobeOfTheChiefPlus::ReturnArmorBonusNumber()
{
	return armor_bonus;
}
