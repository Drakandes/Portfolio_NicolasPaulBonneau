#include "stdafx.h"
#include "A_RobeOfTheAncient.h"


A_RobeOfTheAncient::A_RobeOfTheAncient(int current_language)
{
	name_armor = current_language == English_E ? "Robe of the Ancient" : "Robe de l'Ancien";
	armor_level_recommanded = current_language == English_E ? "Level 19 required" : "Niveau 19 requis";
}


A_RobeOfTheAncient::~A_RobeOfTheAncient()
{
}

sf::String A_RobeOfTheAncient::ReturnNameArmor()
{
	return name_armor;
}

sf::String A_RobeOfTheAncient::ReturnArmorLevelRecommandedString()
{
	return armor_level_recommanded;
}

int A_RobeOfTheAncient::ReturnArmorPrice()
{
	return armor_price;
}

int A_RobeOfTheAncient::ReturnAmorNumberGems()
{
	return armor_number_of_gems;
}

int A_RobeOfTheAncient::ReturnArmorNumberEquipments()
{
	return armor_number_of_equipments;
}

int A_RobeOfTheAncient::ReturnArmorNumberSkills()
{
	return armor_number_of_skills;
}

sf::String A_RobeOfTheAncient::ReturnArmorBonusString()
{
	return armor_bonus_string;
}

int A_RobeOfTheAncient::ReturnArmorBonusType()
{
	return armor_type_bonus;
}

int A_RobeOfTheAncient::ReturnArmorBonusNumber()
{
	return armor_bonus;
}
