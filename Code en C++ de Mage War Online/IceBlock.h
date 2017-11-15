#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GlobalEnum.h"
#include <iostream>
#include "GlobalFunction.h"
#include "ProjectileBase.h"

class IceBlock : public ProjectileBase
{
private:
	bool need_to_be_put_in_quadtree = false;
	int rayon = 62;
	int id_projectile;
	int id_parent;
	sf::Vector2f position_projectile;
	sf::Vector2f size_projectile{ 124,76 };
	sf::Sprite projectile;
	sf::Texture texture_projectile;
	float duration_projectile;
	float distance_pushing;
	bool is_to_delete = false;
	bool been_init = false;
	sf::Clock clock_time_creation;

	sf::Texture shadow_texture;
	sf::Sprite shadow;
	sf::Vector2f shadow_size { 124,76 };
public:
	IceBlock();
	~IceBlock();

	virtual int GetId() { return id_parent; }
	virtual void PutItBackInQuadtree();
	virtual bool CheckIfNeedGoBackQuadtree();
	virtual void DealWithCollision(std::shared_ptr<CollisionalObject> object_collided);
	virtual int GetTypeCollisionalObject() { return Projectile_E; }
	virtual sf::FloatRect GetCollisionRect() { return projectile.getGlobalBounds(); }
	void Init(sf::Vector2f position_initial, float duration_received, float distance_pushing_received);
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
	virtual bool CanPush();
	virtual float GetDistancePushing();
	virtual bool CanAffectMonster();
	virtual bool CanAffectPlayer();
	virtual void DrawShadow(sf::RenderWindow &window);
	virtual bool SpriteHasShadow() { return true; }
	virtual sf::Vector2f GetCurrentPositionShadow();
};

