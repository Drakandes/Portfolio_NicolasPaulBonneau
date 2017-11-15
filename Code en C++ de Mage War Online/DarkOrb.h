#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GlobalEnum.h"
#include <iostream>
#include "GlobalFunction.h"
#include "MonsterBase.h"
#include "ProjectileBase.h"

class DarkOrb : public ProjectileBase
{
private:
	bool need_to_be_put_in_quadtree = false;
	std::shared_ptr<MonsterBase> parent;
	int rayon = 9;
	int id_projectile;
	int id_parent;
	float damage_initial;
	float damage;
	float projectile_rotation_around_caster;
	float speed_projectile = 75;
	float distance_from_caster = 0;
	float speed_projectile_rotation_initial = 0.5;
	float speed_projectile_rotation = 2.5;
	float rotation_on_itself;
	float range_of_orbs = 700;
	sf::Vector2f position_origin;
	sf::Vector2f size_projectile{ 18,18 };
	sf::Vector2f size_projectile_for_drawing{ 24,24 };
	sf::Vector2f holder_cuting_sprite{ 0,0 };
	sf::Vector2f dimension_texture{ 0,0 };
	sf::Vector2f current_position;
	sf::Vector2f position_to_go;
	sf::Vector2f last_caster_position{ 0,0 };
	sf::Sprite projectile;
	sf::Texture texture_projectile;
	bool growing = true;
	bool is_to_delete = false;
	bool damage_boosted_by_accurate_shot = false;
	bool been_drawed = false;
	bool is_activated = false;
	bool is_reducing = false;
	sf::Clock clock_time_creation;
	sf::Clock clock_for_rotation;

	sf::Texture shadow_texture;
	sf::Sprite shadow;
	sf::Vector2f shadow_size{ 24,24 };
public:
	DarkOrb();
	~DarkOrb();

	void CanBeActivatedThisFrame() { is_activated = true; }
	virtual int GetId() { return id_parent; }
	virtual void SetToDelete();
	virtual void PutItBackInQuadtree();
	virtual bool CheckIfNeedGoBackQuadtree();
	virtual void DealWithCollision(std::shared_ptr<CollisionalObject> object_collided);
	virtual int GetTypeCollisionalObject() { return Projectile_E; }
	virtual sf::FloatRect GetCollisionRect() { return projectile.getGlobalBounds(); }
	void Init( int id_caster,sf::Vector2f &position_player, float distance_to_go, float damage_received, float direction_projectile_received, std::shared_ptr<MonsterBase> parent_received);
	void MovementGestion(float DELTATIME);
	virtual sf::Vector2f GetCurrentPosition();
	virtual sf::Vector2f GetSize();
	virtual int GetRayon();
	virtual float GetDamage();
	virtual bool IsNeedToDelete();
	virtual void Update(float DELTATIME, sf::Vector2f player_position);
	void UpdateAfterTeleportation(sf::Vector2f position_caster);
	float GetRotation();
	virtual void Draw(sf::RenderWindow &window);
	virtual bool CanAffectMonster();
	virtual bool CanAffectPlayer();
	virtual void DrawShadow(sf::RenderWindow &window);
	virtual bool SpriteHasShadow() { return true; }
	virtual sf::Vector2f GetCurrentPositionShadow();
};

