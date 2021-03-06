#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GlobalEnum.h"
#include "GlobalFunction.h"
#include <iostream>
#include "MonsterBase.h"
#include "DarkOrb.h"
#include "ProjectileGestion.h"
#include "PushImpact.h"
#include "ScaryFace.h"
#include "Electricity.h"
#include "HealingBall.h"
#include "NetProjectile.h"

class Demon : public MonsterBase , public std::enable_shared_from_this<Demon>
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
	sf::Vector2f size_monster{ 75,75 };
	sf::Vector2f holder_cutting_position{ 0,0 };
	sf::Vector2f dimension_monster_texture{ 8,2 };
	sf::Vector2f position_current_monster;
	sf::Sprite sprite_monster;
	int group_monster;
	int id_monster;
	int id_giving_to_projectile =0;
	int rayon_of_collision = 72;
	int level_monster = 1;
	float angle = 0;
	float monster_holder_health;
	float monster_maximum_health = 312;
	float armor = 10;
	float time_between_animation = 0.055;
	float damage = 105;
	float monster_type_fragment_given = StrongFragment;
	float monster_fragments_given = 60;
	float range_of_view = range_of_view_monster;// 1200;
	float range_of_orbs = 700;
	float range_of_teleportation = 350;
	float money_given;
	float exp_given = 20;
	float stun_from_orb = 0.15;
	float stun_from_demon = 0.5;
	float time_being_stunned = 0;
	bool monster_alive = true;
	bool chasing_player = false;
	bool can_drop = false;
	bool been_drawn = false;
	bool monster_is_elite = false;
	bool need_to_be_put_in_quadtree = false;
	bool monster_is_stunned = false;
	bool is_guardian = false;
	sf::RectangleShape bar_total_health;
	sf::RectangleShape bar_current_health;
	sf::RectangleShape stun_bar;
	sf::Clock clock_between_animation;
	sf::Clock clock_between_attack;
	sf::Clock clock_damage_from_all_ignition;
	sf::Clock clock_between_new_positition;
	sf::Clock clock_restraining_fps;
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

	const static int number_graviting_darkorb = 5;
	float number_wings_rotation = 0;
	float number_wings_roation_maximum = 0;
	float holder_demon_splashing = 0;
	float time_between_splashing_animation = 0.05;
	float rotation_graviting_darkorb[number_graviting_darkorb];
	float darkorbit_distance_from_caster_initial = 100;
	float darkorb_distance_from_caster = 100;
	bool is_teleporting = false;
	bool is_splashing = false;
	bool splashing_can_do_damage = true;
	sf::Vector2f number_wings_rotation_range{ 3, 10 };
	sf::Vector2f size_texture_splashing{ 150,144 };
	sf::Clock clock_splashing_animation;
	sf::Clock clock_creation_darkorb;
	sf::Texture texture_splashing;
	sf::Sprite sprite_splashing;
	std::list<std::shared_ptr<DarkOrb>> ListAllDarkOrbs;

	sf::Vector2f position_of_spawn{ 0,0 };
	int id_spawn = -2;
	float size_spawn = 0;

	sf::Font font;
	sf::String string_monster_name;
	sf::Text text_monster_name;
	sf::Vector2f position_text_monster_name;

	sf::Texture shadow_texture;
	sf::Sprite shadow;
	sf::Vector2f shadow_size{ 75,75 };

	void SetAngle(sf::Vector2f player_position);

	std::vector<bool> listEliteBonus{};
	std::vector<float> listEliteBonusCooldown{};
	std::vector<sf::Clock> listEliteBonusClock;
	bool is_invisible = false;
	void MonsterEliteGestion(sf::Vector2f playerPosition, float player_speed, sf::Vector2f player_position, sf::Vector2f velocity_player);
	void MonsterEliteInit();
	void CheckEntityStillInMap();
public:
	Demon();
	~Demon();

	virtual int GetLevelMonster() { return level_monster; }
	virtual bool GetIfMonsterIsGuardian() { return is_guardian; }
	virtual void SetToDelete() { monster_alive = false; }
	virtual void HealObject(float heal_value);
	virtual bool IsMonsterElite() { return monster_is_elite; }
	virtual int GetIdSpawn() { return id_spawn; }
	virtual float GetMoney() { return money_given; }
	virtual void DealWithCollision(std::shared_ptr<CollisionalObject> object_collided);
	virtual int GetTypeCollisionalObject() { return Monster_E; }
	virtual sf::FloatRect GetCollisionRect() { return sprite_monster.getGlobalBounds(); }
	virtual sf::Vector2f GetCurrentPosition();
	virtual void Update(sf::Vector2f playerPosition, float player_speed, sf::Vector2f player_position, float DELTATIME, sf::Vector2f velocity_player);
	virtual float GetDamage();
	virtual float GotDamaged(float damage_dealt,int id_attacker,float armor_penetration_percent);
	virtual int GetRayon();
	virtual sf::Vector2f GetSize();
	virtual bool IsNeedToDelete();
	virtual int GetExp();
	virtual sf::String GetMonsterType();
	virtual int GetId();
	virtual sf::Vector2f GetTypeAndNumberFragments();
	virtual void FirstDraw(sf::RenderWindow &window);
	virtual bool IsOnPuddleBeer();
	virtual float ReturnLastNumberPudleTouched();
	virtual void GetIgnited(int type_ignition, float duration_ignition, float damage_ignition);
	virtual float DamageFromAllIgnition();
	void Init(int id_monster_received, sf::Vector2f position_spawn_r, int id_spawn_r, float size_spawn_r, int level_monster_r,sf::Vector2f position_monster, bool is_elite, bool is_monster_guardian);
	void Health_maintenance();
	virtual void CheckIfIgnited();
	virtual void IgnitionAnimationGestion();
	void CuttingSprite();
	void MovementGestion(sf::Vector2f player_position, float DELTATIME);
	virtual float GetDurationOfStun();
	virtual void StunGestion();
	virtual float GetStunTime();
	virtual void ChangeStunTime(float stun_time_received);
	virtual bool IsPlayerStunned();
	virtual void StunBarGestion();
	virtual void GetPushedAway(float distance_being_pushed_received, int force_of_pushing, sf::Vector2f origin_of_propulsion_receveid, sf::Vector2f origin_object_blocking);
	virtual void Draw(sf::RenderWindow &window);
	virtual bool CheckCollision(sf::FloatRect rect_collision, int id_object, sf::Vector2f position_object);
	virtual void PutItBackInQuadtree();
	virtual void DrawShadow(sf::RenderWindow &window);
	virtual bool SpriteHasShadow() { return true; }
	virtual sf::Vector2f GetCurrentPositionShadow();

	virtual bool CheckIfNeedGoBackQuadtree();
	void Teleportation();
	void SplashingGestion();
	void ChasingPlayer(sf::Vector2f player_postion);
	void NumberDarkOrbGestion();
	virtual sf::Vector2f GetChildPositionGoing();
	virtual void DeleteChild(int id_child);
	int GiveNewId();
};