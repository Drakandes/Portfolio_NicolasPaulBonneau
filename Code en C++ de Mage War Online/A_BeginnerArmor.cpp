#include "stdafx.h"
#include "A_BeginnerArmor.h"


A_BeginnerArmor::A_BeginnerArmor(int current_language)
{
    name_armor = current_language == English_E ? "Beginner armor" : "Armure du Débutant";
	armor_level_recommanded = current_language == English_E ? "Level 5 required" : "Niveau 5 requis";
}


A_BeginnerArmor::~A_BeginnerArmor()
{
}
sf::String A_BeginnerArmor::ReturnNameArmor()
{
	return name_armor;
}

sf::String A_BeginnerArmor::ReturnArmorLevelRecommandedString()
{
	return armor_level_recommanded;
}

int A_BeginnerArmor::ReturnArmorPrice()
{
	return armor_price;
}

int A_BeginnerArmor::ReturnAmorNumberGems()
{
	return armor_number_of_gems;
}

int A_BeginnerArmor::ReturnArmorNumberEquipments()
{
	return armor_number_of_equipments;
}

int A_BeginnerArmor::ReturnArmorNumberSkills()
{
	return armor_number_of_skills;
}

sf::String A_BeginnerArmor::ReturnArmorBonusString()
{
	return armor_bonus_string;
}

int A_BeginnerArmor::ReturnArmorBonusType()
{
	return armor_type_bonus;
}

int A_BeginnerArmor::ReturnArmorBonusNumber()
{
	return armor_bonus;
}
