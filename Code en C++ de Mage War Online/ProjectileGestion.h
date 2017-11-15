#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GlobalEnum.h"
#include "ProjectileBase.h"
#include "MainQuadtree.h"
#include <list>

#include <memory>

class ProjectileGestion
{
private:
	std::list<std::shared_ptr<ProjectileBase>> listAllProjectiles;
	static ProjectileGestion *s_instance;
public:
	ProjectileGestion();
	~ProjectileGestion();

	static void Initialize()
	{
		s_instance = new ProjectileGestion();
	}
	static ProjectileGestion *instance()
	{
		if (!s_instance)
			s_instance = new ProjectileGestion;
		return s_instance;
	}

	void AddListOfObjectToList(std::list<std::shared_ptr<ProjectileBase>> listObjects);
	void AddObjectToList(std::shared_ptr<ProjectileBase> ObjectToAdd);
	void UpdateAllProjectiles(float DELTATIME, sf::Vector2f player_position);
	void AddListToDrawGestion();
	std::list<std::shared_ptr<ProjectileBase>> GetListProjectiles();
};