#include "stdafx.h"
#include "A_RobeOfTheCommander.h"


A_RobeOfTheCommander::A_RobeOfTheCommander(int current_language)
{
	name_armor = current_language == English_E ? "Robe of the Commander" : "Robe du Commandant";
	armor_level_recommanded = current_language == English_E ? "Level 14 required" : "Niveau 14 requis";
}


A_RobeOfTheCommander::~A_RobeOfTheCommander()
{
}

sf::String A_RobeOfTheCommander::ReturnNameArmor()
{
	return name_armor;
}

sf::String A_RobeOfTheCommander::ReturnArmorLevelRecommandedString()
{
	return armor_level_recommanded;
}

int A_RobeOfTheCommander::ReturnArmorPrice()
{
	return armor_price;
}

int A_RobeOfTheCommander::ReturnAmorNumberGems()
{
	return armor_number_of_gems;
}

int A_RobeOfTheCommander::ReturnArmorNumberEquipments()
{
	return armor_number_of_equipments;
}

int A_RobeOfTheCommander::ReturnArmorNumberSkills()
{
	return armor_number_of_skills;
}

sf::String A_RobeOfTheCommander::ReturnArmorBonusString()
{
	return armor_bonus_string;
}

int A_RobeOfTheCommander::ReturnArmorBonusType()
{
	return armor_type_bonus;
}

int A_RobeOfTheCommander::ReturnArmorBonusNumber()
{
	return armor_bonus;
}
