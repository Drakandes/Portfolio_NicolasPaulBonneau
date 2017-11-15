#include "stdafx.h"
#include "A_BrokenArmor.h"

A_BrokenArmor::A_BrokenArmor(int current_language)
{
	name_armor = current_language == English_E ? "Broken armor" : "Armure brisée";
	armor_level_recommanded = current_language == English_E ? "Starting Armor" : "Armure de départ";
}

A_BrokenArmor::~A_BrokenArmor()
{
}

sf::String A_BrokenArmor::ReturnNameArmor()
{
	return name_armor;
}

sf::String A_BrokenArmor::ReturnArmorLevelRecommandedString()
{
	return armor_level_recommanded;
}

int A_BrokenArmor::ReturnArmorPrice()
{
	return armor_price;
}

int A_BrokenArmor::ReturnAmorNumberGems()
{
	return armor_number_of_gems;
}

int A_BrokenArmor::ReturnArmorNumberEquipments()
{
	return armor_number_of_equipments;
}

int A_BrokenArmor::ReturnArmorNumberSkills()
{
	return armor_number_of_skills;
}

sf::String A_BrokenArmor::ReturnArmorBonusString()
{
	return armor_bonus_string;
}

int A_BrokenArmor::ReturnArmorBonusType()
{
	return armor_type_bonus;
}

int A_BrokenArmor::ReturnArmorBonusNumber()
{
	return armor_bonus;
}
