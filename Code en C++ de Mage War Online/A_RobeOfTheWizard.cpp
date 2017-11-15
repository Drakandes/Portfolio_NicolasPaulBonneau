#include "stdafx.h"
#include "A_RobeOfTheWizard.h"


A_RobeOfTheWizard::A_RobeOfTheWizard(int current_language)
{
	name_armor = current_language == English_E ? "Robe of the Wizard" : "Robe du Magicien";
	armor_level_recommanded = current_language == English_E ? "Level 19 required" : "Niveau 19 requis";
}


A_RobeOfTheWizard::~A_RobeOfTheWizard()
{
}

sf::String A_RobeOfTheWizard::ReturnNameArmor()
{
	return name_armor;
}

sf::String A_RobeOfTheWizard::ReturnArmorLevelRecommandedString()
{
	return armor_level_recommanded;
}

int A_RobeOfTheWizard::ReturnArmorPrice()
{
	return armor_price;
}

int A_RobeOfTheWizard::ReturnAmorNumberGems()
{
	return armor_number_of_gems;
}

int A_RobeOfTheWizard::ReturnArmorNumberEquipments()
{
	return armor_number_of_equipments;
}

int A_RobeOfTheWizard::ReturnArmorNumberSkills()
{
	return armor_number_of_skills;
}

sf::String A_RobeOfTheWizard::ReturnArmorBonusString()
{
	return armor_bonus_string;
}

int A_RobeOfTheWizard::ReturnArmorBonusType()
{
	return armor_type_bonus;
}

int A_RobeOfTheWizard::ReturnArmorBonusNumber()
{
	return armor_bonus;
}
