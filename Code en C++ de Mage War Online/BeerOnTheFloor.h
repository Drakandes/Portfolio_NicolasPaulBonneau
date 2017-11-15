#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GlobalEnum.h"
#include "GlobalFunction.h"
#include <iostream>
#include "ProjectileBase.h"

class BeerOnTheFloor : public ProjectileBase
{
private:
	bool need_to_be_put_in_quadtree = false;
	const static int number_of_animation = 8;
	sf::Texture texture;
	sf::Vector2f size{ 50,50 };
	int rayon = 25;
	int id_projectile;
	int id_parent;
	sf::Sprite sprite;
	sf::CircleShape circle;
	sf::Clock clock_time_between_created;
	sf::Clock clock_for_animation;
	bool is_to_delete = false;
	bool can_change_opcatity = false;
	float time_between_opacity = 0.5;
	float time_alive = 1;
	float time_between_animation = 0.05;
	float slow_from_puddle = -50;
	int holder_x =0;
public:
	BeerOnTheFloor();
	~BeerOnTheFloor();

	virtual bool DrawOnTheFloor() { return true; }
	virtual int GetId() { return id_parent; }
	virtual void PutItBackInQuadtree();
	virtual bool CheckIfNeedGoBackQuadtree();
	virtual void DealWithCollision(std::shared_ptr<CollisionalObject> object_collided);
	virtual int GetTypeCollisionalObject() { return Projectile_E; }
	void Init(sf::Vector2f bottle_beer_position, int id_caster);
	virtual void Update(float DELTATIME, sf::Vector2f player_position);
	virtual bool IsNeedToDelete();
	virtual void Draw(sf::RenderWindow &window);
	virtual bool CheckCollision(sf::FloatRect rect_collision, int id_object, sf::Vector2f position_object);
	virtual int GetRayon();
	virtual sf::Vector2f GetCurrentPosition();

	virtual bool CanChangeObjectStat();
	virtual int GetNumberObjectStatChange();
	virtual int GetObjectStatChanging(int number);
	virtual float GetObjectStatChangeDuration(int number);
	virtual float GetObjectStatChangValue(int number);

	virtual bool CanAffectMonster();
	virtual bool CanAffectPlayer();
	virtual sf::FloatRect GetCollisionRect() { return sprite.getGlobalBounds(); }
};

