#include "stdafx.h"
#include "E_Weapon.h"

E_Weapon::E_Weapon(int current_language, int current_save)
{
	language = current_language;
	this->current_save = current_save;
}

E_Weapon::~E_Weapon()
{
}

void E_Weapon::Init(int item_level_received, std::vector<int> listTypeBonus_received, std::vector<float> listBonus_received, std::vector<sf::Vector2f> listRangeBonus_received, std::vector<int> talent_bonuses, std::vector<int> talent_level_bonuses, int type_weapon_received, std::vector<sf::String> listTalentString_received, int id_item_received, int rarity)
{
	type_weapon = type_weapon_received;
	ListTalentBonuses = talent_bonuses;
	ListTalentLevelBonuses = talent_level_bonuses;
	item_level = item_level_received;
	listBonus = listBonus_received;
	listRangeBonus = listRangeBonus_received;
	listTypeBonus = listTypeBonus_received;
	number_bonus = listBonus_received.size();
	listTalentString = listTalentString_received;
	id_item = id_item_received;
	rarity_item = rarity;
}

float E_Weapon::GetBonusValue(int type_bonus)
{
	float bonus = 0;
	for (int i = 0; i < listTypeBonus.size(); i++)
	{
		if (listTypeBonus[i] == type_bonus)
		{
			bonus += listBonus[i];
		}
	}
	return bonus;
}

sf::String E_Weapon::GetStringBonus(int type_bonus)
{
	if (language == English_E)
	{
		switch (type_bonus)
		{
		case DamageAddition:
			return sf::String(" damage  ( ");

		case AttackSpeedPercent:
			return sf::String("% attack speed  ( ");

		case LifeSteal:
			return sf::String("% lifesteal  ( ");

		case HealthAddition:
			return sf::String(" maximum health  ( ");

		case DefenseAddition:
			return sf::String(" armor  ( ");

		case HpRecovery:
			return sf::String("  health per second  ( ");

		case MovementSpeedPercent:
			return sf::String("% movement speed  ( ");

		case CooldownReduction:
			return sf::String("% cooldown reduction  ( ");

		case StunReductionPercent:
			return sf::String("% stun reduction  ( ");
		}
	}
	else
	{
		switch (type_bonus)
		{
		case DamageAddition:
			return sf::String(" dégâts  ( ");

		case AttackSpeedPercent:
			return sf::String("% vitesse d'attaque  ( ");

		case LifeSteal:
			return sf::String("% vol de vie  ( ");

		case HealthAddition:
			return sf::String(" vie totale  ( ");

		case DefenseAddition:
			return sf::String(" armure  ( ");

		case HpRecovery:
			return sf::String("  vie par seconde  ( ");

		case MovementSpeedPercent:
			return sf::String("% vitesse de déplacement  ( ");

		case CooldownReduction:
			return sf::String("% temps de latence  ( ");

		case StunReductionPercent:
			return sf::String("% réduction des étourdissements  ( ");
		}
	}
}

std::vector<sf::String> E_Weapon::GetListStringEquipment()
{
	std::vector<sf::String> listString;
	for (int i = 0; i < number_bonus; i++)
	{
		sf::String string;
		string = ("+");
		string = GlobalFunction::InsertNumberToStringIfFloat(string, listBonus[i], string.getSize());
		string.insert(string.getSize(), GetStringBonus(listTypeBonus[i]));
		string = GlobalFunction::InsertNumberToStringIfFloat(string, listRangeBonus[i].x, string.getSize());
		string.insert(string.getSize(), sf::String(" - "));
		string = GlobalFunction::InsertNumberToStringIfFloat(string, listRangeBonus[i].y, string.getSize());
		string.insert(string.getSize(), sf::String(" )"));
		listString.push_back(string);
	}

	for (int i = 0; i < listTalentString.size(); i++)
	{
		listString.push_back(listTalentString[i]);
	}

	return listString;
}

