#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GlobalEnum.h"
#include <iostream>
#include <list>
#include <vector>
#include "GlobalEnum.h"
#include "PetBase.h"
#include "MonsterBase.h"
#include "Player.h"
#include "MonsterGenerator.h"
#include "IncludeAllPets.h"


class PetGestion
{
public:
	PetGestion();
	~PetGestion();

	void UpdatePlayerPet(float DELTATIME, std::shared_ptr<Player> player, MonsterGenerator &monster_generator);
	void LoadPetInformation(std::shared_ptr<Player> player);
};

