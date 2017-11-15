#include "stdafx.h"
#include "PetGestion.h"

PetGestion::PetGestion()
{
}

PetGestion::~PetGestion()
{
}

void PetGestion::UpdatePlayerPet(float DELTATIME, std::shared_ptr<Player> player, MonsterGenerator &monster_generator)
{
	std::shared_ptr<PetBase> current_pet = player->GetCurrentPet();

	if (current_pet != NULL)
	{
		sf::Vector2f current_pet_position = current_pet->GetCurrentPosition();
		std::shared_ptr<MonsterBase> closest_monster =  monster_generator.GetMonsterCloserToPosition(current_pet_position);
		
		if(closest_monster != NULL)
		{
			current_pet->Update(DELTATIME, closest_monster->GetCurrentPosition(), closest_monster->GetEntityVelocity());
		}
		else
		{
			current_pet->Update(DELTATIME, sf::Vector2f(-1000,-1000), sf::Vector2f(0, 0));
		}
		closest_monster.reset();
	}

	player.reset();
}

void PetGestion::LoadPetInformation(std::shared_ptr<Player> player)
{
	int current_save = ListObjectsSingleton::instance()->GetCurrentSave();
	std::ifstream myfile;

	if (current_save == FirstSave_E)
	{
		myfile.open("Pet1.txt");
	}
	else if (current_save == SecondSave_E)
	{
		myfile.open("Pet2.txt");
	}
	else
	{
		myfile.open("Pet3.txt");
	}
	
	int counter_pet_created = 0;

	if (myfile.is_open())
	{
		std::string str;
		myfile >> str;

		while (str == "NewPet")
		{
			std::vector<int> CurrentPetAttributes{ 0,0,0,0 };;
			std::vector<int> PetMaxAttributes{ 0,0,0,0 };;
			std::vector<sf::Vector2i> ListPetSkillPossible{ sf::Vector2i(0,0) ,sf::Vector2i(0,0) ,sf::Vector2i(0,0) ,sf::Vector2i(0,0) ,sf::Vector2i(0,0) };;
			std::vector<int> ListPetSkillObtained{ -1 ,-1 ,-1 ,-1 ,-1 };;
			std::vector<int> ListPetSkillObtainedForInterface{ -1 ,-1 ,-1 ,-1 ,-1 };;
			float exp = 0;
			int level = 10;
			int type_pet = NoPet_E;
			bool is_current_pet = false;

			myfile >> str;
			if (str == "IdItem")
			{
				myfile >> str;
				if (str == "<")
				{
					myfile >> str;
					while (str != ">")
					{
						if (str == "true")
						{
							is_current_pet = true;
						}
						myfile >> str;
					}
				}
			}

			myfile >> str;
			if (str == "PetAttributes")
			{
				myfile >> str;
				if (str == "<")
				{
					myfile >> str;
					int counter = 0;
					while (str != ">")
					{
						int number = GlobalFunction::ConvertStringToInt(str);
						CurrentPetAttributes[counter] = number;
						counter++;
						myfile >> str;
					}
				}
			}

			myfile >> str;
			if (str == "PetMaxAttributes")
			{
				myfile >> str;
				if (str == "<")
				{
					myfile >> str;
					int counter = 0;
					while (str != ">")
					{
						int number = GlobalFunction::ConvertStringToInt(str);
						PetMaxAttributes[counter] = number;
						counter++;
						myfile >> str;
					}
				}
			}

			myfile >> str;
			if (str == "ListPetSkillPossible")
			{
				myfile >> str;
				if (str == "<")
				{
					myfile >> str;
					int counter = 0;
					while (str != ">")
					{
						sf::Vector2i number;

						number.x = GlobalFunction::ConvertStringToInt(str);
						myfile >> str;

						number.y = GlobalFunction::ConvertStringToInt(str);
						myfile >> str;
						ListPetSkillPossible[counter] = number;
						counter++;
					}
				}
			}

			myfile >> str;
			if (str == "ListPetSkillObtained")
			{
				myfile >> str;
				if (str == "<")
				{
					myfile >> str;
					int counter = 0;
					while (str != ">")
					{
						int number = GlobalFunction::ConvertStringToInt(str);
						ListPetSkillObtained[counter] = number;
						counter++;
						myfile >> str;
					}
				}
			}

			myfile >> str;
			if (str == "ListPetSkillObtainedForInterface")
			{
				myfile >> str;
				if (str == "<")
				{
					myfile >> str;
					int counter = 0;
					while (str != ">")
					{
						int number = GlobalFunction::ConvertStringToInt(str);
						ListPetSkillObtainedForInterface[counter] = number;
						counter++;
						myfile >> str;
					}
				}
			}

			myfile >> str;
			if (str == "exp")
			{
				myfile >> str;
				if (str == "<")
				{
					myfile >> str;
					exp = GlobalFunction::ConvertStringToFloat(str);
					myfile >> str;
				}
			}

			myfile >> str;
			if (str == "level")
			{
				myfile >> str;
				if (str == "<")
				{
					myfile >> str;
					level = GlobalFunction::ConvertStringToInt(str);
					myfile >> str;
				}
			}

			myfile >> str;
			if (str == "TypePet")
			{
				myfile >> str;
				if (str == "<")
				{
					myfile >> str;
					type_pet = GlobalFunction::ConvertStringToInt(str);
					myfile >> str;
				}
			}
			myfile >> str;

			switch (type_pet)
			{
			case Ninja_E:
			{
				std::shared_ptr<Ninja> pet = std::shared_ptr<Ninja>(new Ninja(ListObjectsSingleton::instance()->GetNewID()));
				pet->InitWithInformation(CurrentPetAttributes, PetMaxAttributes, ListPetSkillPossible, ListPetSkillObtained, ListPetSkillObtainedForInterface, exp, level);
				player->GivePet(pet);
				pet.reset();
				break;
			}
			case Fairy_E:
			{
				std::shared_ptr<Fairy> pet = std::shared_ptr<Fairy>(new Fairy(ListObjectsSingleton::instance()->GetNewID()));
				pet->InitWithInformation(CurrentPetAttributes, PetMaxAttributes, ListPetSkillPossible, ListPetSkillObtained, ListPetSkillObtainedForInterface, exp, level);
				player->GivePet(pet);
				pet.reset();
				break;
			}
			case Knight_E:
			{
				std::shared_ptr<Knight> pet = std::shared_ptr<Knight>(new Knight(ListObjectsSingleton::instance()->GetNewID()));
				pet->InitWithInformation(CurrentPetAttributes, PetMaxAttributes, ListPetSkillPossible, ListPetSkillObtained, ListPetSkillObtainedForInterface, exp, level);
				player->GivePet(pet);
				pet.reset();
				break;
			}
			}

			if (is_current_pet)
			{
				player->ChangeCurrentPet(counter_pet_created);
			}
			counter_pet_created++;
		}
	}

	player.reset();
}