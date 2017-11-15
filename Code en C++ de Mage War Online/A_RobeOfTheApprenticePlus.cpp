#include "stdafx.h"
#include "A_RobeOfTheApprenticePlus.h"


A_RobeOfTheApprenticePlus::A_RobeOfTheApprenticePlus(int current_language)
{
	name_armor = current_language == English_E ? "Robe of the apprentice+" : "Robe de l'Apprenti+";
	armor_level_recommanded = current_language == English_E ? "Level 7 required" : "Niveau 7 requis";
}


A_RobeOfTheApprenticePlus::~A_RobeOfTheApprenticePlus()
{
}

sf::String A_RobeOfTheApprenticePlus::ReturnNameArmor()
{
	return name_armor;
}

sf::String A_RobeOfTheApprenticePlus::ReturnArmorLevelRecommandedString()
{
	return armor_level_recommanded;
}

int A_RobeOfTheApprenticePlus::ReturnArmorPrice()
{
	return armor_price;
}

int A_RobeOfTheApprenticePlus::ReturnAmorNumberGems()
{
	return armor_number_of_gems;
}

int A_RobeOfTheApprenticePlus::ReturnArmorNumberEquipments()
{
	return armor_number_of_equipments;
}

int A_RobeOfTheApprenticePlus::ReturnArmorNumberSkills()
{
	return armor_number_of_skills;
}

sf::String A_RobeOfTheApprenticePlus::ReturnArmorBonusString()
{
	return armor_bonus_string;
}

int A_RobeOfTheApprenticePlus::ReturnArmorBonusType()
{
	return armor_type_bonus;
}

int A_RobeOfTheApprenticePlus::ReturnArmorBonusNumber()
{
	return armor_bonus;
}
