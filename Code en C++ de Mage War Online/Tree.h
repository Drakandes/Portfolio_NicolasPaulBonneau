#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GlobalEnum.h"
#include <iostream>
#include "GlobalFunction.h"
#include "NatureObject.h"

class Tree : public NatureObject
{
private:
	
	enum TreeLine{FirstTree, SecondTree,ThirdTree,FourthTree, FifthTree , SixthTree,SeventhTree,EighthTree,NinethTree,TenthTree,EleventhTree,TwelevethTree,ThirdteenthTree, FourteenthTree};

	const static int health_max = 3;
	int number_different_trees = 14;
	int type_tree;
	int tile_tree_size = 32;
	int rayon_collision = 18;
	int health = 3;
	int number_stick_given = 6;
	sf::Sprite sprite;
	sf::RectangleShape rectangle_collision;
	sf::Texture texture;
	sf::Vector2f sprite_position;
	sf::Vector2f sprite_position_collision;
	sf::Vector2i sprite_size_cutting;
	sf::Vector2f sprite_size_collision{ 30,50 };
	sf::Vector2f position_for_cutting;
	bool drawn = false;
	bool is_to_delete = false;
	bool can_produce_material = true;
	sf::Clock clock_health;

	sf::Texture shadow_texture;
	sf::Sprite shadow;
	sf::Vector2f shadow_size{ 32,18 };
public:
	Tree();
	~Tree();

	virtual bool IsNeedToDelete() { return is_to_delete; }
	virtual void SetToDelete() { is_to_delete = true; }
	virtual sf::Vector2f GetSize();
	virtual void DealWithCollision(std::shared_ptr<CollisionalObject> object_collided);
	virtual int GetTypeCollisionalObject() { return NatureObject_E; }
	virtual sf::FloatRect GetCollisionRect() { return rectangle_collision.getGlobalBounds(); }
	virtual void Init(sf::Vector2f position, std::vector<sf::Vector2f> position_tree_received, std::vector<sf::Vector2i> size_tree_received, sf::RenderWindow &window);
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

