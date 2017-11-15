#include "stdafx.h"
#include "A_RobeOfTheWarriorPlus.h"


A_RobeOfTheWarriorPlus::A_RobeOfTheWarriorPlus(int current_language)
{
	name_armor = current_language == English_E ? "Robe of the Warrior+" : "Robe du Guerrier+";
	armor_level_recommanded = current_language == English_E ? "Level 13 required" : "Niveau 13 requis";
}


A_RobeOfTheWarriorPlus::~A_RobeOfTheWarriorPlus()
{
}

sf::String A_RobeOfTheWarriorPlus::ReturnNameArmor()
{
	return name_armor;
}

sf::String A_RobeOfTheWarriorPlus::ReturnArmorLevelRecommandedString()
{
	return armor_level_recommanded;
}

int A_RobeOfTheWarriorPlus::ReturnArmorPrice()
{
	return armor_price;
}

int A_RobeOfTheWarriorPlus::ReturnAmorNumberGems()
{
	return armor_number_of_gems;
}

int A_RobeOfTheWarriorPlus::ReturnArmorNumberEquipments()
{
	return armor_number_of_equipments;
}

int A_RobeOfTheWarriorPlus::ReturnArmorNumberSkills()
{
	return armor_number_of_skills;
}

sf::String A_RobeOfTheWarriorPlus::ReturnArmorBonusString()
{
	return armor_bonus_string;
}

int A_RobeOfTheWarriorPlus::ReturnArmorBonusType()
{
	return armor_type_bonus;
}

int A_RobeOfTheWarriorPlus::ReturnArmorBonusNumber()
{
	return armor_bonus;
}
