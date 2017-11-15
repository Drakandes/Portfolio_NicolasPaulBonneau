#pragma once
#include "EquipmentBase.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

class E_Ring : public EquipmentBase
{
	int language;
	std::vector<bool> listIfHaveBonus;
	std::vector<float> listBonus;
	std::vector<sf::Vector2f> listRangeBonus;
	int item_level;
	int number_bonus;
	int id_item;
	int current_save = NoSave_E;
	int rarity_item = Common_E; 
	int type_ring = 0;
	enum RingBonus { RingHpRecovery, RingHpPercentRevoery, RingMovementSpeedAddition, RingDamagePercent, RingDamageAddition, RingExperiencePercent, RingHealthAddition, RingHealthPercent, RingArmorAddition, RingArmorPercent, RingCooldown, RingAttackSpeedPercent, RingLifeSteal, };
public:
	E_Ring(int current_language, int current_save);
	~E_Ring();

	virtual std::vector<bool> GetListIfHaveBonus() { return listIfHaveBonus; }
	virtual std::vector<float> GetListBonus() { return listBonus; }
	virtual int GetRarityItem() { return rarity_item; }
	void Init(int item_level_received, std::vector<bool> listIfHaveBonus_received, std::vector<float> listBonus_received, std::vector<sf::Vector2f> listRangeBonus_received, int id_item_received, int rarity, int number_max_bonus);
	virtual int GetILvl() { return item_level; }
	virtual int GetCategoryEquipment() { return RingEquipment_E; }
	virtual std::vector<sf::String> GetListStringEquipment();
	virtual void SaveInformation(int id_ring1, int id_ring2, int id_weapon, int id_hat);
	virtual int GetIdEquipment() { return id_item; }
	sf::String GetStringBonus(int type_bonus);
};

