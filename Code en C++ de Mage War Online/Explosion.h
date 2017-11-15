#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GlobalEnum.h"
#include <iostream>
#include "GlobalFunction.h"
#include <list>
#include "ProjectileBase.h"

class Explosion : public ProjectileBase
{
private:
	sf::Texture texture_explosion;
	sf::Sprite sprite_explosion;
	sf::Vector2f size_explosion{ 50,50 };
	sf::Vector2f position_explosion;
	sf::Clock clock_explosion_timer;
	float timer_explosion_to_update = 0.01;
	float damage_explosion;
	float rayon_explosion = 25;
	float explosion_push_distance;
	bool is_to_delete = false;
	int source_x = 0;
	int number_animation = 10;
	int id_parent;
public:
	Explosion();
	~Explosion();

	float GetDamage() { return damage_explosion; }
	int GetTypeCollisionalObject() { return Projectile_E; }
	sf::Vector2f GetCurrentPosition() { return sprite_explosion.getPosition(); }
	sf::Vector2f GetSize() { return size_explosion; }
	int GetRayon() { return rayon_explosion; }
	bool CanAffectMonster(){ return true; }
	bool CanAffectPlayer(){ return true; }
	sf::FloatRect GetCollisionRect() { return sprite_explosion.getGlobalBounds(); }
	void Init( sf::Vector2f position_explosion, float damage_explosion_received, int id_parent, float push_distance);
	void Draw(sf::RenderWindow &window);;
	bool IsNeedToDelete();	
	virtual bool CanPush();
	virtual float GetDistancePushing();
	void Update();
	virtual void DealWithCollision(std::shared_ptr<CollisionalObject> object_collided);
};

