#include "stdafx.h"
#include "A_RobeOfTheExpertPlus.h"


A_RobeOfTheExpertPlus::A_RobeOfTheExpertPlus(int current_language)
{
	name_armor = current_language == English_E ? "Robe of the expert+" : "Robe de l'Expert+";
	armor_level_recommanded =current_language == English_E ? "Level 16 required" : "Niveau 16 requis";
}


A_RobeOfTheExpertPlus::~A_RobeOfTheExpertPlus()
{
}

sf::String A_RobeOfTheExpertPlus::ReturnNameArmor()
{
	return name_armor;
}

sf::String A_RobeOfTheExpertPlus::ReturnArmorLevelRecommandedString()
{
	return armor_level_recommanded;
}

int A_RobeOfTheExpertPlus::ReturnArmorPrice()
{
	return armor_price;
}

int A_RobeOfTheExpertPlus::ReturnAmorNumberGems()
{
	return armor_number_of_gems;
}

int A_RobeOfTheExpertPlus::ReturnArmorNumberEquipments()
{
	return armor_number_of_equipments;
}

int A_RobeOfTheExpertPlus::ReturnArmorNumberSkills()
{
	return armor_number_of_skills;
}

sf::String A_RobeOfTheExpertPlus::ReturnArmorBonusString()
{
	return armor_bonus_string;
}

int A_RobeOfTheExpertPlus::ReturnArmorBonusType()
{
	return armor_type_bonus;
}

int A_RobeOfTheExpertPlus::ReturnArmorBonusNumber()
{
	return armor_bonus;
}
