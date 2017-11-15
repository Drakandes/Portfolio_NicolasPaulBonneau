#include "stdafx.h"
#include "AchievementGestion.h"

AchievementGestion::AchievementGestion()
{

}

AchievementGestion::~AchievementGestion()
{
}

void AchievementGestion::Init(std::vector<sf::String> string_achievement_received)
{
	string_achievement = string_achievement_received;
}

void AchievementGestion::ActionInAchievement(int type_action, float value)
{
	switch (type_action)
	{
	case A_Heal:
		listValueReached[TotalHealOneRun] += value;
		break;
	case A_InCombat:
		if (value > 0)
		{
			float time_passed = clock_outside_battle.getElapsedTime().asSeconds();
			listValueReached[NoDamageWhileCombat] += time_passed;
			clock_outside_battle.restart();
		}
		else
		{
			clock_outside_battle.restart();
		}
		break;
	case A_OutOfSprint:
		listValueReached[OutOfSprintOneRun] += 1;
		break;
	case A_NumberMonsterRadar:
		listValueReached[MonsterOnRadar] = value;
		break;
	case A_MonsterKilled:
		listValueReached[MonsterKilledOneRun] += value;
		break;
	case A_MapReachedLevel:
		listValueReached[MapFifthReached] = value;
		break;
	case A_MonsterHit:
		listValueReached[MonsterHitOneRun] += value;
		break;
	case A_PlayerLevel:
		listValueReached[ReachLevelTen] = value;
		break;
	case A_GoldSpent:
		listValueReached[SpendGoldOneRun] += value;
		break;
	case A_NumberSkillLevelTwo:
		listValueReached[GetFiveSkillLevelTwo] = value;
		break;
	case A_MaterialCollected:
		listValueReached[CollectMaterialOneRun] += value;
		break;
	}
}

void AchievementGestion::Update()
{
	int counter_succeeded = 0;

	for (int i = 0; i < listSucceeded.size(); i++)
	{
		if(listSucceeded[i])
		{
			counter_succeeded++;
		}
	}

	listValueReached[GetFiveAchiemevents] = counter_succeeded;

	for (int i = 0; i < listValueReached.size(); i++)
	{
		if (listPossible[i])
		{
			if (listValueReached[i] >= listValueNeeded[i] && !listSucceeded[i])
			{
				sf::String str = "You got the achievement ";
				str.insert(str.getSize(), string_achievement[i]);
				str.insert(str.getSize(), "!");
				NotificationSystem::instance()->AddNoticeToList(str);
				listSucceeded[i] = true;
			}
		}
	}
}

void AchievementGestion::PlayerDied()
{
	for (int i = 0; i < listPossible.size(); i++)
	{
		listPossible[i] = true;
		listValueReached[i] = 0;
	}
}

void AchievementGestion::PlayerTookDamage()
{
	listPossible[NoDamageWhileCombat] = false;
}

void AchievementGestion::SaveInformation(int current_save)
{
	std::ofstream ofs;

	if (current_save == FirstSave_E)
	{
		ofs.open("Achievements1.txt", std::ofstream::out | std::ofstream::trunc);
	}
	else if (current_save == SecondSave_E)
	{
		ofs.open("Achievements2.txt", std::ofstream::out | std::ofstream::trunc);
	}
	else
	{
		ofs.open("Achievements3.txt", std::ofstream::out | std::ofstream::trunc);
	}

	ofs.close();


	std::ofstream myfile;

	if (current_save == FirstSave_E)
	{
		myfile.open("Achievements1.txt", std::fstream::app);
	}
	else if (current_save == SecondSave_E)
	{
		myfile.open("Achievements2.txt", std::fstream::app);
	}
	else
	{
		myfile.open("Achievements3.txt", std::fstream::app);
	}

	myfile.seekp(std::ios::end);
	myfile << "ModifyAtYourOwnRisk";
	myfile << std::endl;
	myfile << std::endl;

	myfile << "ListSucceeded";
	myfile << std::endl;
	myfile << " < ";
	for (int i = 0; i < listSucceeded.size(); i++)
	{
		if (listSucceeded[i])
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

	myfile << "ListPossible";
	myfile << std::endl;
	myfile << " < ";
	for (int i = 0; i < listPossible.size(); i++)
	{
		if (listPossible[i])
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

	myfile << "ListValueReached";
	myfile << std::endl;
	myfile << " < ";
	for (int i = 0; i < listValueReached.size(); i++)
	{
		std::string str("" + std::to_string(listValueReached[i]));
		myfile << str;
		myfile << std::string(" ");
	}
	myfile << " > ";
	myfile << std::endl;

	myfile.close();
}

void AchievementGestion::LoadInformation(int current_save)
{
	std::ifstream myfile;

	if (current_save == FirstSave_E)
	{
		myfile.open("Achievements1.txt");
	}
	else if (current_save == SecondSave_E)
	{
		myfile.open("Achievements2.txt");
	}
	else
	{
		myfile.open("Achievements3.txt");
	}

	if (myfile.is_open())
	{
		std::string str;
		myfile >> str;

		if (str == "ModifyAtYourOwnRisk")
		{
			myfile >> str;
			if (str == "ListSucceeded")
			{
				myfile >> str;
				if (str == "<")
				{
					int counter = 0;
					myfile >> str;
					while (str != ">")
					{
						if (str == "true")
						{
							listSucceeded[counter] = true;
							counter++;
							myfile >> str;
						}
						else
						{
							listSucceeded[counter] = false;
							counter++;
							myfile >> str;
						}
					}
				}
			}

			myfile >> str;
			if (str == "ListPossible")
			{
				myfile >> str;
				if (str == "<")
				{
					int counter = 0;
					myfile >> str;
					while (str != ">")
					{
						if (str == "true")
						{
							listPossible[counter] = true;
							counter++;
							myfile >> str;
						}
						else
						{
							listPossible[counter] = false;
							counter++;
							myfile >> str;
						}
					}
				}
			}

			myfile >> str;
			if (str == "ListValueReached")
			{
				myfile >> str;
				if (str == "<")
				{
					int counter = 0;
					myfile >> str;
					while (str != ">")
					{
						int number = GlobalFunction::ConvertStringToInt(str);
						listValueReached[counter] = number;
						counter++;
						myfile >> str;
					}
				}
			}
		}
	}

	myfile.close();
}
