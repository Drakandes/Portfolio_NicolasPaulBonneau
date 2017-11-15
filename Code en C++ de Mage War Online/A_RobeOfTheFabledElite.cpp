#include "stdafx.h"
#include "A_RobeOfTheFabledElite.h"


A_RobeOfTheFabledElite::A_RobeOfTheFabledElite(int current_language)
{
	name_armor = current_language == English_E ? "Robe of the Fabled elite" : "Robe du Fabuleux elite";
	armor_level_recommanded = current_language == English_E ? "Level 21 required" : "Niveau 21 requis";
}


A_RobeOfTheFabledElite::~A_RobeOfTheFabledElite()
{
}

sf::String A_RobeOfTheFabledElite::ReturnNameArmor()
{
	return name_armor;
}

sf::String A_RobeOfTheFabledElite::ReturnArmorLevelRecommandedString()
{
	return armor_level_recommanded;
}

int A_RobeOfTheFabledElite::ReturnArmorPrice()
{
	return armor_price;
}

int A_RobeOfTheFabledElite::ReturnAmorNumberGems()
{
	return armor_number_of_gems;
}

int A_RobeOfTheFabledElite::ReturnArmorNumberEquipments()
{
	return armor_number_of_equipments;
}

int A_RobeOfTheFabledElite::ReturnArmorNumberSkills()
{
	return armor_number_of_skills;
}

sf::String A_RobeOfTheFabledElite::ReturnArmorBonusString()
{
	return armor_bonus_string;
}

int A_RobeOfTheFabledElite::ReturnArmorBonusType()
{
	return armor_type_bonus;
}

int A_RobeOfTheFabledElite::ReturnArmorBonusNumber()
{
	return armor_bonus;
}
