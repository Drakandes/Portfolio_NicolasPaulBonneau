#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GlobalEnum.h"
#include "GlobalFunction.h"
#include <iostream>
#include "MonsterBase.h"
#include "BottleBeer.h"
#include "PushImpact.h"
#include "ScaryFace.h"
#include "Electricity.h"
#include "HealingBall.h"
#include "NetProjectile.h"

class Davbheer : public MonsterBase, public std::enable_shared_from_this<Davbheer>
{
private:

	const static int number_of_potions = 4;

	std::list<int> TypeIgnition;
	std::list<float> DurationIgnition;
	std::list<float> DamageIgnition;
	std::list<sf::Clock> ClockIgnition;
	std::list<int> TypeSlow;
	std::list<float> DurationSlow;
	std::list<float> PercentSlow;
	std::list<sf::Clock> ClockSlow;
	sf::Texture texture;
	sf::Vector2f size_monster{ 42,60 };
	sf::Vector2f holder_cutting_position{ 0,0 };
	sf::Vector2f last_position_player{ 0, 0 };
	sf::Sprite sprite_monster;
	sf::Sprite alert_point;
	sf::Sprite sleeping_point;
	int id_monster;
	int rayon_of_collision = 30;
	int direction_davbheer_going;
	int potion_drank;
	int number_of_thrown_beers = 0;
	int level_monster = 1;
	float distance_from_player = 0;
	float angle_going;
	float monster_health;
	float monster_maximum_health = 312;
	float armor = 15;
	float speed_initial = 235;
	float speed;
	float time_between_animation = 0.1;
	float damage = 125;
	float monster_type_fragment_given = StrongFragment;
	float monster_fragments_given = 60;
	float range_davbheer = 400;
	float range_of_view = range_of_view_monster;// 600;
	float exp_given = 20;
	float money_given;
	float attack_speed = 1.4;
	float speed_bottle = 675;
	float cooldown_potions[number_of_potions]{ 10,10,15,15 };
	float health_per_second = 0;
	float movement_potion_modifier = 6;
	float speed_bottle_modifier = 205;
	float range_bottle = 0;
	float time_being_stunned = 0;
	float regeneration_bottle = 90;
	bool monster_alive;
	bool ready_to_change_direction = false;
	bool chasing_player = false;
	bool can_drop = false;
	bool been_drawn = false;
	bool need_to_be_put_in_quadtree = false;
	bool potion_can_be_use[number_of_potions]{ true, true, true, true };
	bool using_a_potion = false;
	bool drinking_a_potion = false;
	bool is_on_a_puddle_of_beer = false;
	bool monster_is_elite = false;
	bool is_guardian = false;
	bool monster_is_stunned = false;
	sf::RectangleShape bar_total_health;
	sf::RectangleShape bar_current_health;
	sf::RectangleShape stun_bar;
	sf::Clock clock_between_animation;
	sf::Clock clock_between_attack;
	sf::Clock clock_between_potions[number_of_potions];
	sf::Clock clock_time_chasing_player;
	sf::Clock clock_regeneration;
	sf::Clock clock_damage_from_all_inition;
	sf::Clock clock_check_if_still_stunned;
	sf::Clock clock_bottle_regeneration;
	std::vector<int> potions{ 1,1,1,1 };

	bool is_ignite = false;
	sf::Texture texture_ignition;
	sf::Sprite sprite_ignition;
	sf::Vector2f holder_cutting_ignition_texture{ 0,0 };
	sf::Vector2f size_sprite_ignition{ 60,60 };
	sf::Clock clock_ignition_animation;
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
	Davbheer();
	~Davbheer();

	virtual sf::Vector2f GetEntityVelocity() { return sf::Vector2f((cos(angle_going * PI / 180))*speed, (sin(angle_going * PI / 180))*speed); }
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
	void Init(int id_monster_received, sf::Vector2f position_spawn_r, int id_spawn_r, float size_spawn_r, int level_monster_r,sf::Vector2f position_monster, bool is_elite, bool is_monster_guardian);
	void MovementGestion(float DELTATIME);
	void CuttingSprite();
	virtual void FirstDraw(sf::RenderWindow &window);
	void ThrowBottle(sf::Vector2f playerPosition, float player_speed, float DELTATIME, sf::Vector2f velocity_player);
	void ChasingPlayer(sf::Vector2f playerPosition, float player_speed);
	void Health_maintenance();
	void DrinkPotions(sf::Vector2f player_position);
	void Regeneration();
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
	virtual void PutItBackInQuadtree();
	virtual bool CheckIfNeedGoBackQuadtree();
	std::vector<float> quad(float a, float b, float c);
	virtual void DrawShadow(sf::RenderWindow &window);
	virtual bool SpriteHasShadow() { return true; }
	virtual sf::Vector2f GetCurrentPositionShadow();
};

