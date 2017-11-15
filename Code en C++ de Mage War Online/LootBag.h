#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "MaterialBase.h"
#include <memory>

class E_Ring;

class LootBag : public MaterialBase, public std::enable_shared_from_this<LootBag>
{
	std::vector<std::shared_ptr<EquipmentBase>> ListLootInBag;
	sf::Texture texture_sprite;
	sf::Sprite sprite;
	sf::Vector2f size_sprite{ 9,12 };
	int id;
	bool need_to_be_put_in_quadtree = false;
	bool is_to_delete = false;
	sf::Clock clock_duration;

public:
	LootBag();
	~LootBag();

	virtual std::vector<std::shared_ptr<EquipmentBase>> GetListEquipmentLoot() {  return ListLootInBag; }
	void AddRingToBag(std::shared_ptr<EquipmentBase> ring) { ListLootInBag.push_back(ring); }
	void Init(sf::Vector2f position, int new_id);
	virtual bool DrawOnTheFloor() { return false; }
	virtual void TeleportEntity(sf::Vector2f position, int TypeTeleportation) {}
	virtual void SetToDelete() { is_to_delete = true; }
	virtual void DealWithCollision(std::shared_ptr<CollisionalObject> object_collided);
	virtual int GetTypeCollisionalObject() { return LootBag_E; }
	virtual sf::FloatRect GetCollisionRect() { return sprite.getGlobalBounds(); }
	virtual sf::Vector2f GetCurrentPosition() { return sprite.getPosition(); }
	virtual void Draw(sf::RenderWindow &window);
	virtual sf::Vector2f GetSize() { return size_sprite; }
	virtual int GetId() { return id; }
	virtual void Update(float DELTATIME, sf::Vector2f player_position);
	virtual bool IsNeedToDelete() { return is_to_delete; }
	virtual void PutItBackInQuadtree() { need_to_be_put_in_quadtree = true; }
	virtual bool CheckIfNeedGoBackQuadtree() { return need_to_be_put_in_quadtree; }
};

