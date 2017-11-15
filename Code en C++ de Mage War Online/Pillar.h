#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "SpriteBase.h"
#include "CollisionalObject.h"
#include <memory>
#include "GlobalFunction.h"
#include "NotificationSystem.h"
#include "ListObjectsSingleton.h"

class Pillar : public SpriteBase
{
	enum TypePillar{Self_Damage, Self_Speed, Self_Exp, Self_Health};
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector2f size_sprite{ 25,50 };
	int type_pillar = 0;
	int counter = 0;
	bool used = false;
	sf::Clock clock_animation;
	sf::Clock clock_used;

	sf::Texture shadow_texture;
	sf::Sprite shadow;
	sf::Vector2f shadow_size{ 25,50 };
public:
	Pillar();
	~Pillar();

	void Init(sf::Vector2f position, int type_pillar);
	sf::Vector2i DealWithCollision(std::shared_ptr<CollisionalObject> object_collided);
	sf::FloatRect GetCollisionRect() { return sprite.getGlobalBounds(); }
	virtual sf::Vector2f GetCurrentPosition() { return sprite.getPosition(); }
	virtual void Draw(sf::RenderWindow &window);
	sf::Vector2f GetSize() { return size_sprite; }
	void Update(float DELTATIME, sf::Vector2f player_position);
	virtual void DrawShadow(sf::RenderWindow &window);
	virtual bool SpriteHasShadow() { return true; }
	virtual sf::Vector2f GetCurrentPositionShadow();
	void ChangeType(int new_type) { type_pillar = new_type; used = false; }
};

