#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GlobalEnum.h"
#include "ProjectileBase.h"
#include "Player.h"

class Fireball : public ProjectileBase
{
private:
	bool need_to_be_put_in_quadtree = false;
	std::shared_ptr<Player> parent;
	sf::Texture fireball_texture;
	sf::Sprite fireball_image;
	sf::Vector2f fireball_image_position_origin;
	sf::Clock clock_animation_of_fireball;
	float fireball_image_rotation;
	float fireball_image_size_x = 32;
	float fireball_image_size_y = 18;
	float fireball_speed;
	float speed_of_fireball = 225;
	float speed_of_fireball_accelerated_3 = speed_of_fireball * 3;
	float speed_of_fireball_accelerated_2 = speed_of_fireball * 2;
	float ignition_damage = 0;
	float fireball_damage_initial;
	float fireball_damage;
	float angle_rotation = 0;
	float ignition_duration = 0;
	float slow_percent = 0;
	float slow_duration = 0;
	float stun_duration = 0;
	int number_of_fireball = 0;
	int fireball_range = 800;
	int fireballDirectionToPlayer;
	int id_projectile;
	int id_parent;
	int type_slow = StackableSlow_E;
	int rayon = 16;
	int fireball_image_animation;
	bool fireball_reapparition;
	bool is_to_delete = false;
	bool drawed = false;
	bool init_from_skill = false;
	bool been_init = false;
	bool touching_fireball = false;
	bool can_init = true;
	bool animation_started = false;
	bool can_ignite = false;
	bool can_stun = false;
	bool can_slow = false;

	int type_ignition = -1;
	std::vector<std::shared_ptr<SkillBase>> listAllSkills;

	sf::Texture shadow_texture;
	sf::Sprite shadow;
	sf::Vector2f shadow_size{ 32,18 };

	void SetAngles(sf::Vector2f &mouse_position, sf::Vector2f &position);

public:
	Fireball();
	~Fireball();

	virtual int GetId() { return id_parent; }
	virtual void SetToDelete() { is_to_delete = true; }
	virtual void PutItBackInQuadtree();
	virtual bool CheckIfNeedGoBackQuadtree();
	virtual void DealWithCollision(std::shared_ptr<CollisionalObject> object_collided);
	virtual int GetTypeCollisionalObject() { return Projectile_E; }
	virtual sf::FloatRect GetCollisionRect() { return fireball_image.getGlobalBounds(); }
	void Init(sf::Vector2f &position_player, float angle_received, float player_damage, std::shared_ptr<Player> player, float speed_modifier);
	void Texture_loading();
	void Movement_of_fireball(float DELTATIME);
	virtual sf::Vector2f GetCurrentPosition();
	void fireball_animation_gestion();
	virtual sf::Vector2f GetSize();
	virtual int GetRayon();
	virtual void Update(float DELTATIME, sf::Vector2f player_position);
	virtual float GetDamage();
	virtual bool IsNeedToDelete();
	void ChangeFireballRotation(float angle);
	virtual void Initialized(int player_id);
	virtual bool GetInitStatus();
	bool GetAnimationStarted();
	void InitFromSkill(sf::Vector2f &position_player, int player_damage, float fireball_range_modified, float fireball_speed_modifier,sf::Vector2f mouse_position, std::shared_ptr<Player> player, float speed_modifier);
	virtual void Draw(sf::RenderWindow &window);
	virtual bool CanAffectMonster();
	virtual bool CanAffectPlayer();
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

	virtual bool CanStun() { return can_stun; }
	virtual float GetStunTime() { return stun_duration; }
};

