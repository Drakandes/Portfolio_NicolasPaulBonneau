#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GlobalEnum.h"
#include "GlobalFunction.h"
#include <iostream>
#include <list>
#include "MonsterBase.h"
#include "PushImpact.h"
#include "ScaryFace.h"
#include "Electricity.h"
#include "HealingBall.h"
#include "NetProjectile.h"

class Blob : public MonsterBase, public std::enable_shared_from_this<Blob>
{
private:
	std::vector<int> ListIdObject;
	std::vector <sf::Clock> ListClockObject;
	std::list<int> TypeIgnition;
	std::list<float> DurationIgnition;
	std::list<float> DamageIgnition;
	std::list<sf::Clock> ClockIgnition;
	std::list<int> TypeSlow;
	std::list<float> DurationSlow;
	std::list<float> PercentSlow;
	std::list<sf::Clock> ClockSlow;
	sf::Texture texture;
	sf::Texture alert_texture;
	sf::Texture blob_explosion_texture;
	sf::Sprite alert_point;
	sf::Sprite sleeping_point;
	sf::Sprite sprite_monster;
	sf::Vector2f alert_point_size{ 8,26 };
	sf::Vector2f sleeping_point_size{ 60, 30 };
	float blob_size_x = 52;
	float blob_size_y = 60;
	float speed_initial = 525;
	float speed;
	float speed_of_blob_raging_modifier_addition = 0.45;
	sf::Clock clock_blob_update;
	float monster_maximum_health = 468;
	float armor = 23;
	float reset_timer = 0.5;
	float monster_holder_health;
	float damage = 165;
	float angle_going;
	float monster_type_fragment_given = StrongFragment;
	float monster_fragments_given = 15;
	float stun_duration = 0.15;
	float time_being_stunned = 0;
	float exp_given = 20;
	float money_given;
	sf::RectangleShape monster_maximum_health_bar;
	sf::RectangleShape blob_health_bar;
	sf::RectangleShape stun_bar;
	sf::Clock clock_blob_speed;
	sf::Clock clock_blob_direction1;
	sf::Clock clock_blob_alert;
	sf::Clock clock_blob_animation;
	sf::Clock clock_blob_sleeping_point;
	sf::Clock clock_blob_raging;
	sf::Clock clock_check_if_still_stunned;
	int source_y_sleeping_point = 0;
	int source_x = 0;
	int source_y;
	int range_of_view = 700;
	int rayon = 30;
	int level_monster = 1;
	bool blob_standing_still = false;
	bool blob_chasing_player = false;
	bool blob_is_just_starting_chasing = false;
	bool blob_sleeping = false;
	bool blob_is_sleeping_alert = false;
	bool blob_sleeping_alert_created = false;
	bool blob_is_raging = false;
	bool monster_is_stunned = false;
	bool need_to_be_put_in_quadtree = false;
	bool monster_is_elite = false;
	bool can_drop = false;
	bool is_guardian = false;
	bool monster_alive = true;
	int id_monster;
	sf::Clock clock_damage_from_all_inition;

	bool is_ignite = false;
	sf::Texture texture_ignition;
	sf::Sprite sprite_ignition;
	sf::Vector2f holder_cutting_ignition_texture{ 0,0 };
	sf::Vector2f size_sprite_ignition{ 60,60 };
	sf::Clock clock_ignition_animation;
	sf::Clock player_collision_timer;
	sf::Vector2f dimension_texture_ignition{ 5,4 };
	int number_ignition = 0;
	float distance_being_pushed;
	bool being_pushed = false;
	sf::Vector2f push_origin{ 0,0 };
	int push_force = NoPush;
	float push_rotation = 0;

	int number_slow = 0;
	float last_slow_percent = 0;

	sf::Vector2f position_of_spawn{ 0,0 };
	int id_spawn = -2;
	float size_spawn = 0;

	sf::Font font;
	sf::String string_monster_name;
	sf::Text text_monster_name;
	sf::Vector2f position_text_monster_name;

