#include "stdafx.h"
#include "A_RobeOfTheSpecialistElite.h"


A_RobeOfTheSpecialistElite::A_RobeOfTheSpecialistElite(int current_language)
{
	name_armor = current_language == English_E ? "Robe of the Specialist elite" : "Robe du Spécialiste elite";
	armor_level_recommanded = current_language == English_E ? "Level 21 required" : "Niveau 21 requis";
}


A_RobeOfTheSpecialistElite::~A_RobeOfTheSpecialistElite()
{
}

sf::String A_RobeOfTheSpecialistElite::ReturnNameArmor()
{
	return name_armor;
}

sf::String A_RobeOfTheSpecialistElite::ReturnArmorLevelRecommandedString()
{
	return armor_level_recommanded;
}

int A_RobeOfTheSpecialistElite::ReturnArmorPrice()
{
	return armor_price;
}

int A_RobeOfTheSpecialistElite::ReturnAmorNumberGems()
{
	return armor_number_of_gems;
}

int A_RobeOfTheSpecialistElite::ReturnArmorNumberEquipments()
{
	return armor_number_of_equipments;
}

int A_RobeOfTheSpecialistElite::ReturnArmorNumberSkills()
{
	return armor_number_of_skills;
}

sf::String A_RobeOfTheSpecialistElite::ReturnArmorBonusString()
{
	return armor_bonus_string;
}

int A_RobeOfTheSpecialistElite::ReturnArmorBonusType()
{
	return armor_type_bonus;
}

int A_RobeOfTheSpecialistElite::ReturnArmorBonusNumber()
{
	return armor_bonus;
}
