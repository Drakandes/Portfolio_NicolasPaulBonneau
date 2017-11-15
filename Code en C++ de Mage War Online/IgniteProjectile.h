#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GlobalEnum.h"
#include <iostream>
#include "Player.h"
#include "GlobalFunction.h"
#include "ProjectileBase.h"

class IgniteProjectile : public ProjectileBase
{
private:
	std::shared_ptr<Player> parent;
	bool need_to_be_put_in_quadtree = false;
	int rayon = 23;
	int id_projectile;
	int id_parent;
	int type_ignition = OnFireFromSkill;
	float damage;
	float speed;
	float ignite_damage;
	float ignite_duration;
	float rotation_projectile;
	float range_projectile;
	float speed_projectile;
	float timer_animation = 0.05;
	sf::Vector2f position_origin;
	sf::Vector2f size_projectile { 46,10 };
	sf::Vector2f holder_cuting_sprite{ 0,0 };
	sf::Vector2f dimension_animation{ 4,0 };
	sf::Sprite projectile;
	sf::Texture texture_projectile;
	bool been_init = false;
	bool is_to_delete = false;
	sf::Clock clock_animation;

	sf::Texture shadow_texture;
	sf::Sprite shadow;
	sf::Vector2f shadow_size{ 32,18 };
public:
	IgniteProjectile();
	~IgniteProjectile();

	virtual int GetId() { return id_parent; }
	virtual void SetToDelete() { is_to_delete = true; }
	virtual void PutItBackInQuadtree();
	virtual bool CheckIfNeedGoBackQuadtree();
	virtual void DealWithCollision(std::shared_ptr<CollisionalObject> object_collided);
	virtual int GetTypeCollisionalObject() { return Projectile_E; }
	virtual sf::FloatRect GetCollisionRect() { return projectile.getGlobalBounds(); }
	void Init(sf::Vector2f &position_player, sf::Vector2f mouse_position, float damage_received, float speed_received, float ignite_damage, float ignite_duration, float range_projectile_received, std::shared_ptr<Player> player);
	void Movement_of_fireball(float DELTATIME);
	virtual sf::Vector2f GetCurrentPosition();
	virtual sf::Vector2f GetSize();
	virtual int GetRayon();
	virtual float GetDamage();
	virtual bool IsNeedToDelete();
	virtual bool CheckCollision(sf::FloatRect rect_collision, int id_object, sf::Vector2f position_object);
	virtual void Initialized(int player_id);
	virtual bool GetInitStatus();
	void SetAngles(sf::Vector2f &mouse_position, sf::Vector2f &position);
	virtual void CuttingSprite();
	virtual void Draw(sf::RenderWindow &window);
	virtual bool CanIgnite();
	virtual int GetTypeIgnition();
	virtual void Update(float DELTATIME, sf::Vector2f player_position);
	virtual float GetIgnitionDuration();
	virtual float GetIgnitionDamage();
	virtual bool CanAffectMonster();
	virtual bool CanAffectPlayer();
	virtual void DrawShadow(sf::RenderWindow &window);
	virtual bool SpriteHasShadow() { return true; }
	virtual sf::Vector2f GetCurrentPositionShadow();
};

