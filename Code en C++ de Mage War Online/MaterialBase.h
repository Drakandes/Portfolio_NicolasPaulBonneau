#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "ProjectileBase.h"
#include <memory>

class MaterialBase : public ProjectileBase
{
public:
	MaterialBase();
	~MaterialBase();

	virtual int GetTypeMaterial() { return -1; };
	virtual bool DrawOnTheFloor() { return false; }
	virtual void TeleportEntity(sf::Vector2f position, int TypeTeleportation) {}
	virtual void SetToDelete() {}
	virtual void DealWithCollision(std::shared_ptr<CollisionalObject> object_collided) {}
	virtual int GetTypeCollisionalObject() { return Nothing_E; }
	virtual sf::FloatRect GetCollisionRect() { sf::FloatRect nothing; return nothing; }
	virtual sf::Vector2f GetCurrentPosition() { return sf::Vector2f(0, 0); }
	virtual void Draw(sf::RenderWindow &window){}
	virtual int GetRayon() { return 0; }
	virtual sf::Vector2f GetSize() { return sf::Vector2f(0, 0); }
	virtual bool CheckIdObject(int id_object) { return false; }
	virtual int GetId() { return 0; }
	virtual void Update(float DELTATIME, sf::Vector2f player_position) {}
	virtual bool IsNeedToDelete() { return false; }
	virtual void PutItBackInQuadtree() {}
	virtual bool CheckIfNeedGoBackQuadtree() { return false; }
};

