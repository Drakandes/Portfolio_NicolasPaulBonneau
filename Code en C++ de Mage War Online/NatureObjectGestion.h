#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GlobalEnum.h"
#include <iostream>
#include <list>
#include "GlobalFunction.h"
#include "Tree.h"
#include "Cactus.h"
#include "Rock.h"
#include "MonsterBase.h"
#include "MainQuadtree.h"

class NatureObjectGestion
{
private: 
	std::vector<sf::Vector2f> position_tree;
	std::vector<sf::Vector2i> size_tree;

	sf::Vector2f size_wall{ 40,40 };

	enum TileSet { Grass_E, Dirt_E, Sand_E };
	std::list <std::shared_ptr<ProjectileBase>> list_nature_object;

	sf::Texture texture_wall;
	std::list<sf::Sprite> listWall;

	std::vector<sf::Vector2f> ListPositionForest;
	float distance_forest = 600;

	bool CheckIfForest(sf::Vector2f position_tree);
	sf::Vector2f GetNatureObjectPositionModifier();
public:
	NatureObjectGestion();
	~NatureObjectGestion();

	void AddANatureObject(sf::Vector2f position);
	void CreateAllNatureObject(std::vector<std::vector<int>> maptiletype, sf::Vector2i size_map, float size_tile, sf::RenderWindow &window);
	void AddNatureObjectToSpriteList();
	std::list<std::shared_ptr<ProjectileBase>> GetListAllNatureObjects();
	void DrawWall(sf::RenderWindow &window, sf::FloatRect part_map_activated);
	void DeleteListNatureObject();
};

