#include "stdafx.h"
#include "ProjectileGestion.h"

ProjectileGestion::ProjectileGestion()
{
}

ProjectileGestion::~ProjectileGestion()
{
	listAllProjectiles.clear();
}

void ProjectileGestion::UpdateAllProjectiles(float DELTATIME, sf::Vector2f player_position)
{
	std::list<std::shared_ptr<ProjectileBase>>::iterator iterator = listAllProjectiles .begin();
	while(iterator != listAllProjectiles.end())
	{
		if ((*iterator)->CheckIfNeedGoBackQuadtree())
		{
			MainQuadtree::instance()->insert((*iterator)->GetCurrentPosition(), (*iterator)->GetSize(), (*iterator));
		}

		(*iterator)->Update(DELTATIME, player_position);

		if ((*iterator)->IsNeedToDelete())
		{
			listAllProjectiles.erase(iterator++);
		}
		else
		{
			iterator++;
		}
	}
}

void ProjectileGestion::AddObjectToList(std::shared_ptr<ProjectileBase> ObjectToAdd)
{
	MainQuadtree::instance()->insert(ObjectToAdd->GetCurrentPosition(), ObjectToAdd->GetSize(), ObjectToAdd);
	listAllProjectiles.push_back(ObjectToAdd);
}

void ProjectileGestion::AddListToDrawGestion()
{
	std::list<std::shared_ptr<ProjectileBase>>::iterator iterator = listAllProjectiles.begin();
	while (iterator != listAllProjectiles.end())
	{
		DrawGestion::instance()->AddObjectToList((*iterator));
		iterator++;
	}
}

std::list<std::shared_ptr<ProjectileBase>>  ProjectileGestion::GetListProjectiles()
{
	return listAllProjectiles;
}

void ProjectileGestion::AddListOfObjectToList(std::list<std::shared_ptr<ProjectileBase>> listObjects)
{
	std::list<std::shared_ptr<ProjectileBase>>::iterator i = listObjects.begin();
	while (i != listObjects.end())
	{
		listAllProjectiles.push_back(*i);
		i++;
	}
	listObjects.clear();
}

ProjectileGestion* ProjectileGestion::s_instance = 0;