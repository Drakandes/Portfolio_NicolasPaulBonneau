#include "stdafx.h"
#include "A_RobeOfTheDevotee.h"


A_RobeOfTheDevotee::A_RobeOfTheDevotee(int current_language)
{
	name_armor = current_language == English_E ? "Robe of the devotee" : "Robe du Dévoué";
	armor_level_recommanded = current_language == English_E ? "Level 9 required" : "Niveau 9 requis";
}


A_RobeOfTheDevotee::~A_RobeOfTheDevotee()
{
}

sf::String A_RobeOfTheDevotee::ReturnNameArmor()
{
	return name_armor;
}

sf::String A_RobeOfTheDevotee::ReturnArmorLevelRecommandedString()
{
	return armor_level_recommanded;
}

int A_RobeOfTheDevotee::ReturnArmorPrice()
{
	return armor_price;
}

int A_RobeOfTheDevotee::ReturnAmorNumberGems()
{
	return armor_number_of_gems;
}

int A_RobeOfTheDevotee::ReturnArmorNumberEquipments()
{
	return armor_number_of_equipments;
}

int A_RobeOfTheDevotee::ReturnArmorNumberSkills()
{
	return armor_number_of_skills;
}

sf::String A_RobeOfTheDevotee::ReturnArmorBonusString()
{
	return armor_bonus_string;
}

int A_RobeOfTheDevotee::ReturnArmorBonusType()
{
	return armor_type_bonus;
}

int A_RobeOfTheDevotee::ReturnArmorBonusNumber()
{
	return armor_bonus;
}
