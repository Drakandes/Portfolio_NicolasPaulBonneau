#include "stdafx.h"
#include "A_ArmorOfTheWandering.h"

A_ArmorOfTheWandering::A_ArmorOfTheWandering(int current_language)
{
	name_armor = current_language == English_E ? "Armor of the wandering" : "Armure de l'errant";
	armor_level_recommanded = current_language == English_E ? "Level 3 required" : "Niveau 3 requis";
}

A_ArmorOfTheWandering::~A_ArmorOfTheWandering()
{
}

sf::String A_ArmorOfTheWandering::ReturnNameArmor()
{
	return name_armor;
}

sf::String A_ArmorOfTheWandering::ReturnArmorLevelRecommandedString()
{
	return armor_level_recommanded;
}

int A_ArmorOfTheWandering::ReturnArmorPrice()
{
	return armor_price;
}

int A_ArmorOfTheWandering::ReturnAmorNumberGems()
{
	return armor_number_of_gems;
}

int A_ArmorOfTheWandering::ReturnArmorNumberEquipments()
{
	return armor_number_of_equipments;
}

int A_ArmorOfTheWandering::ReturnArmorNumberSkills()
{
	return armor_number_of_skills;
}

sf::String A_ArmorOfTheWandering::ReturnArmorBonusString()
{
	return armor_bonus_string;
}

int A_ArmorOfTheWandering::ReturnArmorBonusType()
{
	return armor_type_bonus;
}

int A_ArmorOfTheWandering::ReturnArmorBonusNumber()
{
	return armor_bonus;
}