	std::vector<bool> listEliteBonus{ };
	std::vector<float> listEliteBonusCooldown{};
	std::vector<sf::Clock> listEliteBonusClock;
	bool is_invisible = false;
	void MonsterEliteGestion(sf::Vector2f playerPosition, float player_speed, sf::Vector2f player_position, sf::Vector2f velocity_player);
	void MonsterEliteInit();
	void CheckEntityStillInMap();
public:
	Blob();
	~Blob();

	virtual sf::Vector2f GetEntityVelocity() { return sf::Vector2f((cos(angle_going * PI / 180))*speed, (sin(angle_going * PI / 180))*speed); }
	virtual int GetLevelMonster() { return level_monster; }
	virtual bool GetIfMonsterIsGuardian() { return is_guardian; }
	virtual void SetToDelete() { monster_alive = false; }
	virtual bool IsMonsterElite() { return monster_is_elite; }
	virtual int GetIdSpawn() { return id_spawn; }
	virtual float GetMoney() { return money_given; }
	virtual void DealWithCollision(std::shared_ptr<CollisionalObject> object_collided);
	virtual int GetTypeCollisionalObject() { return Monster_E; }
	virtual sf::FloatRect GetCollisionRect() { return sprite_monster.getGlobalBounds(); }
	void Texture_loading();
	void Init(int id_monster_received, sf::Vector2f position_spawn_r,int id_spawn_r,float size_spawn_r,int level_monster_r, sf::Vector2f position_monster, bool is_elite,bool is_monster_guardian);
	void Health_maintenance();
	void Movement_gestion( float DELTATIME);
	void Get_angle(sf::Vector2f player_Position);
	void Cutting_blob_sprite(sf::Vector2f player_Position);
	bool Is_blob_standing_still();
	void Blob_orientation();
	virtual sf::Vector2f GetCurrentPosition();
	virtual sf::Vector2f GetSize();
	virtual int GetRayon();
	virtual float GotDamaged(float damage_dealt,int id_attacker,float armor_penetration_percent);
	virtual bool CheckCollision(sf::FloatRect rect_collision, int id_object, sf::Vector2f position_object);
	virtual float GetDamage();
	void AlertPointMaintenance();
	void ChasingPlayerMaintenance(sf::Vector2f position_player);
	void SleepingPointMaintenance();
	void BlobRagingMaintenance();
	virtual bool IsNeedToDelete();
	virtual int GetExp();
	virtual sf::String GetMonsterType();
 virtual void Update(sf::Vector2f playerPosition, float player_speed, sf::Vector2f player_position, float DELTATIME, sf::Vector2f velocity_player);
	virtual int GetId();
	virtual sf::Vector2f GetTypeAndNumberFragments();
	virtual void GetIgnited(int type_ignition, float duration_ignition, float damage_ignition);
	virtual float DamageFromAllIgnition();
	virtual void CheckIfIgnited();
	virtual void IgnitionAnimationGestion();
	virtual void GetSlowed(int type_slow, float duration_slow, float percent_slow);
	void CalculateMovementSpeedWithSlows();
	virtual int GetGroupMonster();
	virtual float GetDurationOfStun();
	virtual void StunGestion();
	virtual float GetStunTime();
	virtual void ChangeStunTime(float stun_time_received);
	virtual bool IsPlayerStunned();
	virtual void StunBarGestion();
	virtual void GetPushedAway(float distance_being_pushed_received, int force_of_pushing, sf::Vector2f origin_of_propulsion_receveid, sf::Vector2f origin_object_blocking);
	virtual void Draw(sf::RenderWindow &window);
	virtual bool CanStun();
	virtual bool CheckIdObject(int id_object);
	virtual void PutItBackInQuadtree();
	virtual bool CheckIfNeedGoBackQuadtree();
	virtual void DrawShadow(sf::RenderWindow &window);

	virtual void HealObject(float heal_value);
};

