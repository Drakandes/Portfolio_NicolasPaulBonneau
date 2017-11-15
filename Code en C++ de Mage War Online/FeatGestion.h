#pragma once
#include "GlobalEnum.h"
#include "GlobalFunction.h"
#include "SFML\Graphics.hpp"
#include <vector>
#include <list>
#include <memory>
#include "ListObjectsSingleton.h"
#include <cmath>

class FeatGestion
{
private:
	const static int number_feats = 10;
	static FeatGestion *s_instance1;
	std::vector<float> listFeatBonus;
	std::vector<float> listFeatRecord;
	std::vector<float> listFeatCurrentValue;
	std::vector<double> listFeatBonusPerUnit{0.2,0.0002,0.25,5,10,1,0.25,1,0.5,6};

	void CalculateBonus();
public:
	FeatGestion();
	~FeatGestion();	
	
	static void Initialize()
	{
		s_instance1 = new FeatGestion();
	}
	static FeatGestion *instance()
	{
		if (!s_instance1)
			s_instance1 = new FeatGestion;
		return s_instance1;
	}

	void Action(int type_action, float value);
	void Save(int current_save);
	void Load(int current_save);
	void UpdateUponDeath();
	std::vector<float> GetListFeatBonus() { return listFeatBonus; }
	std::vector<float> GetListFeatRecord() { return listFeatRecord; }
	std::vector<float> GetListFeatCurrentValue() { return listFeatCurrentValue; }
};