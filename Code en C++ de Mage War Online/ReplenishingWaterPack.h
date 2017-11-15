#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GlobalEnum.h"
#include <iostream>
#include "GlobalFunction.h"
#include "Player.h"
#include "ProjectileBase.h"

class ReplenishingWaterPack : public ProjectileBase
{
private:
	bool need_to_be_put_in_quadtree = false;
	int rayon = 15;
	int id_projectile;
	int id_parent;
	sf::Vector2f position_projectile;
	sf::Vector2f size_projectile{ 29,29 };
	sf::Sprite projectile;
	sf::Texture texture_projectile;
	float duration_projectile;
	float duration_recovery = 0;
	float hp_recovery = 0;
	float boost_movement_speed = 0;
	float duration_bonus_movement_speed = 0;
	bool is_to_delete = false;
	bool been_init = false;
	sf::Clock clock_time_creation;

public:
	ReplenishingWaterPack();
	~ReplenishingWaterPack();

	virtual int GetId() { return id_parent; }
	virtual void PutItBackInQuadtree();
	virtual bool CheckIfNeedGoBackQuadtree();
	virtual void DealWithCollision(std::shared_ptr<CollisionalObject> object_collided);
	virtual int GetTypeCollisionalObject() { return Projectile_E; }
	virtual sf::FloatRect GetCollisionRect() { return projectile.getGlobalBounds(); }
	void Init(sf::Vector2f position_initial, float duration_received, float hp_recovery_received, float duration_recovery_received, float movement_speed_bonus, float duration_movement_speed_bonus);
	virtual sf::Vector2f GetCurrentPosition();
	virtual sf::Vector2f GetSize();
	virtual int GetRayon();
	virtual float GetDamage();
	virtual bool IsNeedToDelete();
	virtual bool CheckCollision(sf::FloatRect rect_collision, int id_object, sf::Vector2f position_object);
	virtual void Update(float DELTATIME, sf::Vector2f player_position);
	virtual void CuttingSprite();
	virtual void CheckIfToDelete();
	virtual void Initialized(int player_id);
	virtual bool GetInitStatus();
	virtual void Draw(sf::RenderWindow &window);
	virtual bool CanChangeObjectStat();
	virtual int GetNumberObjectStatChange();
	virtual int GetObjectStatChanging(int number);
	virtual float GetObjectStatChangeDuration(int number);
	virtual float GetObjectStatChangValue(int number);
	virtual bool CanAffectMonster();
	virtual bool CanAffectPlayer();
};

