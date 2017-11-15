#include "stdafx.h"
#include "A_RobeOfTheMaster.h"


A_RobeOfTheMaster::A_RobeOfTheMaster(int current_language)
{
	name_armor = current_language == English_E ? "Robe of the Master" : "Robe du Maître";
	armor_level_recommanded = current_language == English_E ? "Level 19 required" : "Niveau 19 requis";
}


A_RobeOfTheMaster::~A_RobeOfTheMaster()
{
}

sf::String A_RobeOfTheMaster::ReturnNameArmor()
{
	return name_armor;
}

sf::String A_RobeOfTheMaster::ReturnArmorLevelRecommandedString()
{
	return armor_level_recommanded;
}

int A_RobeOfTheMaster::ReturnArmorPrice()
{
	return armor_price;
}

int A_RobeOfTheMaster::ReturnAmorNumberGems()
{
	return armor_number_of_gems;
}

int A_RobeOfTheMaster::ReturnArmorNumberEquipments()
{
	return armor_number_of_equipments;
}

int A_RobeOfTheMaster::ReturnArmorNumberSkills()
{
	return armor_number_of_skills;
}

sf::String A_RobeOfTheMaster::ReturnArmorBonusString()
{
	return armor_bonus_string;
}

int A_RobeOfTheMaster::ReturnArmorBonusType()
{
	return armor_type_bonus;
}

int A_RobeOfTheMaster::ReturnArmorBonusNumber()
{
	return armor_bonus;
}
