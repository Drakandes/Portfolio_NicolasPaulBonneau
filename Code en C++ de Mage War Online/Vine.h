#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GlobalEnum.h"
#include "Player.h"
#include <iostream>
#include "GlobalFunction.h"

#include "ProjectileBase.h"

class Vine : public ProjectileBase
{
private:
	std::shared_ptr<Player> parent;
	bool need_to_be_put_in_quadtree = false;
	int rayon = 500;
	int id_projectile;
	int type_slow = StackableSlow_E;
	int id_parent;
	float damage_initial;
	float damage;
	float speed;
	float rotation_projectile;
	float range_projectile = 500;
	float slow_percent = 0;
	float slow_duration = 0;
	float speed_projectile = 0.05;
	float timer_animation = 0.01;
	float timer_to_reach_max_range = 2;
	float stun_duration;
	sf::Vector2f position_origin;
	sf::Vector2f size_projectile{ 500,16 };
	sf::Vector2f size_projectile_for_cutting{ 500,24 };
	sf::Vector2f size_rect_collision{ 6,25 };
	sf::Vector2f size_current_projectile = sf::Vector2f(0, 0);
	sf::Vector2f holder_cuting_sprite{ 0,0 };
	sf::Vector2f dimension_texture{ 0,20 };
	sf::Sprite projectile;
	sf::RectangleShape rect_collision;
	sf::Texture texture_projectile;
	bool growing = true;
	bool is_to_delete = false;
	bool been_drawed = false;
	bool is_reducing = false;
	bool been_init = false;
	bool black_vine = false;
	bool init_from_skill = false;
	bool can_stun = false;
	bool can_slow = false;

	bool can_ignite = false;
	float ignition_damage = 0;
	float ignition_duration = 0;
	int type_ignition = -1;

	sf::Clock clock_animation;
	sf::Clock clock_time_creation;
	sf::Clock clock_collision;
	std::vector<std::shared_ptr<SkillBase>> listAllSkills;

	sf::Texture shadow_texture;
	sf::Sprite shadow;
	sf::Vector2f shadow_size{ 32,18 };

public:
	Vine();
	~Vine();

	virtual int GetId() { return id_parent; }
	virtual void SetToDelete() { is_to_delete = true; }
	virtual void PutItBackInQuadtree();
	virtual bool CheckIfNeedGoBackQuadtree();
	virtual void DealWithCollision(std::shared_ptr<CollisionalObject> object_collided);
	virtual sf::FloatRect GetCollisionRect() { return rect_collision.getGlobalBounds(); }
	void Init(sf::Vector2f &position_player, float angle_received, float damage_received, std::shared_ptr<Player> player, float speed_modifier);
	void InitFromSkill(sf::Vector2f &position_player, sf::Vector2f mouse_position, float damage_received, float stun_duration_received, std::shared_ptr<Player> player, float speed_modifier);
	void Movement_of_fireball(sf::Vector2f player_position, sf::Vector2f mouse_position, float DELTATIME);
	virtual sf::Vector2f GetCurrentPosition();
	virtual sf::Vector2f GetSize();
	virtual int GetRayon();
	virtual float GetDamage();
	virtual bool IsNeedToDelete();
	virtual bool CheckCollision(sf::FloatRect rect_collision, int id_object, sf::Vector2f position_object);
	virtual void Initialized(int player_id);
	virtual void CuttingSprite();
	virtual bool GetInitStatus();
	virtual void Update(float DELTATIME, sf::Vector2f player_position);
	virtual void Draw(sf::RenderWindow &window);
	virtual bool CanAffectMonster();
	virtual bool CanAffectPlayer();
	virtual bool CanStun();
	virtual float GetStunTime();
	void CheckPassiveSkills(int id_entity);
	virtual bool CanIgnite();
	virtual int GetTypeIgnition();
	virtual float GetIgnitionDuration();
	virtual float GetIgnitionDamage();
	virtual int GetTypeCollisionalObject() { return Projectile_E; }
	virtual void DrawShadow(sf::RenderWindow &window);
	virtual bool SpriteHasShadow() { return true; }
	virtual sf::Vector2f GetCurrentPositionShadow();

	virtual bool CanSlow() { return can_slow; }
	virtual float GetDurationSlow() { return slow_duration; }
	virtual float GetPercentSlow() { return slow_percent; }
};

