#include "stdafx.h"
#include "PillarGestion.h"

PillarGestion::PillarGestion()
{
}

PillarGestion::~PillarGestion()
{
	ListPillar.clear();
}

void PillarGestion::Init(sf::Vector2f size_map)
{
	std::vector<int> listTypePillar{ Self_Damage ,Self_Exp ,Self_Health,Self_Speed };

	if (true)
	{
		std::shared_ptr<Pillar> pillar = std::shared_ptr<Pillar>(new Pillar());
		int random_type = GlobalFunction::getRandomRange(1, listTypePillar.size()) - 1;
		pillar->Init(sf::Vector2f(size_map.x / 3, size_map.y / 3), random_type);
		ListPillar.push_back(pillar);
		listTypePillar.erase(listTypePillar.begin() + random_type);
	}
	if (true)
	{
		std::shared_ptr<Pillar> pillar = std::shared_ptr<Pillar>(new Pillar());
		int random_type = GlobalFunction::getRandomRange(1, listTypePillar.size()) - 1;
		pillar->Init(sf::Vector2f(size_map.x * 2 / 3, size_map.y / 3), random_type);
		ListPillar.push_back(pillar);
		listTypePillar.erase(listTypePillar.begin() + random_type);
	}
	if (true)
	{
		std::shared_ptr<Pillar> pillar = std::shared_ptr<Pillar>(new Pillar());
		int random_type = GlobalFunction::getRandomRange(1, listTypePillar.size()) - 1;
		pillar->Init(sf::Vector2f(size_map.x / 3, size_map.y * 2 / 3), random_type);
		ListPillar.push_back(pillar);
		listTypePillar.erase(listTypePillar.begin() + random_type);
	}
	if (true)
	{
		std::shared_ptr<Pillar> pillar = std::shared_ptr<Pillar>(new Pillar());
		int random_type = GlobalFunction::getRandomRange(1, listTypePillar.size()) - 1;
		pillar->Init(sf::Vector2f(size_map.x * 2 / 3, size_map.y * 2 / 3), random_type);
		ListPillar.push_back(pillar);
		listTypePillar.erase(listTypePillar.begin() + random_type);
	}

	ResetPillar();
}

void PillarGestion::ResetPillar()
{
	std::vector<int> listExceptions;
	for (int i = 0; i < number_pillar; i++)
	{
		int random_number = GlobalFunction::getRandomRangeWithUnknownException(1, number_pillar, listExceptions) - 1;
		listExceptions.push_back(random_number);
		ListPillar[i]->ChangeType(random_number - 1);
	}
}

sf::Vector2i PillarGestion::Update( std::shared_ptr<Player> &player, float DELTATIME)
{
	sf::Vector2i to_return{ MonsterGeneratorNothing,0 };
	if (clock_activation.getElapsedTime().asSeconds() >= 0.3)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		{
			for (int i = 0; i < number_pillar; i++)
			{
				if (ListPillar[i]->GetCollisionRect().intersects(player->GetCollisionRect()))
				{
					to_return = ListPillar[i]->DealWithCollision(player);
				}
			}
			clock_activation.restart();
		}
	}

	for (int i = 0; i < number_pillar; i++)
	{
		ListPillar[i]->Update(DELTATIME, player->GetCurrentPosition());
	}

	return to_return;
}

void PillarGestion::AddPillarDraw()
{
	for (int i = 0; i < number_pillar; i++)
	{
		DrawGestion::instance()->AddObjectToList(ListPillar[i]);
	}
}