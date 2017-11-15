#include "stdafx.h"
#include "A_ArmorBase.h"

A_ArmorBase::A_ArmorBase()
{
}

A_ArmorBase::~A_ArmorBase()
{
}

sf::String A_ArmorBase::ReturnNameArmor()
{
	return name_armor;
}

sf::String A_ArmorBase::ReturnArmorLevelRecommandedString()
{
	return armor_level_recommanded;
}

int A_ArmorBase::ReturnArmorPrice()
{
	return armor_price;
}

int A_ArmorBase::ReturnAmorNumberGems()
{
	return armor_number_of_gems;
}

int A_ArmorBase::ReturnArmorNumberEquipments()
{
	return armor_number_of_equipments;
}

int A_ArmorBase::ReturnArmorNumberSkills()
{
	return armor_number_of_skills;
}

sf::String A_ArmorBase::ReturnArmorBonusString()
{
	return armor_bonus_string;
}

int A_ArmorBase::ReturnArmorBonusType()
{
	return armor_type_bonus;
}

int A_ArmorBase::ReturnArmorBonusNumber()
{
	return armor_bonus;
}

int A_ArmorBase::ArmorCost(int level_required)
{
	switch (level_required)
	{
	case 3:
		return 24000;
		break;
	case 5:
		return 50000;
		break;
	case 7:
		return 84000;
		break;
	case 8:
		return 126000;
		break;
	case 9:
		return 170000;
		break;
	case 10:
		return 224000;
		break;
	case 11:
		return 296000;
		break;
	case 13:
		return 396000;
		break;
	case 14:
		return 512000;
		break;
	case 15:
		return 785000;
		break;
	case 16:
		return 904000;
		break;
	case 17:
		return 1156000;
		break;
	case 19:
		return 1403000;
		break;
	case 21:
		return 1967000;
	}
}
