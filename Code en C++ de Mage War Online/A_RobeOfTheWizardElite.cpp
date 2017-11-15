#include "stdafx.h"
#include "A_RobeOfTheWizardElite.h"


A_RobeOfTheWizardElite::A_RobeOfTheWizardElite(int current_language)
{
	name_armor = current_language == English_E ? "Robe of the Wizard elite" : "Robe du Magicien elite";
	armor_level_recommanded = current_language == English_E ? "Level 21 required" : "Niveau 21 requis";
}


A_RobeOfTheWizardElite::~A_RobeOfTheWizardElite()
{
}

sf::String A_RobeOfTheWizardElite::ReturnNameArmor()
{
	return name_armor;
}

sf::String A_RobeOfTheWizardElite::ReturnArmorLevelRecommandedString()
{
	return armor_level_recommanded;
}

int A_RobeOfTheWizardElite::ReturnArmorPrice()
{
	return armor_price;
}

int A_RobeOfTheWizardElite::ReturnAmorNumberGems()
{
	return armor_number_of_gems;
}

int A_RobeOfTheWizardElite::ReturnArmorNumberEquipments()
{
	return armor_number_of_equipments;
}

int A_RobeOfTheWizardElite::ReturnArmorNumberSkills()
{
	return armor_number_of_skills;
}

sf::String A_RobeOfTheWizardElite::ReturnArmorBonusString()
{
	return armor_bonus_string;
}

int A_RobeOfTheWizardElite::ReturnArmorBonusType()
{
	return armor_type_bonus;
}

int A_RobeOfTheWizardElite::ReturnArmorBonusNumber()
{
	return armor_bonus;
}
