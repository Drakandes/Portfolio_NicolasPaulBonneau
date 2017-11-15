#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GlobalEnum.h"
#include <iostream>
#include "GlobalFunction.h"
#include "ProjectileBase.h"

class EnergizedBall : public ProjectileBase
{
private:
	bool need_to_be_put_in_quadtree = false;
	int rayon = 6;
	int id_projectile;
	int id_parent;
	float damage_initial;
	float damage;
	float direction_projectile;
	float range_projectile = 300;
	float speed_projectile = 850;
	sf::Vector2f position_origin;
	sf::Vector2f size_projectile{ 11,10 };
	sf::Sprite projectile;
	sf::Texture texture_projectile;
	bool is_to_delete = false;
	bool been_drawed = false;
	sf::Clock clock_animation;

	sf::Texture shadow_texture;
	sf::Sprite shadow;
	sf::Vector2f shadow_size{ 11,10 };
public:
	EnergizedBall();
	~EnergizedBall();

	virtual int GetId() { return id_parent; }
	virtual void SetToDelete() { is_to_delete = true; }
	virtual void PutItBackInQuadtree();
	virtual bool CheckIfNeedGoBackQuadtree();
	virtual void DealWithCollision(std::shared_ptr<CollisionalObject> object_collided);
	virtual int GetTypeCollisionalObject() { return Projectile_E; }
	virtual sf::FloatRect GetCollisionRect() { return projectile.getGlobalBounds(); }
	void Init(sf::Vector2f &position_initial, float damage_received, float direction_projectile_received, int id_caster);
	void MovementGestion(float DELTATIME);
	virtual sf::Vector2f GetCurrentPosition();
	virtual sf::Vector2f GetSize();
	virtual int GetRayon();
	virtual float GetDamage();
	virtual bool IsNeedToDelete();
	virtual void Update(float DELTATIME, sf::Vector2f player_position);
	virtual void Draw(sf::RenderWindow &window);
	virtual bool CanAffectMonster();
	virtual bool CanAffectPlayer();
	virtual void DrawShadow(sf::RenderWindow &window);
	virtual bool SpriteHasShadow() { return true; }
	virtual sf::Vector2f GetCurrentPositionShadow();
};

