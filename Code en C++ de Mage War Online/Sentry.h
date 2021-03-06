#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GlobalEnum.h"
#include "GlobalFunction.h"
#include <iostream>
#include "MonsterBase.h"
#include "ProjectileGestion.h"
#include "SentryProjectile.h"
#include "PushImpact.h"
#include "ScaryFace.h"
#include "Electricity.h"
#include "HealingBall.h"
#include "NetProjectile.h"

class Sentry : public MonsterBase, public std::enable_shared_from_this<Sentry>
{
private:
	const static int number_of_potions = 4;
	enum Action{ Absorbing_a,Regrowing_a,Waiting_a};
	float actions_time_given[3]{ 0.3f, 0.3f , 0.5f };
	int actions_number_frames[3]{ 8,9,1 };
	std::list<int> TypeIgnition;
	std::list<float> DurationIgnition;
	std::list<float> DamageIgnition;
	std::list<sf::Clock> ClockIgnition;
	std::list<int> TypeSlow;
	std::list<float> DurationSlow;
	std::list<float> PercentSlow;
	std::list<sf::Clock> ClockSlow;
	sf::Texture texture;
	sf::Vector2f size_monster{ 84,46 };
	sf::Vector2f holder_cutting_position{ 0,0 };
	sf::Sprite sprite_monster;
	int group_monster;
	int id_monster;
	int rayon_of_collision = 42;
	int last_action = Absorbing_a;
	int action_doing = Waiting_a;
	int level_monster = 1;
	float loaded = false;
	float angle = 0;
	float monster_health;
	float monster_maximum_health = 520;
	float speed_initial = 0.2;
	float speed;
	float money_given;
	float damage = 125;
	float monster_type_fragment_given = StrongFragment;
	float monster_fragments_given = 60;
	float range_of_view = range_of_view_monster;// 600;
	float attack_speed = 1.35;
	float armor = 27;
	float exp_given = 20;
	float time_being_stunned = 0;
	bool monster_alive = true;
	bool been_drawn = false;
	bool monster_is_elite = false;
	bool monster_is_stunned = false;
	bool can_drop = false;
	bool need_to_be_put_in_quadtree = false;
	bool can_attack = false;
	bool is_guardian = false;
	sf::RectangleShape bar_total_health;
	sf::RectangleShape bar_current_health;
	sf::RectangleShape stun_bar;
	sf::Clock clock_between_animation;
	sf::Clock clock_between_attack;
	sf::Clock clock_damage_from_all_ignition;
	sf::Clock clock_between_new_positition;
	sf::Clock clock_check_if_still_stunned;

	bool is_ignite = false;
	sf::Texture texture_ignition;
	sf::Sprite sprite_ignition;
	sf::Vector2f holder_cutting_ignition_texture{ 0,0 };
	sf::Vector2f size_sprite_ignition{ 60,60 };
	sf::Clock clock_ignition_animation;
	sf::Clock clock_damage_from_all_inition;
	sf::Vector2f dimension_texture_ignition{ 5,4 };
	int number_ignition = 0;

	float distance_being_pushed;
	bool being_pushed = false;
	sf::Vector2f push_origin{ 0,0 };
	int push_force = NoPush;
	float push_rotation = 0;

	int number_slow = 0;
	float last_slow_percent = 0;
	float speed_projectile_throwing = 800;

	sf::Vector2f position_of_spawn{ 0,0 };
	int id_spawn = -2;
	float size_spawn = 0;

	sf::Font font;
	sf::String string_monster_name;
	sf::Text text_monster_name;
	sf::Vector2f position_text_monster_name;

	sf::Texture shadow_texture;
	sf::Sprite shadow;
	sf::Vector2f shadow_size{ 32,18 };

	std::vector<bool> listEliteBonus{};
	std::vector<float> listEliteBonusCooldown{};
	std::vector<sf::Clock> listEliteBonusClock;
	bool is_invisible = false;
	void MonsterEliteGestion(sf::Vector2f playerPosition, float player_speed, sf::Vector2f player_position, sf::Vector2f velocity_player);
	void MonsterEliteInit();
public:
	Sentry();
	~Sentry();

	virtual int GetLevelMonster() { return level_monster; }
	virtual bool GetIfMonsterIsGuardian() { return is_guardian; }
	virtual void SetToDelete() { monster_alive = false; }
	virtual void HealObject(float heal_value);
	virtual bool IsMonsterElite() { return monster_is_elite; }
	virtual int GetIdSpawn() { return id_spawn; }
	virtual float GetMoney() { return money_given; }
	virtual void DealWithCollision(std::shared_ptr<CollisionalObject> object_collided) {}
	virtual int GetTypeCollisionalObject() { return Monster_E; }
	virtual sf::FloatRect GetCollisionRect() { return sprite_monster.getGlobalBounds(); }
	virtual sf::Vector2f GetCurrentPosition();
 virtual void Update(sf::Vector2f playerPosition, float player_speed, sf::Vector2f player_position, float DELTATIME, sf::Vector2f velocity_player);
	virtual float GotDamaged(float damage_dealt,int id_attacker,float armor_penetration_percent);
	virtual int GetRayon();
	virtual sf::Vector2f GetSize();
	virtual bool IsNeedToDelete();
	virtual int GetExp();
	virtual sf::String GetMonsterType();
	virtual int GetId();
	virtual sf::Vector2f GetTypeAndNumberFragments();
	virtual void GetIgnited(int type_ignition, float duration_ignition, float damage_ignition);
	virtual float DamageFromAllIgnition();
	void Init(int id_monster_received, sf::Vector2f position_spawn_r,int id_spawn_r,float size_spawn_r,int level_monster_r, sf::Vector2f position_monster, bool is_elite, bool is_monster_guardian);
	void Health_maintenance();
	virtual void CheckIfIgnited();
	virtual void IgnitionAnimationGestion();
	void CuttingSprite();
	void MovementGestion(sf::Vector2f player_position, float DELTATIME);
	virtual void GiveNewCenterGroupPosition(sf::Vector2f new_position, int group_concerned, sf::Vector2f next_new_group_position);
	virtual int GetGroupMonster();
	virtual void StunGestion();
	virtual float GetStunTime();
	virtual void ChangeStunTime(float stun_time_received);
	virtual bool IsPlayerStunned();
	virtual void StunBarGestion();
	virtual void GetSlowed(int type_slow, float duration_slow, float percent_slow);
	void CalculateMovementSpeedWithSlows();
	virtual float GetDurationOfStun();
	virtual void GetPushedAway(float distance_being_pushed_received, int force_of_pushing, sf::Vector2f origin_of_propulsion_receveid, sf::Vector2f origin_object_blocking);
	virtual void Draw(sf::RenderWindow &window);
	virtual void PutItBackInQuadtree();
	virtual bool CheckIfNeedGoBackQuadtree();
	virtual void DrawShadow(sf::RenderWindow &window);
	virtual bool SpriteHasShadow() { return true; }
	virtual sf::Vector2f GetCurrentPositionShadow();

	void AttackPlayer(sf::Vector2f player_position, sf::Vector2f velocity_player);
};



