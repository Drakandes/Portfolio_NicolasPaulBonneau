#include "stdafx.h"
#include "A_RobeOfTheHunter.h"


A_RobeOfTheHunter::A_RobeOfTheHunter(int current_language)
{
	name_armor = current_language == English_E ? "Robe of the hunter" : "Robe du Chasseur";
armor_level_recommanded = current_language == English_E ? "Level 11 required" : "Niveau 11 requis";
}


A_RobeOfTheHunter::~A_RobeOfTheHunter()
{
}

sf::String A_RobeOfTheHunter::ReturnNameArmor()
{
	return name_armor;
}

sf::String A_RobeOfTheHunter::ReturnArmorLevelRecommandedString()
{
	return armor_level_recommanded;
}

int A_RobeOfTheHunter::ReturnArmorPrice()
{
	return armor_price;
}

int A_RobeOfTheHunter::ReturnAmorNumberGems()
{
	return armor_number_of_gems;
}

int A_RobeOfTheHunter::ReturnArmorNumberEquipments()
{
	return armor_number_of_equipments;
}

int A_RobeOfTheHunter::ReturnArmorNumberSkills()
{
	return armor_number_of_skills;
}

sf::String A_RobeOfTheHunter::ReturnArmorBonusString()
{
	return armor_bonus_string;
}

int A_RobeOfTheHunter::ReturnArmorBonusType()
{
	return armor_type_bonus;
}

int A_RobeOfTheHunter::ReturnArmorBonusNumber()
{
	return armor_bonus;
}
