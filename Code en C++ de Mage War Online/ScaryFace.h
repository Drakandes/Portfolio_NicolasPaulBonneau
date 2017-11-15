#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GlobalEnum.h"
#include <iostream>
#include "GlobalFunction.h"
#include "ProjectileBase.h"

class ScaryFace : public ProjectileBase
{
private:
	bool need_to_be_put_in_quadtree = false;
	int rayon = 200;
	int id_projectile;
	int id_parent;
	float time_scared = 5;
	float duration = 0.5;
	sf::Vector2f position_origin;
	sf::Vector2f size_projectile{ 40,26 };
	sf::Sprite projectile;
	sf::CircleShape circle_collision;
	sf::Texture texture_projectile;
	sf::Clock clock_duration;
	bool is_to_delete = false;

public:
	ScaryFace();
	~ScaryFace();

	virtual int GetId() { return id_parent; }
	virtual void SetToDelete() { is_to_delete = true; }
	virtual void PutItBackInQuadtree();
	virtual bool CheckIfNeedGoBackQuadtree();
	virtual void DealWithCollision(std::shared_ptr<CollisionalObject> object_collided);
	virtual int GetTypeCollisionalObject() { return Projectile_E; }
	virtual sf::FloatRect GetCollisionRect() { return circle_collision.getGlobalBounds(); }
	void Init(sf::Vector2f &position_initial, int id_caster);
	virtual sf::Vector2f GetCurrentPosition();
	virtual sf::Vector2f GetSize();
	virtual int GetRayon();
	virtual bool IsNeedToDelete();
	virtual void Update(float DELTATIME, sf::Vector2f player_position);
	virtual void Draw(sf::RenderWindow &window);
	virtual bool CanAffectMonster();
	virtual bool CanAffectPlayer();
	virtual bool CanChangeObjectStat();
	virtual int GetNumberObjectStatChange();
	virtual int GetObjectStatChanging(int number);
	virtual float GetObjectStatChangeDuration(int number);
	virtual float GetObjectStatChangValue(int number);
};
