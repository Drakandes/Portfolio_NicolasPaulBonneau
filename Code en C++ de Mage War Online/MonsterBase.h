#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "CollisionalObject.h"
#include "TextGenerator.h"
#include "ListObjectsSingleton.h"
#include "EnergizedBall.h"
#include "E_Ring.h"
#include "LootBag.h"
#include "DeathAnimationGestion.h"

class MonsterBase : public CollisionalObject
{
private:
	std::vector<sf::Vector2f> RarityItemRange{ sf::Vector2f(39.5,17),sf::Vector2f(32.5,33),sf::Vector2f(15,25),sf::Vector2f(7.5,15),sf::Vector2f(3,10) };
	float exp_given = 15;
	float money_given = 650;

	int GetRarityItem(int item_level);
protected:
	int number_monster_elite_bonus = 12;
	int number_energized_ball = 8;
	int rayon_scary_face = 200;
	int range_of_view_monster = 1500;
	int chance_to_drop_on_thousand = 150;
	float elite_percent_damage = 125;
	float elite_percent_health = 150;
	float elite_percent_speed = 50;
	float elite_percent_regeneration = 0.015;
	float elite_percent_attack_speed = 125;
	float number_base_fragment_given = 45;
	float range_teleportation = 250;
	float duration_invisibility = 5;
	float number_traps = 2;
	float elite_percent_exp = 200;
	float elite_percent_money = 200;
	float elite_percent_fragments = 200;
	sf::Vector2i range_healing_ball{ 250,500 };

	float DamageIncreaseGestion(float value, float level_monster);
	float HealthIncreaseGestion(float value, float level_monster);
	float ArmorIncreaseGestion(float value, float level_monster);
	float SpeedIncreaseGestion(float value, float level_monster);
	float AttackSpeedIncreaseGestion(float value, float level_monster);
	int GetNumberMonsterEliteBonus(int monster_level);
	int GetRandomMonsterEliteBonus(std::vector<bool> listAlreadyBonus);
	float GetExpGiven(int level_monster);
	float GetMoneyGiven(int level_monster);

	std::shared_ptr<E_Ring> CreateRing(int level_monster);
	int number_ring_bonus_maximum = 13;
	enum RingBonus{RingHpRecovery,RingHpPercentRevoery, RingMovementSpeedAddition,RingDamagePercent,RingDamageAddition,RingExperiencePercent,RingHealthAddition,RingHealthPercent,RingArmorAddition,RingArmorPercent,RingCooldown,RingAttackSpeedPercent,RingLifeSteal,};
	sf::Vector2f GetRangeBonus(int type_bonus, float item_level);
public:
	virtual void UpdateWithPlayer(std::shared_ptr<Player> ptr_pointer){}
	virtual sf::Vector2f GetEntityVelocity() { return sf::Vector2f(0, 0); }
	virtual int GetLevelMonster() { return 1; }
	virtual bool GetIfMonsterIsGuardian() { return false; }
	virtual bool IsMonsterElite() { return false; }
	virtual int GetIdSpawn() { return -1; }
	virtual float GetMoney() { return 0; }
	virtual void PutItBackInQuadtree() {}
	virtual bool CheckIfNeedGoBackQuadtree() { return false; }
	virtual void DealWithCollision(std::shared_ptr<CollisionalObject> object_collided){}
	virtual int GetTypeCollisionalObject() { return Nothing_E; }
	virtual sf::FloatRect GetCollisionRect() { sf::FloatRect nothing; return nothing; }
	virtual void Init(int id_received, bool is_elite);
	virtual sf::Vector2f GetCurrentPosition();
 virtual void Update(sf::Vector2f playerPosition, float player_speed, sf::Vector2f player_position, float DELTATIME, sf::Vector2f velocity_player);
	virtual bool CheckCollision(sf::FloatRect rect_collision, int id_object, sf::Vector2f position_object);
	virtual float GotDamaged(float damage_dealt,int id_attacker,float armor_penetration_percent);
	virtual int GetRayon();
	virtual sf::Vector2f GetSize();
	virtual float GetDamage();
	virtual void DrawToScreen(sf::RenderWindow &window, sf::View &view_player);
	virtual bool IsNeedToDelete();
	virtual int GetExp();
	virtual sf::String GetMonsterType();
	virtual int GetId();
	virtual sf::Vector2f GetTypeAndNumberFragments();
	virtual void FirstDraw(sf::RenderWindow &window);
	virtual bool IsOnPuddleBeer();
	virtual void ModifyMovementSpeedFromPercent(float percent);
	virtual float ReturnLastNumberPudleTouched();
	virtual void GetIgnited(int type_ignition, float duration_ignition, float damage_ignition);
	virtual float DamageFromAllIgnition();
	virtual void CheckIfIgnited();
	virtual void IgnitionAnimationGestion();
	virtual void GiveNewCenterGroupPosition(sf::Vector2f new_position, sf::Vector2f next_new_group_position);
	virtual int GetGroupMonster();
	virtual float GetDurationOfStun();
	virtual void StunGestion();
	virtual bool CanStun();
	virtual float GetStunTime();
	virtual void ChangeStunTime(float stun_time_received);
	virtual bool IsPlayerStunned();
	virtual void StunBarGestion();
	virtual void GetSlowed(int type_slow, float duration_slow, float percent_slow);
	virtual void GetPushedAway(float distance_being_pushed_received, int force_of_pushing, sf::Vector2f origin_of_propulsion_receveid, sf::Vector2f origin_object_blocking);
	virtual void Draw(sf::RenderWindow &window);
	virtual std::shared_ptr<MonsterBase> SpawnChild();
	virtual bool CanSpawnChild();
	virtual void GivePosition(sf::Vector2f position);
	virtual sf::Vector2f GetChildPositionGoing();
	virtual void DeleteChild(int id_child);
	virtual bool CheckIdObject(int id_object);
	virtual bool SpriteHasShadow() { return false; }
};

