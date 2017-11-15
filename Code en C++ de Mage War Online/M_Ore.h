#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "MaterialBase.h"

class M_Ore : public MaterialBase, public std::enable_shared_from_this<M_Ore>
{
	sf::Texture texture_iron;
	sf::Texture texture_ruby;
	sf::Texture texture_emerald;
	sf::Texture texture_topaz;
	sf::Sprite sprite;
	sf::Vector2f size_material{ 20,16 };
	int id;
	int type_ore = IM_Iron;
	int rayon = 15;
	bool need_to_be_put_in_quadtree = false;
	bool is_to_delete = false;
	sf::Clock clock_duration;
public:
	M_Ore();
	~M_Ore();

	virtual int GetTypeMaterial() { return type_ore; };
	void Init(sf::Vector2f position, int new_id, int type_ore_received);
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

