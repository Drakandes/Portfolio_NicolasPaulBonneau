#include "stdafx.h"
#include "A_RobeOfTheFabled.h"


A_RobeOfTheFabled::A_RobeOfTheFabled(int current_language)
{
	name_armor = current_language == English_E ? "Robe of the Fabled" : "Robe du Fabuleux";
	armor_level_recommanded = current_language == English_E ? "Level 19 required" : "Niveau 19 requis";
}


A_RobeOfTheFabled::~A_RobeOfTheFabled()
{
}

sf::String A_RobeOfTheFabled::ReturnNameArmor()
{
	return name_armor;
}

sf::String A_RobeOfTheFabled::ReturnArmorLevelRecommandedString()
{
	return armor_level_recommanded;
}

int A_RobeOfTheFabled::ReturnArmorPrice()
{
	return armor_price;
}

int A_RobeOfTheFabled::ReturnAmorNumberGems()
{
	return armor_number_of_gems;
}

int A_RobeOfTheFabled::ReturnArmorNumberEquipments()
{
	return armor_number_of_equipments;
}

int A_RobeOfTheFabled::ReturnArmorNumberSkills()
{
	return armor_number_of_skills;
}

sf::String A_RobeOfTheFabled::ReturnArmorBonusString()
{
	return armor_bonus_string;
}

int A_RobeOfTheFabled::ReturnArmorBonusType()
{
	return armor_type_bonus;
}

int A_RobeOfTheFabled::ReturnArmorBonusNumber()
{
	return armor_bonus;
}
