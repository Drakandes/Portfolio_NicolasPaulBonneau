#include "stdafx.h"
#include "A_RobeOfTheApprentice.h"


A_RobeOfTheApprentice::A_RobeOfTheApprentice(int current_language)
{
	name_armor = current_language == English_E ? "Robe of the Apprentice" : "Robe de l'Apprenti";
	armor_level_recommanded = current_language == English_E ? "Level 7 required" : "Niveau 7 requis";
}


A_RobeOfTheApprentice::~A_RobeOfTheApprentice()
{
}

sf::String A_RobeOfTheApprentice::ReturnNameArmor()
{
	return name_armor;
}

sf::String A_RobeOfTheApprentice::ReturnArmorLevelRecommandedString()
{
	return armor_level_recommanded;
}

int A_RobeOfTheApprentice::ReturnArmorPrice()
{
	return armor_price;
}

int A_RobeOfTheApprentice::ReturnAmorNumberGems()
{
	return armor_number_of_gems;
}

int A_RobeOfTheApprentice::ReturnArmorNumberEquipments()
{
	return armor_number_of_equipments;
}

int A_RobeOfTheApprentice::ReturnArmorNumberSkills()
{
	return armor_number_of_skills;
}

sf::String A_RobeOfTheApprentice::ReturnArmorBonusString()
{
	return armor_bonus_string;
}

int A_RobeOfTheApprentice::ReturnArmorBonusType()
{
	return armor_type_bonus;
}

int A_RobeOfTheApprentice::ReturnArmorBonusNumber()
{
	return armor_bonus;
}
