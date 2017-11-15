#include "stdafx.h"
#include "A_RobeOfTheScoutElite.h"


A_RobeOfTheScoutElite::A_RobeOfTheScoutElite(int current_language)
{
	name_armor = current_language == English_E ? "Robe of the scout elite" : "Robe du Scout elite";
	armor_level_recommanded = current_language == English_E ? "Level 21 required" : "Niveau 21 requis";
}


A_RobeOfTheScoutElite::~A_RobeOfTheScoutElite()
{
}

sf::String A_RobeOfTheScoutElite::ReturnNameArmor()
{
	return name_armor;
}

sf::String A_RobeOfTheScoutElite::ReturnArmorLevelRecommandedString()
{
	return armor_level_recommanded;
}

int A_RobeOfTheScoutElite::ReturnArmorPrice()
{
	return armor_price;
}

int A_RobeOfTheScoutElite::ReturnAmorNumberGems()
{
	return armor_number_of_gems;
}

int A_RobeOfTheScoutElite::ReturnArmorNumberEquipments()
{
	return armor_number_of_equipments;
}

int A_RobeOfTheScoutElite::ReturnArmorNumberSkills()
{
	return armor_number_of_skills;
}

sf::String A_RobeOfTheScoutElite::ReturnArmorBonusString()
{
	return armor_bonus_string;
}

int A_RobeOfTheScoutElite::ReturnArmorBonusType()
{
	return armor_type_bonus;
}

int A_RobeOfTheScoutElite::ReturnArmorBonusNumber()
{
	return armor_bonus;
}
