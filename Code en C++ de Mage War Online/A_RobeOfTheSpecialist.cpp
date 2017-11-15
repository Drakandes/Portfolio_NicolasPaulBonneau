#include "stdafx.h"
#include "A_RobeOfTheSpecialist.h"


A_RobeOfTheSpecialist::A_RobeOfTheSpecialist(int current_language)
{
	name_armor = current_language == English_E ? "Robe of the Specialist" : "Robe du Spécialiste";
	armor_level_recommanded = current_language == English_E ? "Level 19 required" : "Niveau 19 requis";
}


A_RobeOfTheSpecialist::~A_RobeOfTheSpecialist()
{
}

sf::String A_RobeOfTheSpecialist::ReturnNameArmor()
{
	return name_armor;
}

sf::String A_RobeOfTheSpecialist::ReturnArmorLevelRecommandedString()
{
	return armor_level_recommanded;
}

int A_RobeOfTheSpecialist::ReturnArmorPrice()
{
	return armor_price;
}

int A_RobeOfTheSpecialist::ReturnAmorNumberGems()
{
	return armor_number_of_gems;
}

int A_RobeOfTheSpecialist::ReturnArmorNumberEquipments()
{
	return armor_number_of_equipments;
}

int A_RobeOfTheSpecialist::ReturnArmorNumberSkills()
{
	return armor_number_of_skills;
}

sf::String A_RobeOfTheSpecialist::ReturnArmorBonusString()
{
	return armor_bonus_string;
}

int A_RobeOfTheSpecialist::ReturnArmorBonusType()
{
	return armor_type_bonus;
}

int A_RobeOfTheSpecialist::ReturnArmorBonusNumber()
{
	return armor_bonus;
}
