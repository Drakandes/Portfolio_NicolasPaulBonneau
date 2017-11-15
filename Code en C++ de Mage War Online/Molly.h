#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GlobalEnum.h"
#include "GlobalFunction.h"
#include <iostream>
#include <list>
#include "MonsterBase.h"

class Molly : public MonsterBase, public std::enable_shared_from_this<Molly>
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
	sf::Texture monster_texture;
	sf::Sprite sprite_monster;
	sf::Vector2f monster_size{ 108,53 };
	sf::RectangleShape monster_maximum_health_bar;
	sf::RectangleShape monster_health_bar;
	sf::RectangleShape stun_bar;
	sf::Clock clock_animation;
	sf::Clock clock_check_if_still_stunned;
	int source_x = 0;
	int rayon = 30;
	int level_monster = 1;
	int id_monster;
	int number_animation = 8;
	int counter_hammer_charge = 0;
	bool monster_is_stunned = false;
	bool need_to_be_put_in_quadtree = false;
	bool can_drop = false;
	bool monster_alive = true;
	bool going_left = true;
	float cooldown_hammer = 10;
	float timer_animation = 0.075;
	float monster_type_fragment_given = StrongFragment;
	float monster_fragments_given = 15;
	float time_being_stunned = 0;
	float exp_given = 55;
	float money_given;
	float speed_projectile_throwing = 750;
	float monster_maximum_health = 1500;
	float armor = 22;
	float reset_timer = 0.5;
	float monster_holder_health;
	float damage = 200;
	float speed_initial = GlobalFunction::getRandomRange(450,550);
	float speed;
	float angle_going = 0;
	sf::Clock clock_ignition_animation;
	sf::Clock player_collision_timer;
	sf::Clock clock_damage_from_all_inition;
	sf::Clock clock_attack;
	sf::Clock clock_direction;

	sf::Vector2f lastest_position_player{ 0,0 };

	bool is_ignite = false;
	sf::Texture texture_ignition;
	sf::Sprite sprite_ignition;
	sf::Vector2f holder_cutting_ignition_texture{ 0,0 };
	sf::Vector2f size_sprite_ignition{ 60,60 };
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

	sf::Texture shadow_texture;
	sf::Sprite shadow;
	sf::Vector2f shadow_size{ 108,53 };

	sf::Font font;
	sf::String string_monster_name;
	sf::Text text_monster_name;
	sf::Vector2f position_text_monster_name;

	void CheckEntityStillInMap();
	bool CheckIdObject(int id_object);
public:
	Molly();
	~Molly();

	virtual int GetLevelMonster() { return level_monster; }
	virtual void SetToDelete() { monster_alive = false; }
	virtual int GetIdSpawn() { return id_spawn; }
	virtual float GetMoney() { return money_given; }
	virtual void DealWithCollision(std::shared_ptr<CollisionalObject> object_collided);
	virtual int GetTypeCollisionalObject() { return Monster_E; }
	virtual sf::FloatRect GetCollisionRect() { return sprite_monster.getGlobalBounds(); }
	void Init(int id_monster_received, sf::Vector2f position_monster);
	void Health_maintenance();
	void Movement_gestion(float DELTATIME, sf::Vector2f player_position);
	void Cutting_sprite();
	virtual sf::Vector2f GetCurrentPosition();
	virtual sf::Vector2f GetSize();
	virtual int GetRayon();
	virtual float GotDamaged(float damage_dealt, int id_attacker, float armor_penetration_percent);
	virtual float GetDamage();
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
	virtual float GetDurationOfStun();
	virtual void StunGestion();
	virtual float GetStunTime();
	virtual void ChangeStunTime(float stun_time_received);
	virtual bool IsPlayerStunned();
	virtual void StunBarGestion();
	virtual void GetPushedAway(float distance_being_pushed_received, int force_of_pushing, sf::Vector2f origin_of_propulsion_receveid, sf::Vector2f origin_object_blocking);
	virtual void Draw(sf::RenderWindow &window);
	virtual bool CanStun();
	virtual void PutItBackInQuadtree();
	virtual bool CheckIfNeedGoBackQuadtree();
	virtual void DrawShadow(sf::RenderWindow &window);
	virtual void HealObject(float heal_value);
};