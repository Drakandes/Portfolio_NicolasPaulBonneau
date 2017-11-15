#include "stdafx.h"
#include "A_RobeOfTheDevoteePlus.h"


A_RobeOfTheDevoteePlus::A_RobeOfTheDevoteePlus(int current_language)
{
	name_armor = current_language == English_E ? "Robe of the devotee+" : "Robe du Dévoué+";
	armor_level_recommanded = current_language == English_E ? "Level 9 required" : "Niveau 9 requis";
}


A_RobeOfTheDevoteePlus::~A_RobeOfTheDevoteePlus()
{
}

sf::String A_RobeOfTheDevoteePlus::ReturnNameArmor()
{
	return name_armor;
}

sf::String A_RobeOfTheDevoteePlus::ReturnArmorLevelRecommandedString()
{
	return armor_level_recommanded;
}

int A_RobeOfTheDevoteePlus::ReturnArmorPrice()
{
	return armor_price;
}

int A_RobeOfTheDevoteePlus::ReturnAmorNumberGems()
{
	return armor_number_of_gems;
}

int A_RobeOfTheDevoteePlus::ReturnArmorNumberEquipments()
{
	return armor_number_of_equipments;
}

int A_RobeOfTheDevoteePlus::ReturnArmorNumberSkills()
{
	return armor_number_of_skills;
}

sf::String A_RobeOfTheDevoteePlus::ReturnArmorBonusString()
{
	return armor_bonus_string;
}

int A_RobeOfTheDevoteePlus::ReturnArmorBonusType()
{
	return armor_type_bonus;
}

int A_RobeOfTheDevoteePlus::ReturnArmorBonusNumber()
{
	return armor_bonus;
}
