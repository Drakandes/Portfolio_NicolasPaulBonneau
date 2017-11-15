#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <list>
#include "SpriteBase.h"
#include <algorithm>
#include <memory>

class Player;
class MonsterBase;
class SkillBase;
class NatureObject;

class DrawGestion
{
private:
	static DrawGestion *s_instance;
	std::vector<std::shared_ptr<SpriteBase>> listAllSprites;
	std::vector<std::shared_ptr<SpriteBase>> listAllSpritesOnFloor;
	std::vector<sf::RectangleShape> listAllRectangle;
	std::vector<sf::CircleShape> listAllCircle;
	std::vector<float> listPositionYSprite;
	std::vector<float> listPositionYSpriteOnFloor;
	std::vector<bool> listIsShadowSprite;
	sf::Vector2f position_view_player;
	sf::Vector2f window_dimension;
public:
	DrawGestion();
	~DrawGestion();

	static void Initialize() 
	{ 
		s_instance = new DrawGestion(); 
	}
	static DrawGestion *instance()
	{
		if (!s_instance)
			s_instance = new DrawGestion;
		return s_instance;
	}

	void AddRectangleToList(sf::RectangleShape rectangle) { listAllRectangle.push_back(rectangle); }
	void AddCircleToList(sf::CircleShape circle) { listAllCircle.push_back(circle); }
	void AddObjectToList(std::shared_ptr<SpriteBase> ObjectToAdd);
	void DrawAllObjectInList(sf::RenderWindow &window, sf::Vector2f position_view_player);
	void GivePositionViewPlayerThisFrame(sf::Vector2f position_view_player_received);
	void GiveWindowDimension(sf::Vector2f window_dimension_received);
	void SortListSprite();
};
