#pragma once
#include <SFML/Graphics.hpp>
#include "GlobalFunction.h"
#include "GlobalEnum.h"
#include "CollisionalObject.h"
#include "TextGenerator.h"

#include <memory>

class Quadtree
{
private:
	enum D{TopLeftQuadrant, BottomLeftQuadrant, BottomRightQuadrant, TopRightQuadrant};
	sf::RectangleShape rect;
	int MAX_OBJECTS = 10;
	int MAX_LEVELS = 5;
	int level = 0;
	int index = -1;
	std::list<std::shared_ptr<CollisionalObject>> ObjectsProjectile;
	std::list<std::shared_ptr<CollisionalObject>> ObjectsPlayer;
	std::list<std::shared_ptr<CollisionalObject>> ObjectsNature;
	std::list<std::shared_ptr<CollisionalObject>> ObjectsMonster;
	std::list<std::shared_ptr<CollisionalObject>> ObjectsMaterial;
	std::vector<std::shared_ptr<Quadtree>> nodes;
	sf::Vector2f size_quadtree;
	sf::Vector2f position_quadtree;
	sf::FloatRect floatrect;
	int counter = 0;
	sf::Clock clock_collision;

	bool CheckIfStillIn(sf::FloatRect object_collision_box);
public:
	Quadtree(int plevel, sf::Vector2f size_received, sf::Vector2f position_received, int index);
	~Quadtree();

	void UpdatePositionsObjects(sf::FloatRect map_part_activated);
	void Clear();
	void Split();
	void insert(std::shared_ptr<CollisionalObject> object);
	void CheckCollision(sf::FloatRect map_part_activated);
	void Draw(sf::RenderWindow &window);
	bool getIndex(sf::FloatRect object_collision_box);
	bool CheckIfToDelete();
	void AddObjectInList(std::shared_ptr<CollisionalObject> object);
};

