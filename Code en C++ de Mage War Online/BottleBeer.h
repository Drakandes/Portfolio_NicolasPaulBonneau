#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GlobalEnum.h"
#include <iostream>
#include "GlobalFunction.h"
#include "ProjectileBase.h"
#include "BeerOnTheFloor.h"
#include "ProjectileGestion.h"

class BottleBeer : public ProjectileBase
{
private:
	bool need_to_be_put_in_quadtree = false;
	sf::Sprite bottle_beer;
	sf::Texture texture;
	sf::Vector2f size{ 24,24 };
	sf::Vector2f size_for_collision{ 14,14 };
	sf::Vector2f position_initial;
	float angle_rotation;
	float speed_bottle;
	int range;
	int id_projectile;
	int id_parent;
	bool is_to_delete = false;
	bool on_the_floor = false;
	int holder_x = 0;
	int rayon = 14;
	sf::Clock clock_between_animation;
	float time_between_animation = 0.15;
	float damage;
	int max_animation = 8;

	sf::Texture shadow_texture;
	sf::Sprite shadow;
	sf::Vector2f shadow_size{ 32,18 };
public:
	BottleBeer();
	~BottleBeer();

	virtual int GetId() { return id_parent; }
	virtual void SetToDelete() { is_to_delete = true; }
	virtual void PutItBackInQuadtree();
	virtual bool CheckIfNeedGoBackQuadtree();
	virtual void DealWithCollision(std::shared_ptr<CollisionalObject> object_collided);
	virtual int GetTypeCollisionalObject() { return Projectile_E; }
	void Init(sf::Vector2f position_davbheer, float angle_rotation_received, float davbheer_damage, float speed_bottle_received, float range_bottle, int id_caster);
	virtual void Update(float DELTATIME, sf::Vector2f player_position);
	virtual bool IsNeedToDelete();
	virtual void CuttingSprite();
	virtual float GetDamage();
	virtual bool CheckCollision(sf::FloatRect rect_collision, int id_object, sf::Vector2f position_object);
	virtual int GetRayon();
	virtual sf::Vector2f GetSize();
	virtual sf::Vector2f GetCurrentPosition();
	virtual void Draw(sf::RenderWindow &window);
	virtual bool CanAffectMonster();
	virtual bool CanAffectPlayer();
	virtual sf::FloatRect GetCollisionRect() { return bottle_beer.getGlobalBounds(); }
	virtual void DrawShadow(sf::RenderWindow &window);
	virtual bool SpriteHasShadow() { return true; }
	virtual sf::Vector2f GetCurrentPositionShadow();
};

