#include "stdafx.h"
#include "A_RobeOfTheExpert.h"


A_RobeOfTheExpert::A_RobeOfTheExpert(int current_language)
{
	name_armor = current_language == English_E ? "Robe of the Expert" : "Robe de l'Expert";
	armor_level_recommanded = current_language == English_E ? "Level 16 required" : "Niveau 16 requis";
}


A_RobeOfTheExpert::~A_RobeOfTheExpert()
{
}

sf::String A_RobeOfTheExpert::ReturnNameArmor()
{
	return name_armor;
}

sf::String A_RobeOfTheExpert::ReturnArmorLevelRecommandedString()
{
	return armor_level_recommanded;
}

int A_RobeOfTheExpert::ReturnArmorPrice()
{
	return armor_price;
}

int A_RobeOfTheExpert::ReturnAmorNumberGems()
{
	return armor_number_of_gems;
}

int A_RobeOfTheExpert::ReturnArmorNumberEquipments()
{
	return armor_number_of_equipments;
}

int A_RobeOfTheExpert::ReturnArmorNumberSkills()
{
	return armor_number_of_skills;
}

sf::String A_RobeOfTheExpert::ReturnArmorBonusString()
{
	return armor_bonus_string;
}

int A_RobeOfTheExpert::ReturnArmorBonusType()
{
	return armor_type_bonus;
}

int A_RobeOfTheExpert::ReturnArmorBonusNumber()
{
	return armor_bonus;
}
