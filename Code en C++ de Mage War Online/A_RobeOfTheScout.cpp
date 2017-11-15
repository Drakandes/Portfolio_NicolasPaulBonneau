#include "stdafx.h"
#include "A_RobeOfTheScout.h"


A_RobeOfTheScout::A_RobeOfTheScout(int current_language)
{
	name_armor = current_language == English_E ? "Robe of the Scout" : "Robe du Scout";
	armor_level_recommanded = current_language == English_E ? "Level 19 required" : "Niveau 19 requis";
}


A_RobeOfTheScout::~A_RobeOfTheScout()
{
}

sf::String A_RobeOfTheScout::ReturnNameArmor()
{
	return name_armor;
}

sf::String A_RobeOfTheScout::ReturnArmorLevelRecommandedString()
{
	return armor_level_recommanded;
}

int A_RobeOfTheScout::ReturnArmorPrice()
{
	return armor_price;
}

int A_RobeOfTheScout::ReturnAmorNumberGems()
{
	return armor_number_of_gems;
}

int A_RobeOfTheScout::ReturnArmorNumberEquipments()
{
	return armor_number_of_equipments;
}

int A_RobeOfTheScout::ReturnArmorNumberSkills()
{
	return armor_number_of_skills;
}

sf::String A_RobeOfTheScout::ReturnArmorBonusString()
{
	return armor_bonus_string;
}

int A_RobeOfTheScout::ReturnArmorBonusType()
{
	return armor_type_bonus;
}

int A_RobeOfTheScout::ReturnArmorBonusNumber()
{
	return armor_bonus;
}
