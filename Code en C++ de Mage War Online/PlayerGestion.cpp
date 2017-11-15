#include "stdafx.h"
#include "PlayerGestion.h"

PlayerGestion::PlayerGestion()
{
}

PlayerGestion::~PlayerGestion()
{
	listPlayers.clear();
}

void PlayerGestion::AddPlayer(sf::Vector2f window_dimension)
{
	std::shared_ptr<Player> player = std::shared_ptr<Player>(new Player());
	player->Init(sf::Vector2f(100, 100),sf::Vector2f(0,0), window_dimension, ListObjectsSingleton::instance()->GetNewID());
	player->UpdateStatsWithEquipments();
	listPlayers.push_back(player);
	MainQuadtree::instance()->insert(player->GetCurrentPosition(), player->GetSize(), player);
	player.reset();
}

void PlayerGestion::UpdateAllPlayer(float DELTATIME, SkillManagement &skill_manager, sf::Vector2f mouse_position)
{
	std::list<std::shared_ptr<Player>>::iterator iterator = listPlayers.begin();
	while (iterator != listPlayers.end())
	{
		if ((*iterator)->CheckIfNeedGoBackQuadtree())
		{
			MainQuadtree::instance()->insert((*iterator)->GetCurrentPosition(), (*iterator)->GetSize(), (*iterator));
		}
		(*iterator)->CalculateMovement(DELTATIME,mouse_position);
		(*iterator)->UsingSkill(skill_manager, mouse_position);
		iterator++;
	}
}

void PlayerGestion::AddPlayerToDrawList()
{
	std::list<std::shared_ptr<Player>>::iterator iterator = listPlayers.begin();
	while (iterator != listPlayers.end())
	{
		(*iterator)->AddToDrawListPet();
		DrawGestion::instance()->AddObjectToList(*iterator);
		iterator++;
	}
}
