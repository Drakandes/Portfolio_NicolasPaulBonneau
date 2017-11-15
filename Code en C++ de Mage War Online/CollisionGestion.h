#pragma once
#include <SFML/Graphics.hpp>
#include "GlobalFunction.h"
#include "GlobalEnum.h"
#include "CollisionalObject.h"
#include "ProjectileBase.h"
#include "ProjectileGestion.h"
#include "TextGenerator.h"

#include "MonsterBase.h"
#include "NatureObject.h"
#include "RectTest.h"

class CollisionGestion
{
private:
public:
	CollisionGestion();
	~CollisionGestion();

	void CollisionUpdate(std::list<std::shared_ptr<MonsterBase>> &listMonsters, std::shared_ptr<CollisionalObject> player, TextGenerator &text_generator, std::list<std::shared_ptr<ProjectileBase>> listNatureObjects);
};

