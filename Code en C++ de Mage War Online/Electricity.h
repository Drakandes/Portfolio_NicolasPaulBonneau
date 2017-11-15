#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GlobalEnum.h"
#include <iostream>
#include "GlobalFunction.h"
#include "ProjectileBase.h"
#include "MonsterBase.h"

class Electricity : public ProjectileBase
{
private:
	std::shared_ptr<MonsterBase> parent;
	bool need_to_be_put_in_quadtree = false;
	int rayon = 300;
	int id_projectile;
	int id_parent;
	float damage_initial;
	float damage;
	float rotation_projectile;
	float range_projectile = 600;
	float timer_to_reach_end = 0.85;
	float stun_duration = 1.25;
	float length_projectile = 1;
	sf::Vector2f position_origin;
	sf::Vector2f size_projectile{ 600,15 };
	sf::Vector2f size_rect_collision{ 6,25 };
	sf::Vector2f size_current_projectile = sf::Vector2f(0, 0);
	sf::Sprite projectile;
	sf::RectangleShape rect_collision;
	sf::Texture texture_projectile;
	bool growing = true;
	bool is_to_delete = false;
	bool can_stun = false;

	sf::Clock clock_animation;
	sf::Clock clock_time_creation;

	sf::Texture shadow_texture;
	sf::Sprite shadow;
	sf::Vector2f shadow_size{ 32,18 };

public:
	Electricity();
	~Electricity();

	virtual int GetId() { return id_parent; }
	virtual void SetToDelete() { is_to_delete = true; }
	virtual void PutItBackInQuadtree();
	virtual bool CheckIfNeedGoBackQuadtree();
	virtual void DealWithCollision(std::shared_ptr<CollisionalObject> object_collided);
	virtual sf::FloatRect GetCollisionRect() { return rect_collision.getGlobalBounds(); }
	void Init(sf::Vector2f &position_player, float damage_received, float angle, float id_parent, std::shared_ptr<MonsterBase> parent_received);
	void Movement_of_fireball();
	virtual sf::Vector2f GetCurrentPosition();
	virtual sf::Vector2f GetSize();
	virtual float GetDamage();
	virtual bool IsNeedToDelete();
	virtual void CuttingSprite();
	virtual void Update(float DELTATIME, sf::Vector2f player_position);
	virtual void Draw(sf::RenderWindow &window);
	virtual bool CanAffectMonster();
	virtual bool CanAffectPlayer();
	virtual bool CanStun();
	virtual float GetStunTime();
	virtual int GetTypeCollisionalObject() { return Projectile_E; }
	virtual void DrawShadow(sf::RenderWindow &window);
	virtual bool SpriteHasShadow() { return true; }
	virtual sf::Vector2f GetCurrentPositionShadow();
};

