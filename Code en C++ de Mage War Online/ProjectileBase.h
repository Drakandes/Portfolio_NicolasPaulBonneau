#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GlobalEnum.h"
#include <iostream>
#include "GlobalFunction.h"
#include "CollisionalObject.h"
#include "TextGenerator.h"

class ProjectileBase : public CollisionalObject
{
public:
	ProjectileBase();
	~ProjectileBase();

	virtual int GetId() { return 0; }
	virtual int GetTypeMaterial() { return -1; };
	virtual bool DrawOnTheFloor() { return false; }
	virtual void SetToDelete(){}
	virtual void DealWithCollision(std::shared_ptr<CollisionalObject> object_collided);
	virtual int GetTypeCollisionalObject() { return Nothing_E; }
	virtual sf::Vector2f GetSize();
	virtual int GetRayon();
	virtual float GetDamage();
	virtual void Update(float DELTATIME, sf::Vector2f player_position);
	virtual bool IsNeedToDelete();
	virtual void Draw(sf::RenderWindow &window);
	virtual sf::Vector2f GetCurrentPosition();
	virtual bool CheckCollision(sf::FloatRect rect_collision, int id_object, sf::Vector2f position_object);
	virtual bool CanAffectMonster();
	virtual bool CanAffectPlayer();
	virtual sf::FloatRect GetCollisionRect() { sf::FloatRect nothing; return nothing; }
	virtual void PutItBackInQuadtree() {}
	virtual bool CheckIfNeedGoBackQuadtree() { return false; }
	virtual bool CanDamageNatureObject() { return true; }

	virtual bool CanPush();
	virtual float GetDistancePushing();

	virtual bool CanSlow();
	virtual float GetDurationSlow();
	virtual float GetPercentSlow();

	virtual bool CanStun();
	virtual float GetStunTime();

	virtual bool CanChangeSkillCooldown();
	virtual int GetSkillCooldownChanging();
	virtual float GetNewSkillCooldown();

	virtual bool CanChangeObjectStat();
	virtual int GetNumberObjectStatChange();
	virtual int GetObjectStatChanging(int number);
	virtual float GetObjectStatChangeDuration(int number);
	virtual float GetObjectStatChangValue(int number);

	virtual bool CanIgnite();
	virtual int GetTypeIgnition();
	virtual float GetIgnitionDuration();
	virtual float GetIgnitionDamage();

	virtual bool CanCreateExplosion();
	virtual sf::Vector2f GetSizeExplosion();
	virtual float GetDamageExplosion();
	virtual float GetSizeExplosionModifier();

	virtual bool CheckIfProjectileDisable() { return false; }
};

