#include "stdafx.h"
#include "A_RobeOfTheGuardian.h"


A_RobeOfTheGuardian::A_RobeOfTheGuardian(int current_language)
{
	name_armor = current_language == English_E ? "Robe of the Guardian" : "Robe du Gardien";
	armor_level_recommanded = current_language == English_E ? "Level 17 required" : "Niveau 17 requis";
}


A_RobeOfTheGuardian::~A_RobeOfTheGuardian()
{
}

sf::String A_RobeOfTheGuardian::ReturnNameArmor()
{
	return name_armor;
}

sf::String A_RobeOfTheGuardian::ReturnArmorLevelRecommandedString()
{
	return armor_level_recommanded;
}

int A_RobeOfTheGuardian::ReturnArmorPrice()
{
	return armor_price;
}

int A_RobeOfTheGuardian::ReturnAmorNumberGems()
{
	return armor_number_of_gems;
}

int A_RobeOfTheGuardian::ReturnArmorNumberEquipments()
{
	return armor_number_of_equipments;
}

int A_RobeOfTheGuardian::ReturnArmorNumberSkills()
{
	return armor_number_of_skills;
}

sf::String A_RobeOfTheGuardian::ReturnArmorBonusString()
{
	return armor_bonus_string;
}

int A_RobeOfTheGuardian::ReturnArmorBonusType()
{
	return armor_type_bonus;
}

int A_RobeOfTheGuardian::ReturnArmorBonusNumber()
{
	return armor_bonus;
}
