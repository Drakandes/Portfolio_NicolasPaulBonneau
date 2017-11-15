#include "stdafx.h"
#include "A_RobeOfTheNovice.h"


A_RobeOfTheNovice::A_RobeOfTheNovice(int current_language)
{
	name_armor = current_language == English_E ? "Robe of the Novice" : "Robe du Novice";
	armor_level_recommanded = current_language == English_E ? "Level 8 required" : "Niveau 8 requis";
}


A_RobeOfTheNovice::~A_RobeOfTheNovice()
{
}

sf::String A_RobeOfTheNovice::ReturnNameArmor()
{
	return name_armor;
}

sf::String A_RobeOfTheNovice::ReturnArmorLevelRecommandedString()
{
	return armor_level_recommanded;
}

int A_RobeOfTheNovice::ReturnArmorPrice()
{
	return armor_price;
}

int A_RobeOfTheNovice::ReturnAmorNumberGems()
{
	return armor_number_of_gems;
}

int A_RobeOfTheNovice::ReturnArmorNumberEquipments()
{
	return armor_number_of_equipments;
}

int A_RobeOfTheNovice::ReturnArmorNumberSkills()
{
	return armor_number_of_skills;
}

sf::String A_RobeOfTheNovice::ReturnArmorBonusString()
{
	return armor_bonus_string;
}

int A_RobeOfTheNovice::ReturnArmorBonusType()
{
	return armor_type_bonus;
}

int A_RobeOfTheNovice::ReturnArmorBonusNumber()
{
	return armor_bonus;
}
