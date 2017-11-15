#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GlobalEnum.h"
#include <iostream>
#include "GlobalFunction.h"
#include "ProjectileBase.h"
#include "IncludeAllMaterial.h"
#include "ListObjectsSingleton.h"

class NatureObject : public ProjectileBase
{
public:
	NatureObject();
	~NatureObject();

	virtual bool IsNeedToDelete() { return false; }
	virtual void SetToDelete(){}
	virtual sf::Vector2f GetSize() { return sf::Vector2f(0, 0); }
	virtual void DealWithCollision(std::shared_ptr<CollisionalObject> object_collided){}
	virtual int GetTypeCollisionalObject() { return NatureObject_E; }
	virtual sf::FloatRect GetCollisionRect() { sf::FloatRect nothing; return nothing; }
	virtual void Init(sf::Vector2f position);
	virtual bool CheckCollision(sf::FloatRect rect_collision, int id_object, sf::Vector2f position_object);
	virtual sf::Vector2f GetCurrentPosition();
	virtual void Draw(sf::RenderWindow &window);
	virtual bool CanPush();
	virtual float GetDistancePushing();
};