void E_Weapon::SaveInformation(int id_ring1, int id_ring2, int id_weapon, int id_hat)
{
	std::ofstream myfile;

	if (current_save == FirstSave_E)
	{
		myfile.open("Weapons1.txt", std::fstream::app);
	}
	else if (current_save == SecondSave_E)
	{
		myfile.open("Weapons2.txt", std::fstream::app);
	}
	else
	{
		myfile.open("Weapons3.txt", std::fstream::app);
	}
	myfile.seekp(std::ios::end);
	myfile << "NewWeapon";
	myfile << std::endl;

	if (true)
	{
		myfile << "IdItem";
		myfile << std::endl;
		myfile << " < ";
		if (id_weapon == id_item)
		{
			myfile << "true";
			myfile << std::string(" ");
		}
		else
		{
			myfile << "false";
			myfile << std::string(" ");
		}
		myfile << " > ";
		myfile << std::endl;
	}

	myfile << "ListTalentBonuses";
	myfile << std::endl;
	myfile << " < ";
	for (int i = 0; i < ListTalentBonuses.size(); i++)
	{
		std::string str("" + std::to_string(ListTalentBonuses[i]));
		myfile << str;
		myfile << std::string(" ");
	}
	myfile << " > ";
	myfile << std::endl;

	myfile << "ListTalentLevelBonuses";
	myfile << std::endl;
	myfile << " < ";
	for (int i = 0; i < ListTalentLevelBonuses.size(); i++)
	{
		std::string str("" + std::to_string(ListTalentLevelBonuses[i]));
		myfile << str;
		myfile << std::string(" ");
	}
	myfile << " > ";
	myfile << std::endl;

	myfile << "listTypeBonus";
	myfile << std::endl;
	myfile << " < ";
	for (int i = 0; i < listTypeBonus.size(); i++)
	{
		std::string str("" + std::to_string(listTypeBonus[i]));
		myfile << str;
		myfile << std::string(" ");
	}
	myfile << " > ";
	myfile << std::endl;

	myfile << "listBonus";
	myfile << std::endl;
	myfile << " < ";
	for (int i = 0; i < listBonus.size(); i++)
	{
		std::string str("" + std::to_string(listBonus[i]));
		myfile << str;
		myfile << std::string(" ");
	}
	myfile << " > ";
	myfile << std::endl;

	myfile << "listRangeBonus";
	myfile << std::endl;
	myfile << " < ";
	for (int i = 0; i < listRangeBonus.size(); i++)
	{
		float x = listRangeBonus[i].x;
		std::string str("" + std::to_string(x));
		myfile << str;
		myfile << std::string(" ");
		float y = listRangeBonus[i].y;
		std::string str1("" + std::to_string(y));
		myfile << str1;
		myfile << std::string(" ");
	}
	myfile << " > ";
	myfile << std::endl;

	myfile << "listTalentString";
	myfile << std::endl;
	myfile << " < ";
	for (int i = 0; i < listTalentString.size(); i++)
	{
		myfile << listTalentString[i].toAnsiString();
		myfile << " ";
	}
	myfile << " > ";
	myfile << std::endl;

	if (true)
	{
		myfile << "item_level";
		myfile << std::endl;
		myfile << " < ";
		int number = item_level;
		std::string str("" + std::to_string(number));
		myfile << str;
		myfile << " ";
		myfile << " > ";
		myfile << std::endl;
	}

	if (true)
	{
		myfile << "type_weapon";
		myfile << std::endl;
		myfile << " < ";
		int number = type_weapon;
		std::string str("" + std::to_string(number));
		myfile << str;
		myfile << " ";
		myfile << " > ";
		myfile << std::endl;
	}

	if (true)
	{
		myfile << "RarityItem";
		myfile << std::endl;
		myfile << " < ";
		std::string str("" + std::to_string(rarity_item));
		myfile << str;
		myfile << std::string(" ");
		myfile << " > ";
		myfile << std::endl;
	}
}

int E_Weapon::GetRarityItem() 
{ 
	return rarity_item; 
}
