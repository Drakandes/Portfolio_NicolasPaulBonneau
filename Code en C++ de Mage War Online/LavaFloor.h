#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GlobalEnum.h"
#include <iostream>
#include <list>
#include "Player.h"
#include "GlobalFunction.h"
#include "ProjectileBase.h"

class LavaFloor : public ProjectileBase
{
private:
	std::shared_ptr<Player> parent;
	bool need_to_be_put_in_quadtree = false;
	std::vector<int> ListIdObject;
	std::vector<sf::Clock> ListClockObject;
	int rayon = 50;
	int id_projectile;
	int id_parent;
	int type_ignition = OnFireFromLavaFloor;
	float damage;
	sf::Vector2f position_projectile;
	sf::Vector2f size_projectile{ 100,50 };
	sf::Vector2f holder_cuting_sprite{ 0,0 };
	sf::Vector2f dimension_texture{ 4,1 };
	sf::Sprite projectile;
	sf::Texture texture_projectile;
	float current_time_between_damage = 0;
	float time_between_damage = 0;
	float time_between_animation = 0.1;
	float damage_ignition;
	float duration_ignition;
	float duration_projectile;
	bool is_to_delete = false;
	bool been_init = false;
	sf::Clock clock_time_creation;
	sf::Clock clock_between_animation;
	std::list<int> listIdMonsterTouched;
	std::list<sf::Clock> listClockBetweenAttack;

public:
	LavaFloor();
	~LavaFloor();

	virtual int GetId() { return id_parent; }
	virtual bool DrawOnTheFloor() { return true; }
	virtual void PutItBackInQuadtree();
	virtual bool CheckIfNeedGoBackQuadtree();
	virtual void DealWithCollision(std::shared_ptr<CollisionalObject> object_collided);
	virtual int GetTypeCollisionalObject() { return Projectile_E; }
	virtual sf::FloatRect GetCollisionRect() { return projectile.getGlobalBounds(); }
	void Init(sf::Vector2f position_initial, float damage_received, float duration_received, float time_between_damage_received, float damage_ignition_received, float duration_ignition_received, std::shared_ptr<Player> player);
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
	virtual bool CanIgnite();
	virtual int GetTypeIgnition();
	virtual float GetIgnitionDuration();
	virtual float GetIgnitionDamage();
	virtual bool CanAffectMonster();
	virtual bool CanAffectPlayer();
	bool CheckIdObject(int id_object);
};
