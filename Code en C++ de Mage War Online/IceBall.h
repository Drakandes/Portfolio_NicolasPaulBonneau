#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GlobalEnum.h"
#include <iostream>
#include "GlobalFunction.h"
#include "IcePlate.h"
#include "ProjectileBase.h"
#include "ProjectileGestion.h"

class IceBall : public ProjectileBase
{
private:
	bool need_to_be_put_in_quadtree = false;
	int rayon = 8;
	int id_projectile;
	int id_parent;
	float damage_initial;
	float damage;
	float direction_projectile;
	float range_projectile = 500;
	float speed_projectile = 1700;
	float timer_animation = 0.01;
	sf::Vector2f position_origin;
	sf::Vector2f size_projectile{ 16,16 };
	sf::Vector2f holder_cuting_sprite{ 0,0 };
	sf::Vector2f dimension_texture{ 0,0 };
	sf::Sprite projectile;
	sf::Texture texture_projectile;
	bool growing = true;
	bool is_to_delete = false;
	bool damage_boosted_by_accurate_shot = false;
	bool been_drawed = false;
	bool is_reducing = false;
	sf::Clock clock_animation;
	sf::Clock clock_time_creation;
	sf::Clock clock_movement;

	float rotation_spinning_projectile = 0;
	float stun_duration = 0.45;

	sf::Texture shadow_texture;
	sf::Sprite shadow;
	sf::Vector2f shadow_size{ 32,18 };

public:
	IceBall();
	~IceBall();

	virtual int GetId() { return id_parent; }
	virtual void SetToDelete() { is_to_delete = true; }
	virtual void PutItBackInQuadtree();
	virtual bool CheckIfNeedGoBackQuadtree();
	virtual int GetTypeCollisionalObject() { return Projectile_E; }
	virtual sf::FloatRect GetCollisionRect() { return projectile.getGlobalBounds(); }
	void Init(sf::Vector2f &position_player, float range_projectile_received, float damage_received, float direction_projectile_received, float speed_received, int id_caster);
	virtual sf::Vector2f GetCurrentPosition();
	virtual sf::Vector2f GetSize();
	virtual int GetRayon();
	virtual float GetDamage();
	virtual bool IsNeedToDelete();
	virtual void Update(float DELTATIME, sf::Vector2f player_position);
	virtual void Draw(sf::RenderWindow &window);
	virtual bool CanStun();
	virtual float GetStunTime();
	virtual bool CanAffectMonster();
	virtual bool CanAffectPlayer();
	virtual void DealWithCollision(std::shared_ptr<CollisionalObject> object_collided);
	virtual void DrawShadow(sf::RenderWindow &window);
	virtual bool SpriteHasShadow() { return true; }
	virtual sf::Vector2f GetCurrentPositionShadow();
};

