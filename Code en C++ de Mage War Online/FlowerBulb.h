#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GlobalEnum.h"
#include <iostream>
#include "GlobalFunction.h"
#include "Player.h"
#include "ProjectileBase.h"

class FlowerBulb : public ProjectileBase
{
private:
	bool need_to_be_put_in_quadtree = false;
	int rayon = 50;
	int id_projectile;
	int id_parent;
	float damage;
	sf::Vector2f position_projectile;
	sf::Vector2f size_projectile{ 70,74 };
	sf::Vector2f holder_cuting_sprite{ 0,0 };
	sf::Vector2f dimension_texture{ 7,1 };
	sf::Sprite projectile;
	sf::Texture texture_projectile;
	float time_between_animation = 0.5;
	float duration_projectile;
	bool is_to_delete = false;
	bool been_init = false;
	sf::Clock clock_time_creation;
	sf::Clock clock_between_animation;

	sf::Texture shadow_texture;
	sf::Sprite shadow;
	sf::Vector2f shadow_size{ 32,18 };
public:
	FlowerBulb();
	~FlowerBulb();

	virtual int GetId() { return id_parent; }
	virtual void PutItBackInQuadtree();
	virtual bool CheckIfNeedGoBackQuadtree();
	virtual void DealWithCollision(std::shared_ptr<CollisionalObject> object_collided);
	virtual int GetTypeCollisionalObject() { return Projectile_E; }
	virtual sf::FloatRect GetCollisionRect() { return projectile.getGlobalBounds(); }
	void Init(sf::Vector2f position_initial,float duration_received, std::shared_ptr<Player> player, float healing_percent);
	virtual sf::Vector2f GetCurrentPosition();
	virtual sf::Vector2f GetSize();
	virtual int GetRayon();
	virtual float GetDamage();
	virtual bool IsNeedToDelete();
	virtual bool CheckCollision(sf::FloatRect rect_collision, int id_object, sf::Vector2f position_object);
	virtual void Update(float DELTATIME, sf::Vector2f player_position);
	void CuttingSprite();
	virtual void CheckIfToDelete();
	virtual void Initialized(int player_id);
	virtual bool GetInitStatus();
	virtual void Draw(sf::RenderWindow &window);
	virtual bool CanAffectMonster();
	virtual bool CanAffectPlayer();
	virtual void DrawShadow(sf::RenderWindow &window);
	virtual bool SpriteHasShadow() { return true; }
	virtual sf::Vector2f GetCurrentPositionShadow();
};

