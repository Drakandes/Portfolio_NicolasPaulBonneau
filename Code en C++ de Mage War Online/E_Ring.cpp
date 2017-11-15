#include "stdafx.h"
#include "E_Ring.h"

E_Ring::E_Ring(int current_language, int current_save)
{
	language = current_language;
	this->current_save = current_save;
}

E_Ring::~E_Ring()
{
}

void E_Ring::Init(int item_level_received, std::vector<bool> listIfHaveBonus_received, std::vector<float> listBonus_received, std::vector<sf::Vector2f> listRangeBonus_received, int id_item_received, int rarity, int number_max_bonus)
{
	item_level = item_level_received;
	listBonus = listBonus_received;
	listRangeBonus = listRangeBonus_received;
	listIfHaveBonus = listIfHaveBonus_received;
	number_bonus = number_max_bonus;
	id_item = id_item_received;
	rarity_item = rarity;
}

sf::String E_Ring::GetStringBonus(int type_bonus)
{
	if (language == English_E)
	{
		switch (type_bonus)
		{
		case RingHpRecovery:
			return sf::String(" health per second  ( ");

		case RingHpPercentRevoery:
			return sf::String("% of maximum health per second  ( ");

		case RingMovementSpeedAddition:
			return sf::String(" movement speed  ( ");

		case RingDamagePercent:
			return sf::String("% damage  ( ");

		case RingDamageAddition:
			return sf::String(" to damage  ( ");

		case RingExperiencePercent:
			return sf::String("% experience  ( ");

		case RingHealthAddition:
			return sf::String(" health  ( ");

		case RingHealthPercent:
			return sf::String("% of maximum health  ( ");

		case RingArmorAddition:
			return sf::String(" armor  ( ");

		case RingArmorPercent:
			return sf::String("% armor  ( ");

		case RingCooldown:
			return sf::String("% cooldown reduction  ( ");

		case RingAttackSpeedPercent:
			return sf::String("% attack speed  ( ");

		case RingLifeSteal:
			return sf::String("% lifesteal  ( ");
		}
	}
	else
	{
		switch (type_bonus)
		{
		case RingHpRecovery:
			return sf::String(" de soins par seconde  ( ");

		case RingHpPercentRevoery:
			return sf::String("% de la vie totale en soins par seconde  ( ");

		case RingMovementSpeedAddition:
			return sf::String(" � la vitesse de d�placement  ( ");

		case RingDamagePercent:
			return sf::String("% de d�g�ts  ( ");

		case RingDamageAddition:
			return sf::String(" aux d�g�ts  ( ");

		case RingExperiencePercent:
			return sf::String("% d'exp�rience re�u  ( ");

		case RingHealthAddition:
			return sf::String(" � la vie totale  ( ");

		case RingHealthPercent:
			return sf::String("% de vie totale  ( ");

		case RingArmorAddition:
			return sf::String(" � l'armure  ( ");

		case RingArmorPercent:
			return sf::String("% d'armure  ( ");

		case RingCooldown:
			return sf::String("% de temps de latence  ( ");

		case RingAttackSpeedPercent:
			return sf::String("% de vitesse d'attaque  ( ");

		case RingLifeSteal:
			return sf::String("% de vol de vie  ( ");
		}
	}
}

std::vector<sf::String> E_Ring::GetListStringEquipment()
{
	std::vector<sf::String> listString;
	for (int i = 0; i < number_bonus; i++)
	{
		if (listIfHaveBonus[i])
		{
			sf::String string;
			string = ("+");
			string = GlobalFunction::InsertNumberToStringIfFloat(string, listBonus[i], string.getSize());
			string.insert(string.getSize(), GetStringBonus(i));
			string = GlobalFunction::InsertNumberToStringIfFloat(string, listRangeBonus[i].x, string.getSize());
			string.insert(string.getSize(), sf::String(" - "));
			string = GlobalFunction::InsertNumberToStringIfFloat(string, listRangeBonus[i].y, string.getSize());
			string.insert(string.getSize(), sf::String(" )"));
			listString.push_back(string);
		}
	}

	return listString;
}

void E_Ring::SaveInformation(int id_ring1, int id_ring2, int id_weapon, int id_hat)
{
	std::ofstream myfile;

	if (current_save == FirstSave_E)
	{
		myfile.open("Rings1.txt", std::fstream::app);
	}
	else if (current_save == SecondSave_E)
	{
		myfile.open("Rings2.txt", std::fstream::app);
	}
	else
	{
		myfile.open("Rings3.txt", std::fstream::app);
	}
	myfile.seekp(std::ios::end);
	myfile << "NewWeapon";
	myfile << std::endl;

	if (true)
	{
		myfile << "IdItem";
		myfile << std::endl;
		myfile << " < ";
		if (id_ring1 == id_item || id_ring2 == id_item)
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

	myfile << "listTypeBonus";
	myfile << std::endl;
	myfile << " < ";
	for (int i = 0; i < listIfHaveBonus.size(); i++)
	{
		if (listIfHaveBonus[i])
		{
			myfile << "true";
			myfile << std::string(" ");
		}
		else
		{
			myfile << "false";
			myfile << std::string(" ");
		}
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
		int number = type_ring;
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

	myfile.close();
}