#include "stdafx.h"
#include "A_RobeOfTheAncientElite.h"


A_RobeOfTheAncientElite::A_RobeOfTheAncientElite(int current_language)
{
	name_armor = current_language == English_E ? "Robe of the ancient elite" : "Robe de l'Ancien elite";
	armor_level_recommanded = current_language == English_E ? "Level 21 required" : "Niveau 21 requis";
}


A_RobeOfTheAncientElite::~A_RobeOfTheAncientElite()
{
}

sf::String A_RobeOfTheAncientElite::ReturnNameArmor()
{
	return name_armor;
}

sf::String A_RobeOfTheAncientElite::ReturnArmorLevelRecommandedString()
{
	return armor_level_recommanded;
}

int A_RobeOfTheAncientElite::ReturnArmorPrice()
{
	return armor_price;
}

int A_RobeOfTheAncientElite::ReturnAmorNumberGems()
{
	return armor_number_of_gems;
}

int A_RobeOfTheAncientElite::ReturnArmorNumberEquipments()
{
	return armor_number_of_equipments;
}

int A_RobeOfTheAncientElite::ReturnArmorNumberSkills()
{
	return armor_number_of_skills;
}

sf::String A_RobeOfTheAncientElite::ReturnArmorBonusString()
{
	return armor_bonus_string;
}

int A_RobeOfTheAncientElite::ReturnArmorBonusType()
{
	return armor_type_bonus;
}

int A_RobeOfTheAncientElite::ReturnArmorBonusNumber()
{
	return armor_bonus;
}
