#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GlobalEnum.h"
#include <iostream>
#include "GlobalFunction.h"
#include "ProjectileBase.h"
#include "Explosion.h"<
#include "ProjectileGestion.h"

class PushImpact : public ProjectileBase
{
private:
	bool need_to_be_put_in_quadtree = false;
	int rayon = 25;
	int id_projectile;
	int id_parent;
	float damage;
	float time_channeling = 0.65;
	float push_distance = 200;
	sf::Vector2f position_origin;
	sf::CircleShape circle_impact;
	sf::CircleShape circle_channeling;
	sf::Clock clock_creation;
	bool is_to_delete = false;
	bool channeled = false;

public:
	PushImpact();
	~PushImpact();

	virtual int GetId() { return id_parent; }
	virtual void SetToDelete() { is_to_delete = true; }
	virtual void PutItBackInQuadtree();
	virtual bool CheckIfNeedGoBackQuadtree();
	virtual void DealWithCollision(std::shared_ptr<CollisionalObject> object_collided);
	virtual int GetTypeCollisionalObject() { return Projectile_E; }
	virtual sf::FloatRect GetCollisionRect() { return circle_impact.getGlobalBounds(); }
	void Init(sf::Vector2f &position_initial, float damage_received , int id_caster);
	virtual sf::Vector2f GetCurrentPosition();
	virtual int GetRayon();
	virtual float GetDamage();
	virtual bool IsNeedToDelete();
	virtual void Update(float DELTATIME, sf::Vector2f player_position);
	virtual void Draw(sf::RenderWindow &window);
	virtual bool CanAffectMonster();
	virtual bool CanAffectPlayer();
};


