#pragma once
#include "EquipmentBase.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

class E_Weapon : public EquipmentBase
{
	int language;
	std::vector<int> ListTalentBonuses;
	std::vector<int> ListTalentLevelBonuses;
	std::vector<int> listTypeBonus;
	std::vector<float> listBonus;
	std::vector<sf::Vector2f> listRangeBonus;
	std::vector<sf::String> listTalentString;
	int item_level;
	int number_bonus;
	int type_weapon;
	int id_item;
	int current_save = NoSave_E;
	int rarity_item = Common_E;
public:
	E_Weapon(int current_language, int current_save);
	~E_Weapon();

	virtual int GetRarityItem();
	void Init(int item_level_received, std::vector<int> listTypeBonus_received, std::vector<float> listBonus_received, std::vector<sf::Vector2f> listRangeBonus_received, std::vector<int> talent_bonuses, std::vector<int> talent_level_bonuses, int type_weapon_received,std::vector<sf::String> listTalentString_received, int id_item_received,int rarity);
	virtual float GetBonusValue(int type_bonus);
	virtual int GetILvl() { return item_level; }
	virtual std::vector<int> GetListTalentIncreasement() { return ListTalentBonuses; }
	virtual int GetCategoryEquipment() { return WeaponEquipment_E; }
	virtual int GetTypeEquipment() { return type_weapon; }
	virtual std::vector<sf::String> GetListStringEquipment();
	virtual void SaveInformation(int id_ring1, int id_ring2, int id_weapon, int id_hat);
	virtual int GetIdEquipment() { return id_item; }
	sf::String GetStringBonus(int type_bonus);
};

