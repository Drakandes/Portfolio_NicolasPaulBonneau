#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GlobalEnum.h"
#include <iostream>
#include "Player.h"
#include "GlobalFunction.h"
#include "ProjectileBase.h"

class BigBubble : public ProjectileBase
{
private:
	std::shared_ptr<Player> parent;
	bool need_to_be_put_in_quadtree = false;
	int rayon = 15;
	int id_projectile;
	int id_parent;
	int number_of_bounces = 0;
	int maximum_bounces;
	float damage;
	float speed;
	float propulsion_distance;
	float rotation_projectile;
	float range_projectile;
	float speed_projectile;
	float timer_animation = 0.05;
	sf::Vector2f position_origin;
	sf::Vector2f size_projectile{ 30,30 };
	sf::Sprite projectile;
	sf::Texture texture_projectile;
	bool been_init = false;
	bool is_to_delete = false;
	sf::Clock clock_animation;
	bool can_affect_player = false;

	sf::Texture shadow_texture;
	sf::Sprite shadow;
	sf::Vector2f shadow_size{ 26,10};
public:
	BigBubble();
	~BigBubble();

	virtual int GetId() { return id_parent; }
	virtual void SetToDelete() { is_to_delete = true; }
	virtual void PutItBackInQuadtree();
	virtual bool CheckIfNeedGoBackQuadtree();
	virtual void DealWithCollision(std::shared_ptr<CollisionalObject> object_collided);
	virtual int GetTypeCollisionalObject() { return Projectile_E; }
	void Init(sf::Vector2f &position_player, sf::Vector2f mouse_position, float damage_received, float speed_received, float range_projectile_received, float propulsion_distance_received, int bouncing_time, std::shared_ptr<Player> player);
	void Movement_of_fireball(float DELTATIME);
	virtual sf::Vector2f GetCurrentPosition();
	virtual sf::Vector2f GetSize();
	virtual int GetRayon();
	virtual void Update(float DELTATIME, sf::Vector2f player_position);
	virtual float GetDamage();
	virtual bool IsNeedToDelete();
	virtual bool CheckCollision(sf::FloatRect rect_collision, int id_object, sf::Vector2f position_object);
	virtual void Initialized(int player_id);
	virtual bool GetInitStatus();
	void SetAngles(sf::Vector2f &mouse_position, sf::Vector2f &position);
	virtual float CheckCollisionWithCaster(int rayon_player, sf::Vector2f position_player, sf::Vector2f size_player);
	virtual void Draw(sf::RenderWindow &window);
	virtual bool CanPush();
	virtual float GetDistancePushing();
	virtual bool CanAffectMonster();
	virtual bool CanAffectPlayer();
	virtual sf::FloatRect GetCollisionRect() { return projectile.getGlobalBounds(); }
	virtual void DrawShadow(sf::RenderWindow &window);
	virtual bool SpriteHasShadow() { return true; }
	virtual sf::Vector2f GetCurrentPositionShadow();
};

