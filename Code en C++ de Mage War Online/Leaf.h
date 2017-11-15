#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GlobalEnum.h"
#include <iostream>
#include "Player.h"
#include "GlobalFunction.h"
#include "ProjectileBase.h"

class Leaf : public ProjectileBase
{
private:
	std::shared_ptr<Player> parent;
	bool need_to_be_put_in_quadtree = false;
	int rayon = 9;
	int id_projectile;
	int id_parent;
	int health_leaf = 2;
	float damage;
	float speed;
	float rotation_projectile;
	float range_projectile;
	float speed_projectile;
	float timer_animation = 0.05;
	float duration_projectile;
	sf::Vector2f position_origin;
	sf::Vector2f size_projectile{ 12,18 };
	sf::Sprite projectile;
	sf::Texture texture_projectile;
	bool been_init = false;
	bool is_to_delete = false;
	sf::Clock clock_time_of_creation;
	sf::Clock clock_rotation;

public:
	Leaf();
	~Leaf();

	virtual int GetId() { return id_parent; }
	virtual void PutItBackInQuadtree();
	virtual bool CheckIfNeedGoBackQuadtree();
	virtual void DealWithCollision(std::shared_ptr<CollisionalObject> object_collided);
	virtual int GetTypeCollisionalObject() { return Projectile_E; }
	virtual sf::FloatRect GetCollisionRect() { return projectile.getGlobalBounds(); }
	void Init(sf::Vector2f &position_player, float damage_received, float speed_received, float range_projectile_received, float duration_received, std::shared_ptr<Player> player);
	void MovementOfProjectile(sf::Vector2f player_position, float DELTATIME);
	virtual void Update(float DELTATIME, sf::Vector2f player_position);
	virtual sf::Vector2f GetCurrentPosition();
	virtual sf::Vector2f GetSize();
	virtual int GetRayon();
	virtual float GetDamage();
	virtual bool IsNeedToDelete();
	virtual bool CheckCollision(sf::FloatRect rect_collision, int id_object, sf::Vector2f position_object);
	virtual void Initialized(int player_id, float angle_rotation_received);
	virtual bool GetInitStatus();
	void ToDelete();
	virtual void CheckIfToDelete();
	virtual void Draw(sf::RenderWindow &window);
	virtual bool CanAffectMonster();
	virtual bool CanAffectPlayer();
	virtual void DrawShadow(sf::RenderWindow &window);
};

