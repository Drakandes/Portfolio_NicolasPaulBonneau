#include "stdafx.h"
#include "A_RobeOfTheAcclaimedPlus.h"


A_RobeOfTheAcclaimedPlus::A_RobeOfTheAcclaimedPlus(int current_language)
{
	name_armor = current_language == English_E ? "Robe of the Acclaimed+" : "Robe de l'Acclamé+";
	armor_level_recommanded = current_language == English_E ? "Level 10 required" : "Niveau 10 requis";
}


A_RobeOfTheAcclaimedPlus::~A_RobeOfTheAcclaimedPlus()
{
}

sf::String A_RobeOfTheAcclaimedPlus::ReturnNameArmor()
{
	return name_armor;
}

sf::String A_RobeOfTheAcclaimedPlus::ReturnArmorLevelRecommandedString()
{
	return armor_level_recommanded;
}

int A_RobeOfTheAcclaimedPlus::ReturnArmorPrice()
{
	return armor_price;
}

int A_RobeOfTheAcclaimedPlus::ReturnAmorNumberGems()
{
	return armor_number_of_gems;
}

int A_RobeOfTheAcclaimedPlus::ReturnArmorNumberEquipments()
{
	return armor_number_of_equipments;
}

int A_RobeOfTheAcclaimedPlus::ReturnArmorNumberSkills()
{
	return armor_number_of_skills;
}

sf::String A_RobeOfTheAcclaimedPlus::ReturnArmorBonusString()
{
	return armor_bonus_string;
}

int A_RobeOfTheAcclaimedPlus::ReturnArmorBonusType()
{
	return armor_type_bonus;
}

int A_RobeOfTheAcclaimedPlus::ReturnArmorBonusNumber()
{
	return armor_bonus;
}
