#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "SpriteBase.h"
#include "GlobalEnum.h"
#include <iostream>
#include <memory>

class EquipmentBase;

class CollisionalObject : public SpriteBase
{
protected:
	float push_speed = 135;
public:
	CollisionalObject();
	~CollisionalObject();

	virtual void ShieldObject(float amount_shield){}
	virtual std::vector<std::shared_ptr<EquipmentBase>> GetListEquipmentLoot() { std::vector<std::shared_ptr<EquipmentBase>> nothing; return nothing; }
	virtual bool SpriteHasShadow() { return false; }
	virtual void DrawShadow(sf::RenderWindow &window);
	virtual int GetTypeMaterial() { return -1; };
	virtual void AddMaterialToList(std::shared_ptr<CollisionalObject> object){}
	virtual bool DrawOnTheFloor() { return false; }
	virtual void TeleportEntity(sf::Vector2f position, int TypeTeleportation) {}
	virtual void SetToDelete() {}
	virtual void DealWithCollision(std::shared_ptr<CollisionalObject> object_collided) {}
	virtual int GetTypeCollisionalObject() { return Nothing_E; }
	virtual sf::FloatRect GetCollisionRect() { sf::FloatRect nothing; return nothing; }
	virtual sf::Vector2f GetCurrentPosition();
	virtual void Draw(sf::RenderWindow &window);
	virtual void GetPushedAway(float distance_being_pushed_received, int force_of_pushing, sf::Vector2f origin_of_propulsion_receveid, sf::Vector2f origin_object_blocking);
	virtual void ChangeStunTime(float stun_time_received);
	virtual void GivePlayerChangeStat(int type_change, float duration_change, float value_change);
	virtual void GetSlowed(int type_slow, float duration_slow, float percent_slow);
	virtual void GetIgnited(int type_ignition, float duration_ignition, float damage_ignition);
	virtual float GotDamaged(float damage_dealt,int id_attacker,float armor_penetration_percent);
	virtual void ChangeASkillCooldown(int skill_cooldown_changing, float new_cooldown);
	virtual int GetRayon();
	virtual sf::Vector2f GetSize();
	virtual bool CheckCollision(sf::FloatRect rect_collision, int id_object, sf::Vector2f position_object);
	virtual float GetDamage();
	virtual bool CanStun();
	virtual float GetDurationOfStun();
	virtual bool CheckIdObject(int id_object);
	virtual int GetId() { return 0; }
	virtual void Update(float DELTATIME, sf::Vector2f player_position){}
	virtual bool IsNeedToDelete() { return false; }
	virtual void PutItBackInQuadtree(){}
	virtual bool CheckIfNeedGoBackQuadtree(){ return false; }
	virtual void HealObject(float heal_value) { };

	virtual bool CanAffectMonster() { return false; }
	virtual bool CanAffectPlayer() { return false; }

	virtual bool CanPush() { return false; }
	virtual float GetDistancePushing() { return 0; }

	virtual bool CanSlow() { return false; }
	virtual float GetDurationSlow() { return 0; }
	virtual float GetPercentSlow() { return 0; }

	virtual float GetStunTime() { return 0; }

	virtual bool CanChangeSkillCooldown() { return false; }
	virtual int GetSkillCooldownChanging() { return 0; }
	virtual float GetNewSkillCooldown() { return 0; }

	virtual bool CanChangeObjectStat() { return false; }
	virtual int GetNumberObjectStatChange() { return 0; }
	virtual int GetObjectStatChanging(int number) { return 0; }
	virtual float GetObjectStatChangeDuration(int number) { return 0; }
	virtual float GetObjectStatChangValue(int number) { return 0; }

	virtual bool CanIgnite() { return false; }
	virtual int GetTypeIgnition() { return 0; }
	virtual float GetIgnitionDuration() { return 0; }
	virtual float GetIgnitionDamage() { return 0; }

	virtual bool CheckIfProjectileDisable() { return false; }
};

