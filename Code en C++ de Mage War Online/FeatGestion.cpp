#include "stdafx.h"
#include "FeatGestion.h"

FeatGestion::FeatGestion()
{
	for (int i = 0; i < number_feats; i++)
	{
		listFeatBonus.push_back(0);
		listFeatRecord.push_back(0);
		listFeatCurrentValue.push_back(0);
	}
}

FeatGestion::~FeatGestion()
{
}

void FeatGestion::Action(int type_action, float value)
{
	if(type_action == F_Achievement)
	{ 
		listFeatCurrentValue[Talented_E] = value;
		if (listFeatCurrentValue[type_action] > listFeatRecord[type_action])
		{
			listFeatRecord[type_action] = listFeatCurrentValue[type_action];
		}
	}
	else if (type_action == F_MoneyReceived)
	{
		listFeatCurrentValue[type_action] = std::floor(value / 15000);
		if (listFeatCurrentValue[type_action] > listFeatRecord[type_action])
		{
			listFeatRecord[type_action] = listFeatCurrentValue[type_action];
		}
	}
	else if (type_action == F_LevelReached)
	{
		listFeatCurrentValue[type_action] = value;
		if (listFeatCurrentValue[type_action] > listFeatRecord[type_action])
		{
			listFeatRecord[type_action] = listFeatCurrentValue[type_action];
		}
	}
	else if (type_action == F_MapReached)
	{
		listFeatCurrentValue[type_action] = value;
		if (listFeatCurrentValue[type_action] > listFeatRecord[type_action])
		{
			listFeatRecord[type_action] = listFeatCurrentValue[type_action];
		}
	}
	else if (type_action == F_TimeBattle)
	{
		listFeatCurrentValue[type_action] += value/60;
		if (listFeatCurrentValue[type_action] > listFeatRecord[type_action])
		{
			listFeatRecord[type_action] = listFeatCurrentValue[type_action];
		}
	}
	else
	{
		listFeatCurrentValue[type_action] += value;
		if (listFeatCurrentValue[type_action] > listFeatRecord[type_action])
		{
			listFeatRecord[type_action] = listFeatCurrentValue[type_action];
		}
	}
}

void FeatGestion::UpdateUponDeath()
{
	for (int i = 0; i < listFeatRecord.size(); i++)
	{
		if (listFeatCurrentValue[i] > listFeatRecord[i])
		{
			listFeatRecord[i] = listFeatCurrentValue[i];
		}
		listFeatCurrentValue[i] = 0;
	}

	CalculateBonus();
}

void FeatGestion::CalculateBonus()
{
	for (int i = 0; i < listFeatRecord.size(); i++)
	{
		listFeatBonus[i] = listFeatBonusPerUnit[i] * listFeatRecord[i];
	}
}

void FeatGestion::Save(int current_save)
{
	std::ofstream ofs;

	if (current_save == FirstSave_E)
	{
		ofs.open("Feat1.txt", std::ofstream::out | std::ofstream::trunc);
	}
	else if (current_save == SecondSave_E)
	{
		ofs.open("Feat2.txt", std::ofstream::out | std::ofstream::trunc);
	}
	else
	{
		ofs.open("Feat3.txt", std::ofstream::out | std::ofstream::trunc);
	}

	ofs.close();

	std::ofstream myfile;

	if (current_save == FirstSave_E)
	{
		myfile.open("Feat1.txt", std::fstream::app);
	}
	else if (current_save == SecondSave_E)
	{
		myfile.open("Feat2.txt", std::fstream::app);
	}
	else
	{
		myfile.open("Feat3.txt", std::fstream::app);
	}

	listFeatCurrentValue[Lord_E] = 0;
	listFeatCurrentValue[Archmage_E] = 0;

	myfile.seekp(std::ios::end);
	myfile << "Feat";
	myfile << std::endl;

	myfile << "ListRecord";
	myfile << std::endl;
	myfile << " < ";
	for (int i = 0; i < listFeatRecord.size(); i++)
	{
		std::string str("" + std::to_string(listFeatRecord[i]));
		myfile << str;
		myfile << std::string(" ");
	}
	myfile << " > ";
	myfile << std::endl;

	myfile << "ListCurrentValue";
	myfile << std::endl;
	myfile << " < ";
	for (int i = 0; i < listFeatCurrentValue.size(); i++)
	{
		std::string str("" + std::to_string(listFeatCurrentValue[i]));
		myfile << str;
		myfile << std::string(" ");
	}
	myfile << " > ";
	myfile << std::endl;

	myfile << "ListFeatBonus";
	myfile << std::endl;
	myfile << " < ";
	for (int i = 0; i < listFeatBonus.size(); i++)
	{
		std::string str("" + std::to_string(listFeatBonus[i]));
		myfile << str;
		myfile << std::string(" ");
	}
	myfile << " > ";
	myfile << std::endl;

	myfile.close();
}

void FeatGestion::Load(int current_save)
{
	std::ifstream myfile;

	if (current_save == FirstSave_E)
	{
		myfile.open("Feat1.txt");
	}
	else if (current_save == SecondSave_E)
	{
		myfile.open("Feat2.txt");
	}
	else
	{
		myfile.open("Feat3.txt");
	}

	if (myfile.is_open())
	{
		std::string str;
		myfile >> str;

		while (str == "Feat")
		{
			myfile >> str;
			if (str == "ListRecord")
			{
				myfile >> str;
				if (str == "<")
				{
					myfile >> str;
					int counter = 0;
					while (str != ">")
					{
						float number = GlobalFunction::ConvertStringToFloat(str);
						listFeatRecord[counter] = number;
						counter++;
						myfile >> str;
					}
				}
			}

			myfile >> str;
			if (str == "ListCurrentValue")
			{
				myfile >> str;
				if (str == "<")
				{
					myfile >> str;
					int counter = 0;
					while (str != ">")
					{
						float number = GlobalFunction::ConvertStringToFloat(str);
						listFeatCurrentValue[counter] = number;
						counter++;
						myfile >> str;
					}
				}
			}

			myfile >> str;
			if (str == "ListFeatBonus")
			{
				myfile >> str;
				if (str == "<")
				{
					myfile >> str;
					int counter = 0;
					while (str != ">")
					{
						float number = GlobalFunction::ConvertStringToFloat(str);
						listFeatBonus[counter] = number;
						counter++;
						myfile >> str;
					}
				}
			}
		}
	}

	myfile.close();
}

FeatGestion* FeatGestion::s_instance1 = 0;

