#pragma once
#include <SFML/Graphics.hpp>
#include "GlobalFunction.h"
#include "GlobalEnum.h"
#include "CollisionalObject.h"
#include "ProjectileBase.h"
#include "ProjectileGestion.h"
#include "TextGenerator.h"

#include "Quadtree.h"
#include "RectTest.h"

class MainQuadtree
{
private:
	enum D { TopLeftQuadrant, BottomLeftQuadrant, BottomRightQuadrant, TopRightQuadrant };
	sf::RectangleShape rect;
	int MAX_OBJECTS = 10;
	int MAX_LEVELS = 8;
	int level = 0;
	int index = -1;
	std::list<std::shared_ptr<CollisionalObject>> ObjectsWithinQuadtree;
	std::list<std::shared_ptr<CollisionalObject>> ObjectsNature;
	std::vector<std::shared_ptr<Quadtree>> nodes;
	sf::Vector2f size_quadtree;
	sf::Vector2f position_quadtree;
	static MainQuadtree *s_instance;
	sf::Clock clock_collision;

	int getIndex(sf::Vector2f position_object, sf::Vector2f size_object);
public:
	MainQuadtree();
	~MainQuadtree();

	static void Initialize()
	{
		s_instance = new MainQuadtree();
	}
	static MainQuadtree *instance()
	{
		if (!s_instance)
			s_instance = new MainQuadtree();
		return s_instance;
	}
	void UpdatePositionsObjects(sf::FloatRect map_part_activated);
	void Clear();
	void Split();
	void insert(sf::Vector2f position_object, sf::Vector2f size_object, std::shared_ptr<CollisionalObject> object);
	void CheckCollision(sf::FloatRect map_part_activated);
	void Draw(sf::RenderWindow &window);
	void Init(int plevel, sf::Vector2f size_received, sf::Vector2f position_received, int holder);
	void DeleteEmptyNodes();
};

