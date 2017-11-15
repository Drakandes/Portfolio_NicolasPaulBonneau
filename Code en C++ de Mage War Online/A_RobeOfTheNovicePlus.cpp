#include "stdafx.h"
#include "A_RobeOfTheNovicePlus.h"


A_RobeOfTheNovicePlus::A_RobeOfTheNovicePlus(int current_language)
{
	name_armor = current_language == English_E ? "Robe of the Novice+" : "Robe du Novice+";
	armor_level_recommanded = current_language == English_E ? "Level 8 required" : "Niveau 8 requis";
}


A_RobeOfTheNovicePlus::~A_RobeOfTheNovicePlus()
{
}

sf::String A_RobeOfTheNovicePlus::ReturnNameArmor()
{
	return name_armor;
}

sf::String A_RobeOfTheNovicePlus::ReturnArmorLevelRecommandedString()
{
	return armor_level_recommanded;
}

int A_RobeOfTheNovicePlus::ReturnArmorPrice()
{
	return armor_price;
}

int A_RobeOfTheNovicePlus::ReturnAmorNumberGems()
{
	return armor_number_of_gems;
}

int A_RobeOfTheNovicePlus::ReturnArmorNumberEquipments()
{
	return armor_number_of_equipments;
}

int A_RobeOfTheNovicePlus::ReturnArmorNumberSkills()
{
	return armor_number_of_skills;
}

sf::String A_RobeOfTheNovicePlus::ReturnArmorBonusString()
{
	return armor_bonus_string;
}

int A_RobeOfTheNovicePlus::ReturnArmorBonusType()
{
	return armor_type_bonus;
}

int A_RobeOfTheNovicePlus::ReturnArmorBonusNumber()
{
	return armor_bonus;
}
