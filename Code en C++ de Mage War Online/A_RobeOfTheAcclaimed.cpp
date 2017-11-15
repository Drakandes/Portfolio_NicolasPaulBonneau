#include "stdafx.h"
#include "A_RobeOfTheAcclaimed.h"


A_RobeOfTheAcclaimed::A_RobeOfTheAcclaimed(int current_language)
{
	name_armor = current_language == English_E ? "Robe of the Acclaimed" : "Robe de l'Acclamé";
	armor_level_recommanded = current_language == English_E ? "Level 10 required" : "Niveau 10 requis";
}


A_RobeOfTheAcclaimed::~A_RobeOfTheAcclaimed()
{
}

sf::String A_RobeOfTheAcclaimed::ReturnNameArmor()
{
	return name_armor;
}

sf::String A_RobeOfTheAcclaimed::ReturnArmorLevelRecommandedString()
{
	return armor_level_recommanded;
}

int A_RobeOfTheAcclaimed::ReturnArmorPrice()
{
	return armor_price;
}

int A_RobeOfTheAcclaimed::ReturnAmorNumberGems()
{
	return armor_number_of_gems;
}

int A_RobeOfTheAcclaimed::ReturnArmorNumberEquipments()
{
	return armor_number_of_equipments;
}

int A_RobeOfTheAcclaimed::ReturnArmorNumberSkills()
{
	return armor_number_of_skills;
}

sf::String A_RobeOfTheAcclaimed::ReturnArmorBonusString()
{
	return armor_bonus_string;
}

int A_RobeOfTheAcclaimed::ReturnArmorBonusType()
{
	return armor_type_bonus;
}

int A_RobeOfTheAcclaimed::ReturnArmorBonusNumber()
{
	return armor_bonus;
}
