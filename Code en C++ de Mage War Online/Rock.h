#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GlobalEnum.h"
#include <iostream>
#include "GlobalFunction.h"
#include "NatureObject.h"

class Rock : public NatureObject
{
private:
	const static int health_max = 4;
	int number_different_trees = 14;
	int type_rock;
	int rayon_collision = 45;
	int health;
	int tile_rock_height = 50;
	sf::Sprite sprite;
	sf::Texture texture;
	sf::RectangleShape rectangle_collision;
	sf::Vector2f sprite_position;
	sf::Vector2i sprite_size_cutting{ 95,50 };
	sf::Vector2f sprite_size_collision{ 80,40 };
	sf::Vector2f sprite_position_collision;
	bool drawn = false;
	sf::Clock clock_health;
	bool can_produce_material = true;
	bool is_to_delete = false;

	sf::Texture shadow_texture;
	sf::Sprite shadow;
	sf::Vector2f shadow_size{ 32,18 };
public:
	Rock();
	~Rock();

	virtual bool IsNeedToDelete() {return is_to_delete;}
	virtual void SetToDelete() { is_to_delete = true; }
	virtual sf::Vector2f GetSize();
	virtual void DealWithCollision(std::shared_ptr<CollisionalObject> object_collided);
	virtual int GetTypeCollisionalObject() { return NatureObject_E; }
	virtual sf::FloatRect GetCollisionRect() { return rectangle_collision.getGlobalBounds(); }
	virtual void Init(sf::Vector2f position, sf::RenderWindow &window);
	virtual bool CheckCollision(sf::FloatRect rect_collision, int id_object, sf::Vector2f position_object);
	void HealthGestion();
	virtual sf::Vector2f GetCurrentPosition();
	virtual void Draw(sf::RenderWindow &window);
	virtual bool CanPush();
	virtual float GetDistancePushing();
	virtual bool CheckIfProjectileDisable() { if (health <= 0) { return true; } return false; }
	virtual void DrawShadow(sf::RenderWindow &window);
	virtual bool SpriteHasShadow() { return true; }
	virtual sf::Vector2f GetCurrentPositionShadow();
};
