#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GlobalEnum.h"
#include <iostream>
#include "GlobalFunction.h"
#include "ProjectileBase.h"
#include "Player.h"

class Boulder : public ProjectileBase
{
private:
	std::vector<int> ListIdObject;
	bool need_to_be_put_in_quadtree = false;
	std::shared_ptr<Player> parent;
	sf::Texture texture;
	sf::Sprite projectile;
	sf::Vector2f size_projectile{ 18,15 };
	sf::Vector2f projectile_position_origin;
	int rayon = 9;
	int id_projectile;
	int id_parent;
	int projectileDirectionToPlayer;
	int number_of_projectile = 0;
	int type_slow = StackableSlow_E;
	int number_hit = 0;
	float projectile_range = 450;
	float damage_initial;
	float damage;
	float speed_projectile = 600;
	float projectile_rotation;
	float slow_percent = 0;
	float slow_duration = 0;
	float stun_duration = 0;
	float projectile_animation = 0;
	bool is_to_delete = false;
	bool touching_projectile = false;
	bool can_init = true;
	bool been_init = false;
	bool been_drawed = false;
	bool init_from_skill = false;
	bool can_stun = false;
	bool can_slow = false;

	bool can_ignite = false;
	float ignition_damage = 0;
	float ignition_duration = 0;
	int type_ignition = -1;

	sf::Texture shadow_texture;
	sf::Sprite shadow;
	sf::Vector2f shadow_size{ 32,18 };

	sf::Clock clock_animation_of_projectile;
	std::vector<std::shared_ptr<SkillBase>> listAllSkills;

	void SetAngles(sf::Vector2f &mouse_position, sf::Vector2f &position);
	bool CheckIdObject(int id_object);
public:
	Boulder();
	~Boulder();

	virtual int GetId() { return id_parent; }
	virtual void SetToDelete() { is_to_delete = true; }
	virtual void PutItBackInQuadtree();
	virtual bool CheckIfNeedGoBackQuadtree();
	virtual void DealWithCollision(std::shared_ptr<CollisionalObject> object_collided);
	virtual int GetTypeCollisionalObject() { return Projectile_E; }
	virtual sf::FloatRect GetCollisionRect() { return projectile.getGlobalBounds(); }
	void Init(sf::Vector2f &position_player, float angle_received, float player_damage, std::shared_ptr<Player> player, float speed_modifier);
	void Texture_loading();
	void Movement_of_projectile(float DELTATIME);
	virtual sf::Vector2f GetCurrentPosition();
	void projectile_animation_gestion();
	sf::Vector2f GetSize();
	virtual int GetRayon();
	virtual float GetDamage();
	virtual bool IsNeedToDelete();
	virtual void Update(float DELTATIME, sf::Vector2f player_position);
	virtual bool CheckCollision(sf::FloatRect rect_collision, int id_object, sf::Vector2f position_object);
	void ChangeProjectileRotation(float angle);
	virtual void Initialized(int player_id);
	virtual bool GetInitStatus();
	void InitFromSkill(sf::Vector2f &position_player, float player_damage, sf::Vector2f mouse_position, float stun_duration_received, std::shared_ptr<Player> player, float range_modifier, float speed_modifier);
	void AngleGestion();
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
	virtual void DrawShadow(sf::RenderWindow &window);
	virtual bool SpriteHasShadow() { return true; }
	virtual sf::Vector2f GetCurrentPositionShadow();

	virtual bool CanSlow() { return can_slow; }
	virtual float GetDurationSlow() { return slow_duration; }
	virtual float GetPercentSlow() { return slow_percent; }
};
