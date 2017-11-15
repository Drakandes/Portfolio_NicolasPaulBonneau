#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GlobalEnum.h"
#include <iostream>
#include "GlobalFunction.h"
#include "Player.h"
#include "ProjectileBase.h"

class LeafBlade : public ProjectileBase
{
private:
	std::shared_ptr<Player> parent;
	bool need_to_be_put_in_quadtree = false;
	int rayon = 17;
	int id_projectile;
	int id_parent;
	float damage;
	float speed_initial = 0;
	float ignite_damage;
	float ignite_duration;
	float rotation_projectile;
	float rotation_on_itself = 1;
	float range_projectile;
	float speed_projectile;
	float timer_animation = 0.05;
	float duration_reduction;
	float slow_applied;
	sf::Vector2f position_origin;
	sf::Vector2f size_projectile{ 10,34 };
	sf::Sprite projectile;
	sf::Texture texture_projectile;
	bool been_init = false;
	bool is_to_delete = false;
	bool coming_back_to_player = false;
	bool can_affect_monster = true;
	bool can_affect_player = false;

	sf::Texture shadow_texture;
	sf::Sprite shadow;
	sf::Vector2f shadow_size{ 10,34 };
public:
	LeafBlade();
	~LeafBlade();

	virtual int GetId() { return id_parent; }
	virtual void SetToDelete() { is_to_delete = true; }
	virtual void PutItBackInQuadtree();
	virtual bool CheckIfNeedGoBackQuadtree();
	virtual void DealWithCollision(std::shared_ptr<CollisionalObject> object_collided);
	virtual int GetTypeCollisionalObject() { return Projectile_E; }
	virtual sf::FloatRect GetCollisionRect() { return projectile.getGlobalBounds(); }
	void Init(sf::Vector2f &position_player, sf::Vector2f mouse_position, float damage_received, float speed_received, float range_projectile_received, float duration_reduction_recevied, float slow_applied_recevied, std::shared_ptr<Player> player);
	void Movement_of_fireball(sf::Vector2f position_player, float DELTATIME);	
	virtual void Update(float DELTATIME, sf::Vector2f player_position);
	virtual sf::Vector2f GetCurrentPosition();
	virtual sf::Vector2f GetSize();
	int GetRayon();
	virtual virtual float GetDamage();
	virtual bool IsNeedToDelete();
	virtual bool CheckCollision(sf::FloatRect rect_collision, int id_object, sf::Vector2f position_object);
	virtual void Initialized(int player_id);
	virtual bool GetInitStatus();
	void SetAngles(sf::Vector2f &mouse_position, sf::Vector2f &position);
	virtual float CheckCollisionWithCaster(int rayon_player, sf::Vector2f position_player, sf::Vector2f size_player);
	virtual void Draw(sf::RenderWindow &window);
	virtual bool CanSlow();
	virtual float GetDurationSlow();
	virtual float GetPercentSlow();
	virtual bool CanAffectMonster();
	virtual bool CanAffectPlayer();
	virtual bool CanChangeSkillCooldown() { return true; }
	virtual int GetSkillCooldownChanging() { return RestrainingLeafBladeEnum; }
	virtual float GetNewSkillCooldown() { return 0.4; }
	virtual void DrawShadow(sf::RenderWindow &window);
	virtual bool SpriteHasShadow() { return true; }
	virtual sf::Vector2f GetCurrentPositionShadow();
};

