#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GlobalEnum.h"
#include <iostream>
#include "GlobalFunction.h"
#include "Player.h"
#include "ProjectileBase.h"

class LeafZone : public ProjectileBase
{
private:
	std::vector<int> ListIdObject;
	bool need_to_be_put_in_quadtree = false;
	int rayon = 150;
	int id_projectile;
	int current_rune_using;
	int id_parent;
	sf::Vector2f position_projectile;
	sf::Vector2f size_projectile{ 300,300 };
	sf::Sprite projectile;
	sf::Texture texture_projectile;
	float time_between_boost = 0;
	float duration_projectile;
	float boost_of_defense = 0;
	float boost_of_health_percent = 0;
	bool is_to_delete = false;
	bool been_init = false;
	bool shield_refilled = false;
	sf::Clock clock_time_creation;

	bool CheckIdObject(int id_object);
public:
	LeafZone();
	~LeafZone();

	virtual int GetId() { return id_parent; }
	virtual bool DrawOnTheFloor() { return true; }
	virtual void PutItBackInQuadtree();
	virtual bool CheckIfNeedGoBackQuadtree();
	virtual void DealWithCollision(std::shared_ptr<CollisionalObject> object_collided);
	virtual int GetTypeCollisionalObject() { return Projectile_E; }
	virtual sf::FloatRect GetCollisionRect() { return projectile.getGlobalBounds(); }
	void Init(sf::Vector2f position_initial, float duration_received, float defense_boost, float health_percent_boost, float time_between_boost_received, int current_rune);
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
	virtual bool CanChangeObjectStat();
	virtual int GetNumberObjectStatChange();
	virtual int GetObjectStatChanging(int number);
	virtual float GetObjectStatChangeDuration(int number);
	virtual float GetObjectStatChangValue(int number);
	virtual bool CanAffectMonster();
	virtual bool CanAffectPlayer();
};

