#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "MaterialBase.h"

class M_MagicSand : public MaterialBase, public std::enable_shared_from_this<M_MagicSand>
{
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Clock clock_animation;
	sf::Vector2f size_material{ 20,20 };
	int id;
	int rayon = 15;
	int number_animation = 8;
	int current_animation = 0;
	float rate_animation = 0.5;
	float rate_animation_flashing = 0.1;
	bool need_to_be_put_in_quadtree = false;
	bool is_to_delete = false;
	sf::Clock clock_duration;
public:
	M_MagicSand();
	~M_MagicSand();

	virtual int GetTypeMaterial() { return IM_MagicSand; };
	void Init(sf::Vector2f position, int new_id);
	virtual bool DrawOnTheFloor() { return false; }
	virtual void TeleportEntity(sf::Vector2f position, int TypeTeleportation) {}
	virtual void SetToDelete() { is_to_delete = true; }
	virtual void DealWithCollision(std::shared_ptr<CollisionalObject> object_collided);
	virtual int GetTypeCollisionalObject() { return Material_E; }
	virtual sf::FloatRect GetCollisionRect() { return sprite.getGlobalBounds(); }
	virtual sf::Vector2f GetCurrentPosition() { return sprite.getPosition(); }
	virtual void Draw(sf::RenderWindow &window);
	virtual int GetRayon() { return rayon; }
	virtual sf::Vector2f GetSize() { return size_material; }
	virtual int GetId() { return id; }
	virtual void Update(float DELTATIME, sf::Vector2f player_position);
	virtual bool IsNeedToDelete() { return is_to_delete; }
	virtual void PutItBackInQuadtree() { need_to_be_put_in_quadtree = true; }
	virtual bool CheckIfNeedGoBackQuadtree() { return need_to_be_put_in_quadtree; }
};

