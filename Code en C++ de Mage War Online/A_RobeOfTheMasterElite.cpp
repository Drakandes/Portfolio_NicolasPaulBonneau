#include "stdafx.h"
#include "A_RobeOfTheMasterElite.h"


A_RobeOfTheMasterElite::A_RobeOfTheMasterElite(int current_language)
{
	name_armor = current_language == English_E ? "Robe of the Master elite" : "Robe du Maître elite";
	armor_level_recommanded = current_language == English_E ? "Level 21 required" : "Niveau 21 requis";
}


A_RobeOfTheMasterElite::~A_RobeOfTheMasterElite()
{
}

sf::String A_RobeOfTheMasterElite::ReturnNameArmor()
{
	return name_armor;
}

sf::String A_RobeOfTheMasterElite::ReturnArmorLevelRecommandedString()
{
	return armor_level_recommanded;
}

int A_RobeOfTheMasterElite::ReturnArmorPrice()
{
	return armor_price;
}

int A_RobeOfTheMasterElite::ReturnAmorNumberGems()
{
	return armor_number_of_gems;
}

int A_RobeOfTheMasterElite::ReturnArmorNumberEquipments()
{
	return armor_number_of_equipments;
}

int A_RobeOfTheMasterElite::ReturnArmorNumberSkills()
{
	return armor_number_of_skills;
}

sf::String A_RobeOfTheMasterElite::ReturnArmorBonusString()
{
	return armor_bonus_string;
}

int A_RobeOfTheMasterElite::ReturnArmorBonusType()
{
	return armor_type_bonus;
}

int A_RobeOfTheMasterElite::ReturnArmorBonusNumber()
{
	return armor_bonus;
}
