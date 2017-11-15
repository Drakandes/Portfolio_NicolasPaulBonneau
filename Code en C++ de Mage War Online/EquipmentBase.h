#pragma once
#include "GlobalEnum.h"
#include "GlobalFunction.h"
#include "SFML\Graphics.hpp"
#include <vector>
#include <list>
#include <memory>

class EquipmentBase
{
public:
	EquipmentBase();
	~EquipmentBase();

	virtual std::vector<bool> GetListIfHaveBonus() { std::vector<bool> holder; return holder; }
	virtual std::vector<float> GetListBonus() { std::vector<float> holder; return holder; }
	virtual int GetRarityItem() { return -1; }
	virtual void SaveInformation(int id_ring1,int id_ring2,int id_weapon, int id_hat){}
	virtual float GetBonusValue(int type_bonus) { return 0; }
	virtual std::vector<int> GetListTalentIncreasement() { std::vector<int> holder; return holder; }
	virtual std::vector<int> GetListSkillIncreasement();
	virtual std::vector<int> GetListSkillIncreasementLevel() { std::vector<int> holder; return holder; }
	virtual int GetCategoryEquipment() { return BaseEquipment_E; }
	virtual int GetILvl() { return 0; }
	virtual int GetTypeEquipment() { return 0; }
	virtual int GetIdEquipment() { return -1; }
	virtual std::vector<sf::String> GetListStringEquipment() { std::vector<sf::String> holder;  return holder; }
};

