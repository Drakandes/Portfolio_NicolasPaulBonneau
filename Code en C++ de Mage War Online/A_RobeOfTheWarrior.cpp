#include "stdafx.h"
#include "A_RobeOfTheWarrior.h"


A_RobeOfTheWarrior::A_RobeOfTheWarrior(int current_language)
{
	name_armor = current_language == English_E ? "Robe of the Warrior" : "Robe du Guerrier";
	armor_level_recommanded = current_language == English_E ? "Level 13 required" : "Niveau 13 requis";
}


A_RobeOfTheWarrior::~A_RobeOfTheWarrior()
{
}

sf::String A_RobeOfTheWarrior::ReturnNameArmor()
{
	return name_armor;
}

sf::String A_RobeOfTheWarrior::ReturnArmorLevelRecommandedString()
{
	return armor_level_recommanded;
}

int A_RobeOfTheWarrior::ReturnArmorPrice()
{
	return armor_price;
}

int A_RobeOfTheWarrior::ReturnAmorNumberGems()
{
	return armor_number_of_gems;
}

int A_RobeOfTheWarrior::ReturnArmorNumberEquipments()
{
	return armor_number_of_equipments;
}

int A_RobeOfTheWarrior::ReturnArmorNumberSkills()
{
	return armor_number_of_skills;
}

sf::String A_RobeOfTheWarrior::ReturnArmorBonusString()
{
	return armor_bonus_string;
}

int A_RobeOfTheWarrior::ReturnArmorBonusType()
{
	return armor_type_bonus;
}

int A_RobeOfTheWarrior::ReturnArmorBonusNumber()
{
	return armor_bonus;
}
