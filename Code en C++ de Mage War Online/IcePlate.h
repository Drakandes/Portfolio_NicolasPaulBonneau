#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GlobalEnum.h"
#include "GlobalFunction.h"
#include <iostream>
#include "ProjectileBase.h"

class IcePlate : public ProjectileBase
{
private:
	bool need_to_be_put_in_quadtree = false;
	std::vector<int> ListIdObject;
	std::vector<sf::Clock> ListClockObject;
	const static int number_of_animation = 8;
	sf::Texture texture;
	sf::Vector2f size{ 125,125 };
	int rayon = 25;
	sf::Sprite sprite;
	sf::CircleShape circle;
	sf::Clock clock_time_between_created;
	sf::Clock clock_for_animation;
	sf::Clock clock_between_damage;
	bool is_to_delete = false;
	bool can_change_opcatity = false;
	float time_alive = 2;
	float damage_puddle = 25;
	float reset_timer = 0.2;
	float slow = -15;
	int holder_x = 0;
	int id_parent;
	int id_projectile;
public:
	IcePlate();
	~IcePlate();

	virtual int GetId() { return id_parent; }
	virtual bool DrawOnTheFloor() { return true; }
	virtual void PutItBackInQuadtree();
	virtual bool CheckIfNeedGoBackQuadtree();
	virtual void DealWithCollision(std::shared_ptr<CollisionalObject> object_collided);
	virtual int GetTypeCollisionalObject() { return Projectile_E; }
	virtual sf::FloatRect GetCollisionRect() { return sprite.getGlobalBounds(); }
	void Init(sf::Vector2f puddle_position, float damage_puddle_received, int id_caster);
	virtual void Update(float DELTATIME, sf::Vector2f player_position);
	virtual bool IsNeedToDelete();
	virtual void Draw(sf::RenderWindow &window);
	virtual int GetRayon();
	virtual sf::Vector2f GetCurrentPosition();
	virtual float GetDamage();
	virtual bool CheckCollision(sf::FloatRect rect_collision, int id_object, sf::Vector2f position_object);
	virtual bool CanAffectMonster();
	virtual bool CanAffectPlayer();
	bool CheckIdObject(int id_object);
};



