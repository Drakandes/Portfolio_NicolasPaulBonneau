#include "stdafx.h"
#include "A_RobeOfTheChief.h"


A_RobeOfTheChief::A_RobeOfTheChief(int current_language)
{
	name_armor = current_language == English_E ? "Robe of the chief" : "Robe du Chef";
	armor_level_recommanded = current_language == English_E ? "Level 15 required" : "Niveau 15 requis";
}


A_RobeOfTheChief::~A_RobeOfTheChief()
{
}

sf::String A_RobeOfTheChief::ReturnNameArmor()
{
	return name_armor;
}

sf::String A_RobeOfTheChief::ReturnArmorLevelRecommandedString()
{
	return armor_level_recommanded;
}

int A_RobeOfTheChief::ReturnArmorPrice()
{
	return armor_price;
}

int A_RobeOfTheChief::ReturnAmorNumberGems()
{
	return armor_number_of_gems;
}

int A_RobeOfTheChief::ReturnArmorNumberEquipments()
{
	return armor_number_of_equipments;
}

int A_RobeOfTheChief::ReturnArmorNumberSkills()
{
	return armor_number_of_skills;
}

sf::String A_RobeOfTheChief::ReturnArmorBonusString()
{
	return armor_bonus_string;
}

int A_RobeOfTheChief::ReturnArmorBonusType()
{
	return armor_type_bonus;
}

int A_RobeOfTheChief::ReturnArmorBonusNumber()
{
	return armor_bonus;
}
