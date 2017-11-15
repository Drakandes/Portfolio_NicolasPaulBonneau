#pragma once
#include "EquipmentBase.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

class E_WizardHat : public EquipmentBase
{
	int language;
	std::vector<int> ListSkillIncreasement;
	std::vector<int> ListSkillIncreasementLevel;
	std::vector<int> listTypeBonus;
	std::vector<float> listBonus;
	std::vector<sf::Vector2f> listRangeBonus;
	std::vector<sf::String> listStringSkillIncreasement;
	int item_level;
	int number_bonus;
	int type_hat;
	int id_item;
	int current_save = NoSave_E;
	int rarity_item = Common_E;

	sf::String GetStringBonus(int type_bonus);
public:
	E_WizardHat(int current_language, int current_save);
	~E_WizardHat();

	virtual int GetRarityItem() { return rarity_item; }
	void Init(int item_level_received, std::vector<int> listTypeBonus_received, std::vector<float> listBonus_received, std::vector<sf::Vector2f> listRangeBonus_received, std::vector<int> SkillIncreasement, std::vector<int> SkillIncreasementLevel,std::vector<sf::String> listStringSkillBonus, int type_hat_received, int id_item_received, int rarity);
	virtual float GetBonusValue(int type_bonus);
	virtual int GetILvl() { return item_level; }
	virtual std::vector<int> GetListSkillIncreasement();
	virtual std::vector<int> GetListSkillIncreasementLevel() {return ListSkillIncreasementLevel;}
	virtual int GetCategoryEquipment() { return WizardHatEquipment_E; }
	virtual int GetTypeEquipment() { return type_hat; }
	virtual void SaveInformation(int id_ring1, int id_ring2, int id_weapon, int id_hat);
	virtual int GetIdEquipment() { return id_item; }
	virtual std::vector<sf::String> GetListStringEquipment();
};

