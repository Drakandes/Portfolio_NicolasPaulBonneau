#include "stdafx.h"
#include "E_WizardHat.h"

E_WizardHat::E_WizardHat(int current_language, int current_save)
{
	language = current_language;
	this->current_save = current_save;
}

E_WizardHat::~E_WizardHat()
{
}

void E_WizardHat::Init(int item_level_received, std::vector<int> listTypeBonus_received, std::vector<float> listBonus_received, std::vector<sf::Vector2f> listRangeBonus_received, std::vector<int> SkillIncreasement, std::vector<int> SkillIncreasementLevel, std::vector<sf::String> listStringSkillBonus, int type_hat_received, int id_item_received, int rarity)
{
	ListSkillIncreasement = SkillIncreasement;
	ListSkillIncreasementLevel = SkillIncreasementLevel;
	item_level = item_level_received;
	listBonus = listBonus_received;
	listRangeBonus = listRangeBonus_received;
	listTypeBonus = listTypeBonus_received;
	number_bonus = listBonus_received.size();
	listStringSkillIncreasement = listStringSkillBonus;
	type_hat = type_hat_received;
	id_item = id_item_received;
	rarity_item = rarity;
}

float E_WizardHat::GetBonusValue(int type_bonus)
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

std::vector<int> E_WizardHat::GetListSkillIncreasement()
{ 
	return ListSkillIncreasement;
}

sf::String E_WizardHat::GetStringBonus(int type_bonus)
{
	if (language == English_E)
	{
		switch (type_bonus)
		{
		case DamagePerLevel:
			return sf::String("% of initial damage ");

		case AttackSpeedPerLevel:
			return sf::String("% of initial attack speed ");

		case HealthPerLevel:
			return sf::String("% of initial maximum health ");

		case ArmorPerLevel:
			return sf::String("% of initial armor ");

		case SpeedPerLevel:
			return sf::String("% of initial movement speed ");

		case CooldownRedutionPerLevel:
			return sf::String("% of initial cooldown reduction ");
		}
	}
	else
	{
		switch (type_bonus)
		{
		case DamagePerLevel:
			return sf::String("% des dégâts initiaux ");

		case AttackSpeedPerLevel:
			return sf::String("% de la vitesse d'attaque initiale ");

		case HealthPerLevel:
			return sf::String("% de la vie totale initiale ");

		case ArmorPerLevel:
			return sf::String("% de l'armure initiale ");

		case SpeedPerLevel:
			return sf::String("% de la vitesse de déplacement initiale ");

		case CooldownRedutionPerLevel:
			return sf::String("% du temps de latence initial ");
		}
	}
}

std::vector<sf::String> E_WizardHat::GetListStringEquipment()
{
	std::vector<sf::String> listString;
	for (int i = 0; i < number_bonus; i++)
	{
		sf::String string;
		string = ("+");
		string = GlobalFunction::InsertNumberToStringIfFloat(string, listBonus[i], string.getSize());
		string.insert(string.getSize(), GetStringBonus(listTypeBonus[i]));
		string.insert(string.getSize(), sf::String(" per level ("));
		string = GlobalFunction::InsertNumberToStringIfFloat(string, listRangeBonus[i].x, string.getSize());
		string.insert(string.getSize(), sf::String(" - "));
		string = GlobalFunction::InsertNumberToStringIfFloat(string, listRangeBonus[i].y, string.getSize());
		string.insert(string.getSize(), sf::String(" )"));
		listString.push_back(string);
	}

	for (int i = 0; i < listStringSkillIncreasement.size(); i++)
	{
		listString.push_back(listStringSkillIncreasement[i]);
	}

	return listString;
}

void E_WizardHat::SaveInformation(int id_ring1, int id_ring2, int id_weapon, int id_hat)
{
	std::ofstream myfile;

	if (current_save == FirstSave_E)
	{
		myfile.open("WizardHats1.txt", std::fstream::app);
	}
	else if (current_save == SecondSave_E)
	{
		myfile.open("WizardHats2.txt", std::fstream::app);
	}
	else
	{
		myfile.open("WizardHats3.txt", std::fstream::app);
	}
	myfile.seekp(std::ios::end);
	myfile << "NewWeapon";
	myfile << std::endl;

	if (true)
	{
		myfile << "IdItem";
		myfile << std::endl;
		myfile << " < ";
		if (id_hat == id_item)
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
	for (int i = 0; i < ListSkillIncreasement.size(); i++)
	{
		std::string str("" + std::to_string(ListSkillIncreasement[i]));
		myfile << str;
		myfile << std::string(" ");
	}
	myfile << " > ";
	myfile << std::endl;

	myfile << "ListTalentLevelBonuses";
	myfile << std::endl;
	myfile << " < ";
	for (int i = 0; i < ListSkillIncreasementLevel.size(); i++)
	{
		std::string str("" + std::to_string(ListSkillIncreasementLevel[i]));
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
	for (int i = 0; i < listStringSkillIncreasement.size(); i++)
	{
		myfile << listStringSkillIncreasement[i].toAnsiString();
		myfile << " . ";
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
		int number = type_hat;
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
