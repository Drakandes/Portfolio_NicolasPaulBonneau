#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GlobalEnum.h"
#include <iostream>
#include "GlobalFunction.h"
#include "Player.h"
#include "ProjectileBase.h"

class PhantomBall : public ProjectileBase
{
private:
	bool need_to_be_put_in_quadtree = false;
	int rayon = 17;
	int id_projectile;
	float damage;
	float speed_initial = 0;
	float ignite_damage;
	float ignite_duration;
	float rotation_projectile;
	float range_projectile = 800;
	float speed_projectile;
	sf::Vector2f position_origin;
	sf::Vector2f size_projectile{ 19,19 };
	sf::Sprite projectile;
	sf::Texture texture_projectile;
	bool been_init = false;
	bool is_to_delete = false;
	bool coming_back = false;

	sf::Texture shadow_texture;
	sf::Sprite shadow;
	sf::Vector2f shadow_size{ 19,19 };
public:
	PhantomBall();
	~PhantomBall();

	virtual int GetId() { return id_projectile; }
	virtual void SetToDelete() { is_to_delete = true; }
	virtual void PutItBackInQuadtree();
	virtual bool CheckIfNeedGoBackQuadtree();
	virtual void DealWithCollision(std::shared_ptr<CollisionalObject> object_collided);
	virtual int GetTypeCollisionalObject() { return Projectile_E; }
	virtual sf::FloatRect GetCollisionRect() { return projectile.getGlobalBounds(); }
	void Init(sf::Vector2f &position_caster, float damage_received, float speed_received, float angle, int id_caster);
	void Movement_of_fireball(sf::Vector2f position_player, float DELTATIME);
	virtual void Update(float DELTATIME, sf::Vector2f player_position);
	virtual sf::Vector2f GetCurrentPosition();
	virtual sf::Vector2f GetSize();
	int GetRayon();
	virtual virtual float GetDamage();
	virtual bool IsNeedToDelete();
	virtual void Draw(sf::RenderWindow &window);
	virtual bool CanAffectPlayer();
	virtual void DrawShadow(sf::RenderWindow &window);
	virtual bool SpriteHasShadow() { return true; }
	virtual sf::Vector2f GetCurrentPositionShadow();
	void GiveParentPosition(sf::Vector2f position);
};
